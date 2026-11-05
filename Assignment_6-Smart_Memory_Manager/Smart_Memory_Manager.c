#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FREE 0
#define USED 1

struct block{
    int size;
    int start;
    int AllocationId;
    int status;
};

struct block* metadata;
unsigned char* memorypool;
int blockCount = 0;
int metadataCapacity = 0;
int nextAllocationId = 1;
int currentStrategy = 1;

int FirstFit(int requestedSize){   // first fit strategy
    int i;
    for (i = 0; i < blockCount; i++) {  
    if (metadata[i].status == FREE && metadata[i].size >= requestedSize) {
        break;  }
    }
    if (i == blockCount) {  // if no suitable block found
        return -1;  
    }
    if (metadata[i].size > requestedSize) {  // checking for splitting 
        if (blockCount == metadataCapacity) {         // incresing metada capacity
            int newCapacity = metadataCapacity * 2;
            struct block* temp = realloc(metadata, newCapacity * sizeof(struct block) );

            if (temp == NULL) {
                return -1; }   
            metadata = temp;
            metadataCapacity = newCapacity;
        }
        for (int j = blockCount; j > i + 1; j--) { 
            metadata[j] = metadata[j - 1];
        }
        metadata[i + 1].start = metadata[i].start + requestedSize;       // Create the remaining free block
        metadata[i + 1].size = metadata[i].size - requestedSize;
        metadata[i + 1].AllocationId = -1;
        metadata[i + 1].status = FREE;
        metadata[i].size = requestedSize;     
        blockCount++;
        }
    metadata[i].status = USED;
    metadata[i].AllocationId = nextAllocationId;
    nextAllocationId++;
    return metadata[i].AllocationId;     
}

int BestFit(int requestedSize){    // best fit strategy
    int bestIndex = -1;
    for (int i = 0; i < blockCount; i++) {
        if (metadata[i].status == FREE && metadata[i].size >= requestedSize) {
            if (bestIndex == -1 || metadata[i].size < metadata[bestIndex].size){
                bestIndex = i;  }
        }
    }
    if (bestIndex == -1) {  // if no suitable block found
        return -1; 
    }
    if (metadata[bestIndex].size > requestedSize) {  // checking for splitting

        if (blockCount == metadataCapacity) {  
            int newCapacity = metadataCapacity * 2;
            struct block* temp = realloc(metadata, newCapacity * sizeof(struct block));

            if (temp == NULL) {
                return -1;}
            metadata = temp;
            metadataCapacity = newCapacity;
            }
        for (int j = blockCount; j > bestIndex + 1; j--) {
            metadata[j] = metadata[j - 1];
        }
        metadata[bestIndex + 1].start = metadata[bestIndex].start + requestedSize;
        metadata[bestIndex + 1].size = metadata[bestIndex].size - requestedSize;
        metadata[bestIndex + 1].AllocationId = -1;
        metadata[bestIndex + 1].status = FREE;
        metadata[bestIndex].size = requestedSize;
        blockCount++;
        }
    metadata[bestIndex].status = USED;
    metadata[bestIndex].AllocationId = nextAllocationId;
    nextAllocationId++;
    return metadata[bestIndex].AllocationId;  
}

int WorstFit(int requestedSize){   // worst fit strategy
     int worstIndex = -1;
    for (int i = 0; i < blockCount; i++) {
        if (metadata[i].status == FREE && metadata[i].size >= requestedSize) {
            if (worstIndex == -1 || metadata[i].size > metadata[worstIndex].size) {
                worstIndex = i; }          
        }
    }
    if (worstIndex == -1) { 
        return -1;
    }
    if (metadata[worstIndex].size > requestedSize) {  // checking for splitting

        if (blockCount == metadataCapacity) {
            int newCapacity = metadataCapacity * 2;
            struct block* temp = realloc(metadata, newCapacity * sizeof(struct block));

            if (temp == NULL) {
                return -1;
            }
            metadata = temp;
            metadataCapacity = newCapacity;
        }
        for (int j = blockCount; j > worstIndex + 1; j--) {
            metadata[j] = metadata[j - 1];
        }
        metadata[worstIndex + 1].start = metadata[worstIndex].start + requestedSize;
        metadata[worstIndex + 1].size = metadata[worstIndex].size - requestedSize;
        metadata[worstIndex + 1].AllocationId = -1;
        metadata[worstIndex + 1].status = FREE;
        metadata[worstIndex].size = requestedSize;
        blockCount++;
    }
    metadata[worstIndex].status = USED;
    metadata[worstIndex].AllocationId = nextAllocationId;
    nextAllocationId++;
    return metadata[worstIndex].AllocationId;
}

