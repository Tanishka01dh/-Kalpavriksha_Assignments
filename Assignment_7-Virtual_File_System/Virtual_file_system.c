#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BLOCK_SIZE 512
#define NUM_BLOCKS 1024
#define FILE_TYPE 1
#define DIR_TYPE 2

typedef struct FreeBlock{       // structure for freeblock node
    int index;
    struct FreeBlock *next;
    struct FreeBlock *prev;
}  FreeBlock;
FreeBlock *freeHead = NULL;  //points to first freeblock
FreeBlock *freeTail = NULL;  //points to current last free block

typedef struct FileNode{     // structure for file/directory node
    char name[51];
    int type;
    struct FileNode *parent;
    struct FileNode *child;
    struct FileNode *next;

    int *blockPointers;
    int blockCount;
    int contentSize;
}  FileNode;
FileNode *root = NULL;
FileNode *cwd = NULL;

int initializeFreeList(){      // allocates memory for all initial free blocks 

    for(int i=0;i<NUM_BLOCKS;i++){
        FreeBlock* newnode;
        newnode = malloc(sizeof(FreeBlock));
        if(newnode == NULL){
            printf("Freeblock allocation failed \n");
            return 1;
        }
        newnode->index = i;
        newnode->next = NULL;
        newnode->prev = freeTail;

        if(freeHead == NULL){
            freeHead = newnode; }
        else { freeTail->next = newnode;
        }
        freeTail = newnode;
    }
    printf("\nFree block list initialized successfully");
    return 0;
}

void createRootDirectory(){          // creates the initial root directory
    root = malloc(sizeof(FileNode));
    if(root == NULL){
        printf("\nRoot directory creation failed!\n");
        return;
    }
    strcpy(root->name, "/");
    root->type = DIR_TYPE;
    root->parent = NULL;
    root->child = NULL;
    root->next = NULL;

    root->blockPointers = NULL;
    root->blockCount = 0;
    root->contentSize = 0;
    printf("Root directory created successfully!\n");
    }


FileNode *findNode(FileNode *parent, char name[]) {    // fun to find a node in filenode linked list
    if(parent->child == NULL){
        return NULL;
    }
    FileNode *temp = parent->child;
    do{
        if(strcmp(temp->name, name) == 0) { return temp; }
        temp = temp->next;
    } while(temp != parent->child);

    return NULL;   // if no matching node found
}

void mkdir(char dirname[]){      //fun for creating the directory
    FileNode *newnode;
    newnode = malloc(sizeof(FileNode));
    if (newnode == NULL) {
        printf("Directory creation failed!\n");
        return;}
    
    if(findNode(cwd, dirname) != NULL){
        printf("Name already exists!\n");
        free(newnode);
        return; }

    strcpy(newnode->name, dirname);
    newnode->type = DIR_TYPE;
    newnode->parent = cwd;
    newnode->child = NULL; 
    newnode->blockPointers = NULL;
    newnode->blockCount = 0;
    newnode->contentSize = 0;

    if(cwd->child == NULL){   // if it is cwd's 1st child
        newnode->next = newnode;
        cwd->child = newnode; 
    }
    else {
        FileNode *temp = cwd->child;
        while(temp->next != cwd->child){
            temp = temp->next;
        }
        temp->next = newnode;
        newnode->next = cwd->child;
    }
    printf("Directory created successfully\n");
}

void rmdir(char dirname[]){    // function to remove a dir
    FileNode *dir = findNode(cwd, dirname);
    if(dir == NULL){
        printf("Directory not found\n");
        return;
    }
    if(dir->type != DIR_TYPE){
        printf("Cannot remove a file using rmdir\n");
        return;
    }
    if(dir->child != NULL){
        printf("Directory is not empty, can't be deleted\n");
        return;}

    FileNode *prev = dir;
    while(prev->next != dir){
        prev = prev->next;
    }

    if(prev == dir){          // Removing directory from circular list
        cwd->child = NULL;
    }
    else{
        prev->next = dir->next;
        if(cwd->child == dir){
            cwd->child = dir->next;
        }
    }
    free(dir);
    printf("Directory removed successfully!\n");
}