void AllocateMemory() {     // allocation of memory using the strategies
    int requestedSize;
    int allocationId = -1;

    printf("\nEnter memory size to allocate: ");
    scanf("%d", &requestedSize);
      if (requestedSize <= 0) {
        printf("\nInvalid memory size!");
        return;  }

    switch (currentStrategy) {
        case 1:
            allocationId = FirstFit(requestedSize);
            break;
        case 2:
            allocationId = BestFit(requestedSize);
            break;
        case 3:
            allocationId = WorstFit(requestedSize);
            break;
        default:
            printf("\nInvalid allocation strategy!");
            return;
    }
    if (allocationId != -1) {
          printf("\nMemory allocated successfully!");
          printf("\nAllocation ID: %d", allocationId); }
    else  printf("\nMemory allocation failed!"); 
}

void mergeMemory(){  // merging the free blocks
    int i = 0;
    while (i < blockCount - 1) {

        if (metadata[i].status == FREE && metadata[i + 1].status == FREE) {
            metadata[i].size = metadata[i].size + metadata[i + 1].size;
            for (int j = i + 1; j < blockCount - 1; j++) {
                metadata[j] = metadata[j + 1];
            }
            blockCount--;  }       
        else i++;
    }
}

void ReleaseMemory(){    // releasing a memory block
    int allocationId;
    int found = 0;

    printf("\nEnter Allocation ID to release: ");
    scanf("%d", &allocationId);

    for (int i = 0; i < blockCount; i++) {
        if (metadata[i].AllocationId == allocationId &&
            metadata[i].status == USED) {
            metadata[i].status = FREE;
            metadata[i].AllocationId = -1;
            found = 1;
            mergeMemory();
            printf("\nMemory released successfully!");
            break;
        }
    }
    if (found == 0) {
        printf("\nInvalid Allocation ID!"); }
}