void ls(){        // shows the contents of the cwd
    if(cwd->child == NULL){
        printf("Directory is empty\n");
        return;
    }
    FileNode *temp = cwd->child;
    printf("Contents of %s:\n", cwd->name);
    do{
        if(temp->type == DIR_TYPE)
            printf("(DIR)  %s\n", temp->name);
        else if(temp->type == FILE_TYPE)
            printf("(FILE) %s\n", temp->name);

        temp = temp->next;
    } while(temp != cwd->child);
}

void cd(char dirname[]){         //function for entering cd
    if(strcmp(dirname, "/") == 0){   // if cd root
        cwd = root;
        return;
    }
    if(strcmp(dirname, "..") == 0){   // going to parent directory
        if(cwd->parent != NULL){
            cwd = cwd->parent;
            return; }
        else {
            printf("Already in root directory \n");
        return;}
    }
    if(cwd->child == NULL){          // going to requested dir
        printf("Directory not found \n");
        return;
    }
    FileNode *temp = cwd->child;
    do{
        if(strcmp(temp->name, dirname) == 0){
            if(temp->type == DIR_TYPE){
                cwd = temp;
                return;
            }
            else{
                printf("Cannot enter a file \n");
                return;
            } }
        temp = temp->next;
    }  while(temp != cwd->child);
    printf("Directory not found!\n");
}

void pwd() {          // fun to print the current working directory
    FileNode *temp = cwd;
    char path[1000];
    char *directories[100];
    int count = 0;

    while(temp != NULL && temp != root){
        directories[count] = temp->name;
        count++;
        temp = temp->parent;
    }
    printf("/");

    for(int i = count - 1; i >= 0; i--){
        printf("%s", directories[i]);
        if(i != 0)
            printf("/");
    }
    printf("\n");
}

void create( char filename[]){        // fun to create a file
    FileNode *newnode;
    newnode = malloc(sizeof(FileNode));
    if(newnode == NULL){
        printf("File creation failed!\n");
        return; }

    if(findNode(cwd, filename) != NULL){
        printf("Name already exists!\n");
        free(newnode);
        return; }
    strcpy(newnode->name, filename);
    newnode->type = FILE_TYPE;
    newnode->parent = cwd;
    newnode->child = NULL;
    newnode->blockPointers = NULL;
    newnode->blockCount = 0;
    newnode->contentSize = 0;

    if(cwd->child == NULL){
        newnode->next = newnode;
        cwd->child = newnode; }
    else {
        FileNode *temp = cwd->child;
        while(temp->next != cwd->child){
            temp = temp->next;
        }
        temp->next = newnode;
        newnode->next = cwd->child;
    }
}

void writeFile(char filename[], char content[], unsigned char virtualdisk[NUM_BLOCKS][BLOCK_SIZE]){   // fun to write contents ina  file
    FileNode *temp = findNode(cwd, filename);
    if(temp == NULL){
        printf("File not found!\n");
        return; }

    if(temp->type != FILE_TYPE){
        printf("Cannot write into a directory\n");
        return; }
    if(temp->blockCount > 0){
        printf("File already contains data!\n");
        return;
    }

    int size = strlen(content);
    if(size == 0){
        printf("Empty content!\n");
        return;}

    int requiredBlocks = (size + BLOCK_SIZE - 1) / BLOCK_SIZE;

    int availableBlocks = 0;      // whether enough free blocks are available
    FreeBlock *freeTemp = freeHead;
    while(freeTemp != NULL){
        availableBlocks++;
        freeTemp = freeTemp->next;
    }
    if(requiredBlocks > availableBlocks){
        printf("Disk is full! Not enough free blocks\n");
        return; }
    
    temp->blockPointers = malloc(requiredBlocks * sizeof(int));
    if(temp->blockPointers == NULL){
        printf("Block pointer allocation failed\n");
        return;
    }
    temp->blockCount = requiredBlocks;
    temp->contentSize = size;
 
    for(int i = 0; i < requiredBlocks; i++){        //allocating blocks in the freelist from head

        FreeBlock *allocatedBlock = freeHead;
        temp->blockPointers[i] = allocatedBlock->index;
        freeHead = freeHead->next;

        if(freeHead != NULL)   freeHead->prev = NULL;
        else    freeTail = NULL;
        free(allocatedBlock); }
    
    for(int i = 0; i < requiredBlocks; i++){          // Copying contents into virtual disk blocks
        int offset = i * BLOCK_SIZE;
        int remaining = size - offset;
        int bytesToCopy;

        if(remaining > BLOCK_SIZE)
            bytesToCopy = BLOCK_SIZE;
        else
            bytesToCopy = remaining;

        memcpy(virtualdisk[temp->blockPointers[i]], content + offset, bytesToCopy);
    }
}

void readFile(char filename[], unsigned char virtualdisk[NUM_BLOCKS][BLOCK_SIZE]){     // fun to read contents in a file
    FileNode *file = findNode(cwd, filename);
    if(file == NULL){
        printf("File not found\n");
        return;
    }
    if(file->type != FILE_TYPE){
        printf("Cannot read a directory\n");
        return;
    }
    if(file->contentSize == 0){
        printf("File is empty, nothing to read\n");
        return;
    }
    printf("\nContent of %s:\n", filename);

    int bytesRead = 0;
    for(int i = 0; i < file->blockCount; i++){

        int blockIndex = file->blockPointers[i];
        int bytesToRead = file->contentSize - bytesRead;

        if(bytesToRead > BLOCK_SIZE){
            bytesToRead = BLOCK_SIZE;
        }
        fwrite(virtualdisk[blockIndex], 1, bytesToRead, stdout);
        bytesRead += bytesToRead;
    }
    printf("\n");
}

void deleteFile(char filename[],unsigned char virtualdisk[NUM_BLOCKS][BLOCK_SIZE]){    // fun to delete a file
    FileNode *file = findNode(cwd, filename);
    if(file == NULL){
        printf("File not found \n");
        return;
    }
    if(file->type != FILE_TYPE){
        printf("Cannot delete a directory using deleteFile \n");
        return;
    }
    FreeBlock *newHead = NULL;
    FreeBlock *newTail = NULL;

    for(int i = 0; i < file->blockCount; i++){

        FreeBlock *newnode = malloc(sizeof(FreeBlock));
        if(newnode == NULL){
            printf("Memory allocation failed!\n");
            while(newHead != NULL){     // Freeing temporary nodes if allocation fails            
                FreeBlock *temp = newHead;
                newHead = newHead->next;
                free(temp);
            }
            return;
        }
        newnode->index = file->blockPointers[i];
        newnode->next = NULL;
        newnode->prev = newTail;
        if(newHead == NULL) newHead = newnode;
        else    { newTail->next = newnode;}
        newTail = newnode;
    }

    if(newHead != NULL) {   // Appending returned blocks to freeblock list
        if(freeHead == NULL){
            freeHead = newHead;
            freeTail = newTail;}
        else{
            freeTail->next = newHead;
            newHead->prev = freeTail;
            freeTail = newTail;}   }
    
    for(int i = 0; i < file->blockCount; i++){   //  Clearing the released disk blocks
        int blockIndex = file->blockPointers[i];
        memset(virtualdisk[blockIndex], 0, BLOCK_SIZE);
    }

    FileNode *prev = file;   // Removing file from circular linked list
    while(prev->next != file){
        prev = prev->next;
    }
    if(prev == file){       
        cwd->child = NULL;
    }
    else{
        prev->next = file->next;
        if(cwd->child == file){
            cwd->child = file->next;
        }
    }
    free(file->blockPointers);
    free(file);
    printf("File deleted successfully\n");
}