void  ResizeAllocation(){     // resizes the allocation
    int allocationId;
    int newSize;
    int oldIndex = -1;

    printf("\nEnter Allocation ID: ");
    scanf("%d", &allocationId);
    printf("\nEnter new memory size: ");
    scanf("%d", &newSize);

    if (newSize <= 0) {
        printf("\nInvalid memory size!");
        return; 
        }
    for (int i = 0; i < blockCount; i++) {
        if (metadata[i].AllocationId == allocationId && metadata[i].status == USED) {
            oldIndex = i;
            break; }       
    }
    if (oldIndex == -1) {
        printf("\nInvalid Allocation ID!");
        return;
    }
    int oldSize = metadata[oldIndex].size;
    int oldStart = metadata[oldIndex].start;

    if (newSize == oldSize) {
        printf("\nAllocation already has the requested size!");
        return;
    }
    if (newSize < oldSize) {
        int extraSpace = oldSize - newSize;
        if (blockCount == metadataCapacity) {
            int newCapacity = metadataCapacity * 2;
            struct block* temp = realloc(metadata, newCapacity * sizeof(struct block));

            if (temp == NULL) {
                printf("\nMetadata expansion failed!");
                return;
            }
            metadata = temp;
            metadataCapacity = newCapacity;
        }
        for (int j = blockCount; j > oldIndex + 1; j--) {
            metadata[j] = metadata[j - 1];
        }
        metadata[oldIndex].size = newSize;      
        metadata[oldIndex + 1].start = oldStart + newSize;
        metadata[oldIndex + 1].size = extraSpace;
        metadata[oldIndex + 1].AllocationId = -1;
        metadata[oldIndex + 1].status = FREE;
        blockCount++;
        mergeMemory();
        printf("\nAllocation resized successfully!");
        printf("\nOld size: %d", oldSize);
        printf("\nNew size: %d", newSize);
        return;
    }
    int extraSpace = newSize - oldSize;

    if ((oldIndex + 1 < blockCount) && (metadata[oldIndex + 1].status == FREE) && metadata[oldIndex + 1].size >= extraSpace) {     // Checking whether immediately next block is free
        metadata[oldIndex].size = newSize;
        metadata[oldIndex + 1].start += extraSpace;
        metadata[oldIndex + 1].size -= extraSpace;
        if (metadata[oldIndex + 1].size == 0) {        // if empty free block,remove
            for (int j = oldIndex + 1; j < blockCount - 1; j++) {
                metadata[j] = metadata[j + 1];
            }
            blockCount--;
        }
        printf("\nAllocation expanded successfully!");
        printf("\nOld size: %d", oldSize);
        printf("\nNew size: %d", newSize);
        return;
    }
    int targetIndex = -1;                //finding suitable free block
    for (int i = 0; i < blockCount; i++) {
        if (metadata[i].status == FREE && metadata[i].size >= newSize) {
            if (currentStrategy == 1) {   // First Fit
                targetIndex = i;
                break;
            }
            else if (currentStrategy == 2) {   // Best Fit
                if (targetIndex == -1 || metadata[i].size < metadata[targetIndex].size) {
                    targetIndex = i;
                }
            }
            else if (currentStrategy == 3) {   //worst fit
                if (targetIndex == -1 || metadata[i].size > metadata[targetIndex].size) {
                   targetIndex = i; }               
            }
        }
    }
    if (targetIndex == -1) {
        printf("\nResize failed! Insufficient free memory.");
        return;
    }
    if (metadata[targetIndex].size > newSize && blockCount == metadataCapacity) {    //metadata capacity, if splitting done
        int newCapacity = metadataCapacity * 2;
        struct block* temp = realloc(metadata, newCapacity * sizeof(struct block) );
        if (temp == NULL) {
            printf("\nMetadata expansion failed!");
            return;
        }
        metadata = temp;
        metadataCapacity = newCapacity;
    }
    int newStart = metadata[targetIndex].start; 

    if (metadata[targetIndex].size > newSize) {       // Splitting selected free block if necessary
        for (int j = blockCount; j > targetIndex + 1; j--) {
            metadata[j] = metadata[j - 1];
        }
        metadata[targetIndex + 1].start = newStart + newSize;
        metadata[targetIndex + 1].size = metadata[targetIndex].size - newSize;
        metadata[targetIndex + 1].AllocationId = -1;
        metadata[targetIndex + 1].status = FREE;
        blockCount++;
    }
    metadata[targetIndex].size = newSize;
    metadata[targetIndex].status = USED;
    metadata[targetIndex].AllocationId = allocationId;

    memcpy(memorypool + newStart, memorypool + oldStart, oldSize);  

    for (int i = 0; i < blockCount; i++) {  // Releasing the old allocation
        if (metadata[i].start == oldStart &&
            metadata[i].AllocationId == allocationId &&
            metadata[i].status == USED) {
            metadata[i].status = FREE;
            metadata[i].AllocationId = -1;
            break;
        }
    }
    mergeMemory();
    printf("\nAllocation resized successfully!");
    printf("\nAllocation moved to a new memory location.");
    printf("\nOld size: %d", oldSize);
    printf("\nNew size: %d", newSize);
}

void DisplayMemoryMap(){   // displaying the memeory map
    int i;
    printf("\n\n --MEMORY MAP--\n");
    if (blockCount == 0) {
        printf("\nNo memory blocks available!");
        return; }    
    printf("\n");
    printf("\nBlock\tStart\tEnd\tSize\tAllocation ID\tStatus");
    printf("\n");
    for (i = 0; i < blockCount; i++) {
        int end = metadata[i].start + metadata[i].size - 1;
        printf("\n%d\t%d\t%d\t%d\t", i + 1, metadata[i].start, end, metadata[i].size);

        if (metadata[i].status == USED) {
            printf("%d\t\tUSED", metadata[i].AllocationId);  }       
        else {   printf("-\t\tFREE"); }
    }
    printf("\n");
    printf("\n\nTotal number of blocks: %d", blockCount);
}
void DisplayMemoryStatistics(){  // displaying memory statics
    int totalMemory = 0;
    int allocatedMemory = 0;
    int freeMemory = 0;
    int allocatedBlocks = 0;
    int freeBlocks = 0;
    int largestFreeBlock = 0;
    float utilization = 0;
    float freePercentage = 0;
    float fragmentation = 0;

    for (int i = 0; i < blockCount; i++) {   //  memory statistics
        totalMemory += metadata[i].size;
        if (metadata[i].status == USED) {
            allocatedMemory += metadata[i].size;
            allocatedBlocks++;
        }
        else {
            freeMemory += metadata[i].size;
            freeBlocks++;
            if (metadata[i].size > largestFreeBlock) {
                largestFreeBlock = metadata[i].size;  }           
        }
    }
    if (totalMemory > 0) {      //  percentage
        utilization = ((float)allocatedMemory / totalMemory) * 100;
        freePercentage = ((float)freeMemory / totalMemory) * 100;  }
    
    if (freeMemory > 0) {       // external fragmentation
       fragmentation = ((float)(freeMemory - largestFreeBlock)/ freeMemory) * 100;
    }
    printf("\n\n---MEMORY STATISTICS---");
    printf("\n\nTotal Memory: %d bytes", totalMemory);
    printf("\nAllocated Memory: %d bytes", allocatedMemory);
    printf("\nFree Memory: %d bytes", freeMemory);
    printf("\n\nTotal Blocks: %d", blockCount);
    printf("\nAllocated Blocks: %d", allocatedBlocks);
    printf("\nFree Blocks: %d", freeBlocks);
    printf("\n\nMemory Utilization: %.2f%%", utilization);
    printf("\nFree Memory Percentage: %.2f%%", freePercentage);
    printf("\nExternal Fragmentation: %.2f%%", fragmentation);
    printf("\nLargest Free Block: %d bytes", largestFreeBlock);
    printf("\n");
}
void cleanup() {       // freeing memory
    free(metadata);
    free(memorypool);
    metadata = NULL;
    memorypool = NULL;
}

int main(){
    int poolsize;
    int startegyChoice;
    int menuechoice;

    printf("\n Memory Mnagaement System:-\n ");
    printf("\nEnter memory pool size: ");     // poolsize entry &check
    scanf("%d", &poolsize);
    while(poolsize<=0 || poolsize>1000000){     
        printf("Invalid poolsize");
        printf("\nEnter Again ");
        scanf("%d", &poolsize);
    }
    memorypool = malloc(poolsize*sizeof(unsigned char));  // memorypool allocated 
    if (memorypool == NULL) {
    printf("\nMemory pool allocation failed!");
    return 1;
    }

    metadata = malloc(sizeof(struct block));    // metadata allocated
    if (metadata == NULL) {
        printf("\nMetadata allocation failed!");
        free(memorypool);
        return 1;
    }
    metadata[0].start = 0;           // initial metadata status
    metadata[0].size = poolsize;
    metadata[0].AllocationId = -1;
    metadata[0].status = FREE;
    blockCount = 1;
    metadataCapacity = 1;

    printf("\nSelect allocation strategy:");   // Selecting allocation 
    printf("\n1. First Fit");
    printf("\n2. Best Fit");
    printf("\n3. Worst Fit");
    printf("\nEnter your choice: ");
    scanf("%d", &startegyChoice);

    while (startegyChoice < 1 || startegyChoice > 3) {
        printf("\nInvalid strategy choice!");
        printf("\nEnter again (1/2/3): ");
        scanf("%d", &startegyChoice);
    }
    currentStrategy = startegyChoice;
    if (currentStrategy == 1) {
        printf("Strategy set to First Fit.");
    }
    else if (currentStrategy == 2) {
        printf("Strategy set to Best Fit.");
    }
    else {  printf("Strategy set to Worst Fit."); }
    
    printf("\n Menu:");
    printf("\n1. Allocate memory");  
    printf("\n2. Release memory");    
    printf("\n3. Resize allocation");    
    printf("\n4. Display memory map");     
    printf("\n5. Display memory statistics");     
    printf("\n6. Change allocation strategy");     
    printf("\n7. Exit");    
    do{
    printf("\n Enter menue choice: ");
    scanf("%d", &menuechoice);
    switch(menuechoice){
        case 1:{
            AllocateMemory();
            break;
        }
        case 2:{
            ReleaseMemory();
            break;
        }
        case 3:{
            ResizeAllocation();
            break;
        }
        case 4:{
            DisplayMemoryMap();
            break;
        }
        case 5:{
            DisplayMemoryStatistics();
            break;
        }
        case 6:{
            printf("\nSelect allocation strategy choice (1/2/3 ):");
            scanf("%d", &startegyChoice);

            if (startegyChoice >= 1 && startegyChoice <= 3) {
                currentStrategy = startegyChoice;
                if (currentStrategy == 1) {
                    printf("\nStrategy changed to First Fit.");  }
                
                else if (currentStrategy == 2) {
                    printf("\nStrategy changed to Best Fit.");  }
                
                else { printf("\nStrategy changed to Worst Fit."); }
                }  

            else {   printf("\nInvalid strategy choice."); }
            break;
        }
        case 7:{
            printf("\n Exiting");
            break;
        }
        default:{
            printf("\nInvalid choice");
            break;
        }
    }
}
while (menuechoice != 7);
cleanup();
return 0;   
}