void df(){         // fun to tell the disk usage
    int freeBlocks = 0;
    int usedBlocks = 0;
    FreeBlock *temp = freeHead;
    while(temp != NULL){
        freeBlocks++;
        temp = temp->next;
    }
    usedBlocks = NUM_BLOCKS - freeBlocks;

    float diskUsage = ((float)usedBlocks / NUM_BLOCKS) * 100;

    printf("\n-- Disk Usage --\n");
    printf("Total Blocks : %d\n", NUM_BLOCKS);
    printf("Used Blocks  : %d\n", usedBlocks);
    printf("Free Blocks  : %d\n", freeBlocks);
    printf("Disk Usage   : %.2f %%\n", diskUsage);
}

void freeDirectoryTree(FileNode *dir){    // frees the directories in the list
    if(dir == NULL)  return;
    if(dir->child != NULL){
        FileNode *first = dir->child;
        FileNode *current = first;
        do{
            FileNode *next = current->next;
            if(current->type == DIR_TYPE){
                freeDirectoryTree(current);
            }
            else{
                free(current->blockPointers);
                free(current);
            }
            current = next;
        } while(current != first);
    }
    free(dir);
}
void cleanup(){      // function to free all the memory
    freeDirectoryTree(root);
    root = NULL;
    cwd = NULL;

    FreeBlock *temp = freeHead;
    while(temp != NULL){
        FreeBlock *next = temp->next;
        free(temp);
        temp = next;
    }
    freeHead = NULL;
    freeTail = NULL;
    printf("All dynamically allocated memory released!\n");
}

int main(){
    unsigned char virtualdisk[NUM_BLOCKS][BLOCK_SIZE];

    if(initializeFreeList() != 0) {
        printf("Initialization of freeblock list failed\n");
        return 1;}

    createRootDirectory();
    if(root == NULL){
    printf("\n Root Directory not created\n");
    return 1;  }

    cwd = root;
    char command[100];
    char dirname[51];
    while(1){ 
        printf("%s > ", cwd->name);
        printf("\nenter command: ");
        scanf("%99s", command);

        if(strcmp(command, "mkdir") == 0){
            printf("Enter directory name: ");
            scanf("%50s", dirname);
            mkdir(dirname);
        }
        else if(strcmp(command, "rmdir") == 0){
            printf("Enter directory name: ");
            scanf("%50s", dirname);
            rmdir(dirname);
        }
        else if(strcmp(command, "ls") == 0){
            ls();
        }
        else if(strcmp(command, "cd") == 0) {
            printf("Enter directory name: ");
            scanf("%50s", dirname);
            cd(dirname);
        }
        else if(strcmp(command, "pwd") == 0){
            pwd();
        }
        else if(strcmp(command, "create") == 0){
            printf("Enter filename: ");
            scanf("%50s", dirname);
            create(dirname);
        }
        else if(strcmp(command, "write") == 0){
            char filename[51];
            char content[10000];

            printf("Enter filename: ");
            scanf("%50s", filename);
            printf("Enter content: ");
            scanf(" %9999[^\n]", content);
            writeFile(filename, content, virtualdisk);
        }
        else if(strcmp(command, "read") == 0){
            char filename[51];

            printf("Enter filename: ");
            scanf("%50s", filename);
            readFile(filename, virtualdisk);
        }
        else if(strcmp(command, "delete") == 0){
            char filename[51];

            printf("Enter filename: ");
            scanf("%50s", filename);
            deleteFile(filename, virtualdisk);
        }
        else if(strcmp(command, "df") == 0){
            df();
        }
        else if(strcmp(command, "exit") == 0){
            cleanup();
            printf("Memory released. Exiting program...\n");
            break;
        }
        else { printf("Invalid command\n");}
    }
    return 0;
}

