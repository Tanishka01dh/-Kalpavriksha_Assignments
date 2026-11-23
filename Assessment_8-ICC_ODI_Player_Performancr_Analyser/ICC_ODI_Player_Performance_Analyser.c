#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Players_data.h"

typedef struct PlayerNode{
    Player data;   
    char *currentNewName;  
    float performanceIndex;
    struct PlayerNode *next;
} PlayerNode;

typedef struct{
    int teamId;
    const char *teamName;
    int totalPlayers;
    PlayerNode *batsmen;
    PlayerNode *bowlers;
    PlayerNode *allRounders;
} TeamNode;
TeamNode teamList[10];

typedef struct {
    PlayerNode *node;
    int teamIndex;
} HeapItem;

void initializeTeams(){    // fun to initialize teamnode in teamlist
    for(int i = 0; i< teamCount; i++){    
        teamList[i].teamId = i + 1;
        teamList[i].teamName = teams[i];
        teamList[i].totalPlayers = 0;
        teamList[i].batsmen = NULL;
        teamList[i].bowlers = NULL;
        teamList[i].allRounders = NULL;
    }
}

float calculatePerformanceIndex(PlayerNode *player){    // fun to calc the performance index
    float performanceIndex = 0;

    if(strcmp(player->data.role, "Batsman") == 0){
        performanceIndex = (player->data.battingAverage * player->data.strikeRate) / 100;
    }
    else if(strcmp(player->data.role, "Bowler") == 0){
        performanceIndex = (player->data.wickets * 2) + (100 - player->data.economyRate);
    }
    else if(strcmp(player->data.role, "All-rounder") == 0){
        performanceIndex = ((player->data.battingAverage * player->data.strikeRate) / 100) +(player->data.wickets * 2);
    }
    return performanceIndex;
}

void insertSorted(PlayerNode **head, PlayerNode *newNode){     // fun to insert playernode in descending order in the list
    PlayerNode *temp;
     
    if(*head == NULL || newNode->performanceIndex > (*head)->performanceIndex) {  // if List is empty Or new player has the highest PI
        newNode->next = *head;
        *head = newNode;
        return;
    }
    temp = *head;     //adding new player at the end/correct position
    while(temp->next != NULL && temp->next->performanceIndex >= newNode->performanceIndex) {
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}
int BinarysearchTeam(const char  teamName[]){  // fun for binary search of teams
    int low = 0;
    int high = teamCount - 1;
    int mid;
    while(low <= high){
        mid = (low + high) / 2;

        if(strcmp(teams[mid], teamName) == 0){
            return mid;
        }
        else if(strcmp(teams[mid], teamName) < 0){
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }
    return -1;
}

void initializePlayers(){   // fun to initialize the players in linkedlist
    int teamIndex;

    for(int i = 0; i < playerCount; i++){   
        teamIndex = BinarysearchTeam(players[i].team);
        if(teamIndex == -1) {continue;}

        PlayerNode *newNode;
        newNode = malloc(sizeof(PlayerNode));
        if(newNode == NULL){
            printf("Memory allocation failed!\n");
            return;
        }
        newNode->data = players[i];

        newNode->currentNewName = malloc(strlen(players[i].name) + 1);
        if(newNode->currentNewName == NULL){
            printf("Memory allocation failed!\n");
            free(newNode);
            return;
        }
        strcpy(newNode->currentNewName, players[i].name);
        newNode->data.name = newNode->currentNewName;
        newNode->performanceIndex = calculatePerformanceIndex(newNode);
        newNode->next = NULL;

        if(strcmp(players[i].role, "Batsman") == 0){
            insertSorted(&teamList[teamIndex].batsmen, newNode);
        }
        else if(strcmp(players[i].role, "Bowler") == 0){
            insertSorted(&teamList[teamIndex].bowlers, newNode);
        }
        else if(strcmp(players[i].role, "All-rounder") == 0) {
            insertSorted(&teamList[teamIndex].allRounders, newNode);
        }
        else{
            free(newNode->currentNewName);
            free(newNode);
            continue;
        }
        teamList[teamIndex].totalPlayers++;      
    }
}

void addPlayer(){    // fun to add new player
    Player newPlayer;
    int teamIndex;
    char teamName[50];
    int roleChoice;

    char *playerName = malloc(100 * sizeof(char));
    if(playerName == NULL){
        printf("Memory allocation failed!\n");
        return;
    }

    printf("\nEnter Player ID: ");
    scanf("%d", &newPlayer.id);
    printf("Enter Player Name: ");
    scanf(" %99[^\n]", playerName);
    printf("Enter Team Name: ");
    scanf(" %49[^\n]", teamName);

    teamIndex = BinarysearchTeam(teamName);
    if(teamIndex == -1){
        printf("Team not found!\n");
        free(playerName);
        return;
    }

    printf("\nSelect Player Role:\n");
    printf("1. Batsman\n");
    printf("2. Bowler\n");
    printf("3. All-rounder\n");
    printf("Enter your choice: ");
    scanf("%d", &roleChoice);

    if(roleChoice == 1){
        newPlayer.role = "Batsman";
    }
    else if(roleChoice == 2){
        newPlayer.role = "Bowler";
    }
    else if(roleChoice == 3){
        newPlayer.role = "All-rounder";
    }
    else{
        printf("Invalid role!\n");
        free(playerName);
        return;
    }

    printf("Enter Total Runs: ");
    scanf("%d", &newPlayer.totalRuns);
    printf("Enter Batting Average: ");
    scanf("%f", &newPlayer.battingAverage);
    printf("Enter Strike Rate: ");
    scanf("%f", &newPlayer.strikeRate);
    printf("Enter Wickets: ");
    scanf("%d", &newPlayer.wickets);
    printf("Enter Economy Rate: ");
    scanf("%f", &newPlayer.economyRate);

    PlayerNode *newNode;     // Allocate memory for new player node
    newNode = malloc(sizeof(PlayerNode));
    if(newNode == NULL){
        printf("Memory allocation failed!\n");
        free(playerName);
        return;
    }

    newPlayer.team = teams[teamIndex];

    newPlayer.name = playerName;
    newNode->data = newPlayer;
    newNode->currentNewName = playerName;

    newNode->performanceIndex = calculatePerformanceIndex(newNode);
    newNode->next = NULL;

    if(roleChoice == 1){      // Inserting into the correct sorted role list
        insertSorted(&teamList[teamIndex].batsmen, newNode);
    }
    else if(roleChoice == 2){
        insertSorted(&teamList[teamIndex].bowlers, newNode);
    }
    else{
        insertSorted(&teamList[teamIndex].allRounders, newNode);
    }

    teamList[teamIndex].totalPlayers++;
    printf("\nPlayer added successfully!\n");
}

void displayTeamPlayers(){    // fun to display indivisual team players
    int teamId;
    int teamIndex = -1;
    float totalStrikeRate = 0;
    int count = 0;
    int battingCount = 0;
    PlayerNode *temp;

    printf("\nEnter Team ID: ");
    scanf("%d", &teamId);

    for(int i = 0; i < teamCount; i++){
        if(teamList[i].teamId == teamId){
            teamIndex = i;
            break;
        }
    }
    if(teamIndex == -1){
        printf("Invalid Team ID!\n");
        return;
    }

    printf("\nPlayers of Team %s:\n", teamList[teamIndex].teamName);

    printf("====================================================================================\n");
    printf("%-5s %-20s %-15s %-7s %-7s %-7s %-7s %-7s %-10s\n",  "ID", "Name", "Role", "Runs", "Avg", "SR", "Wkts", "ER", "Perf.Index");
    printf("====================================================================================\n");

    temp = teamList[teamIndex].batsmen;    // Displaying batsmen
    while(temp != NULL){
        printf("%-5d %-20s %-15s %-7d %-7.1f %-7.1f %-7d %-7.1f %-10.2f\n",
               temp->data.id,
               temp->data.name,
               temp->data.role,
               temp->data.totalRuns,
               temp->data.battingAverage,
               temp->data.strikeRate,
               temp->data.wickets,
               temp->data.economyRate,
               temp->performanceIndex);

        totalStrikeRate += temp->data.strikeRate;
        count++;
        battingCount++;
        temp = temp->next;
    }

    temp = teamList[teamIndex].bowlers;       // Display bowlers
    while(temp != NULL){
        printf("%-5d %-20s %-15s %-7d %-7.1f %-7.1f %-7d %-7.1f %-10.2f\n",
               temp->data.id,
               temp->data.name,
               temp->data.role,
               temp->data.totalRuns,
               temp->data.battingAverage,
               temp->data.strikeRate,
               temp->data.wickets,
               temp->data.economyRate,
               temp->performanceIndex);

        count++;
        temp = temp->next;
    }
    temp = teamList[teamIndex].allRounders;       // Display all-rounders
    while(temp != NULL)
    {
        printf("%-5d %-20s %-15s %-7d %-7.1f %-7.1f %-7d %-7.1f %-10.2f\n",
               temp->data.id,
               temp->data.name,
               temp->data.role,
               temp->data.totalRuns,
               temp->data.battingAverage,
               temp->data.strikeRate,
               temp->data.wickets,
               temp->data.economyRate,
               temp->performanceIndex);

        totalStrikeRate += temp->data.strikeRate;
        count++;
        battingCount++;
        temp = temp->next;
    }
    printf("=================================================================================\n");
    printf("Total Players: %d\n", count);
    if(battingCount > 0){
        printf("Average Batting Strike Rate: %.2f\n", totalStrikeRate / battingCount);
    }
    else{
        printf("Average Batting Strike Rate: 0.00\n");
    }
}

void displayTeamsByStrikeRate(){    // function to display teams in descending by their avg strike rate
    float totalStrikeRate[10] = {0};
    float averageStrikeRate[10] = {0};
    int battingPlayers[10] = {0};
    int order[10];

    for(int i = 0; i < teamCount; i++){  //Calculating average strike rate of each team
        PlayerNode *temp;

        temp = teamList[i].batsmen;    // Traverse batsmen list
        while(temp != NULL){
            totalStrikeRate[i] += temp->data.strikeRate;
            battingPlayers[i]++;
            temp = temp->next;
        }

        temp = teamList[i].allRounders;        // Traverse all-rounders list
        while(temp != NULL){
            totalStrikeRate[i] += temp->data.strikeRate;
            battingPlayers[i]++;
            temp = temp->next;
        }

        if(battingPlayers[i] > 0){
            averageStrikeRate[i] =  totalStrikeRate[i] / battingPlayers[i];     
        }
        order[i] = i;      // Storing original team index
    }

    for(int i = 0; i < teamCount - 1; i++){        //Sorting teams in descending order by bubble sort
        for(int j = 0; j < teamCount - i - 1; j++)
        {
            if(averageStrikeRate[order[j]] < averageStrikeRate[order[j + 1]]){
                int temp = order[j];
                order[j] = order[j + 1];
                order[j + 1] = temp;
            }
        }
    }
    printf("\nTeams sorted by Average Batting Strike Rate:\n");
    printf("----------------------------------------------------\n");
    printf("%-5s %-20s %-15s\n", "ID", "Team Name", "Average SR");
    printf("----------------------------------------------------\n");

    for(int i = 0; i < teamCount; i++){
        int index = order[i];
        printf("%-5d %-20s %-15.2f\n", teamList[index].teamId, teamList[index].teamName, averageStrikeRate[index]);
    }
}

void displayTopKPlayers(){       // displays top k players in a team in a specific role
    int teamId, teamIndex;
    int roleChoice;
    int k, count = 0;

    PlayerNode *temp = NULL;

    printf("\nEnter Team ID: ");
    scanf("%d", &teamId);
    if(teamId < 1 || teamId > teamCount){
        printf("\nInvalid Team ID!\n");
        return;
    }

    teamIndex = BinarysearchTeam(teams[teamId - 1]);
    if(teamIndex == -1){
        printf("\nTeam not found!\n");
        return;
    }

    printf("\nSelect Player Role:\n");
    printf("1. Batsman\n");
    printf("2. Bowler\n");
    printf("3. All-rounder\n");
    printf("Enter your choice: ");
    scanf("%d", &roleChoice);

    if(roleChoice == 1){
        temp = teamList[teamIndex].batsmen;
    }
    else if(roleChoice == 2){
        temp = teamList[teamIndex].bowlers;
    }
    else if(roleChoice == 3){
        temp = teamList[teamIndex].allRounders;
    }
    else{
        printf("\nInvalid role choice!\n");
        return;
    }

    printf("\nEnter K (number of top players): ");
    scanf("%d", &k);
    if(k <= 0){
        printf("\nPlease enter a valid value of K!\n");
        return;
    }

    if(temp == NULL){
        printf("\nNo players found for this role in the selected team!\n");
        return;
    }

    printf("\nTop %d Players:\n", k);
    printf("\n%-8s %-20s %-15s %-12s\n", "ID", "Name", "Role", "Performance");  

    while(temp != NULL && count < k){      
        printf("%-8d %-20s %-15s %-12.2f\n", temp->data.id, temp->data.name, temp->data.role, temp->performanceIndex);

        temp = temp->next;
        count++;
    }
    if(count < k){
        printf("\nOnly %d players are available in this role.\n", count);
    }
}

void insertHeap(HeapItem heap[], int *heapSize, HeapItem item) {     // Function to insert a player into Max Heap

    int i = *heapSize;
    heap[i] = item;
    (*heapSize)++;

    while(i > 0) {   // Move the new element upwards to maintain Max Heap property

        int parent = (i - 1) / 2;
        if(heap[i].node->performanceIndex > heap[parent].node->performanceIndex) {

            HeapItem temp = heap[i];
            heap[i] = heap[parent];
            heap[parent] = temp;
            i = parent;
        }
        else  break;
    }
}
void heapifyDown(HeapItem heap[], int heapSize, int i) {   // Function to maintain Max Heap property after removing maximum element
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < heapSize && heap[left].node->performanceIndex > heap[largest].node->performanceIndex) {
        largest = left;
    }
    if(right < heapSize && heap[right].node->performanceIndex > heap[largest].node->performanceIndex) {
        largest = right;
    }

    if(largest != i) {         // Swap if any child has greater Performance Index
        HeapItem temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;
        heapifyDown(heap, heapSize, largest);
    }
}
HeapItem removeMax(HeapItem heap[], int *heapSize) {     // Function to remove and return the player with maximum Performance Index
    HeapItem maxItem = heap[0];

    heap[0] = heap[*heapSize - 1];
    (*heapSize)--;
  
    if(*heapSize > 0) {   
        heapifyDown(heap, *heapSize, 0);
    }
    return maxItem;
}
void displayAllPlayersByRole() {       // fun to display all the players in all teams by a role

    int roleChoice;
    int heapSize = 0;
    int count = 0;
    const char *roleName;
    PlayerNode *temp;

    HeapItem heap[10];
    HeapItem item;

    printf("\nSelect Player Role:\n");
    printf("1. Batsman\n");
    printf("2. Bowler\n");
    printf("3. All-rounder\n");
    printf("Enter your choice: ");
    scanf("%d", &roleChoice);

    if(roleChoice == 1) {
        roleName = "Batsman";  }
    else if(roleChoice == 2) {
        roleName = "Bowler";  }
    else if(roleChoice == 3) {
        roleName = "All-rounder";  }
    else {
        printf("\nInvalid role choice!\n");
        return;
        }

    for(int i = 0; i < teamCount; i++) {
        if(roleChoice == 1) {
            temp = teamList[i].batsmen;
        }
        else if(roleChoice == 2) {
            temp = teamList[i].bowlers;
        }
        else {
            temp = teamList[i].allRounders;
        }

        if(temp != NULL) {  

            item.node = temp;
            item.teamIndex = i;
            insertHeap(heap, &heapSize, item);
        }
    }

    if(heapSize == 0) {
        printf("\nNo players found for this role!\n");
        return;
    }

    printf("\nAll %s Players Across All Teams:\n", roleName);
    printf("============================================================================================\n");
    printf("%-6s %-20s %-18s %-15s %-7s %-7s %-7s %-7s %-10s\n", "ID", "Name", "Team", "Role", "Runs", "Avg", "SR", "Wkts", "Perf.Index");
    printf("============================================================================================\n");

    while(heapSize > 0) {
        item = removeMax(heap, &heapSize);     // Removing player having the highest PI
        temp = item.node;

        printf("%-6d %-20s %-18s %-15s %-7d %-7.1f %-7.1f %-7d %-10.2f\n",
               temp->data.id,
               temp->data.name,
               teamList[item.teamIndex].teamName,
               temp->data.role,
               temp->data.totalRuns,
               temp->data.battingAverage,
               temp->data.strikeRate,
               temp->data.wickets,
               temp->performanceIndex);
       
        count++;
        temp = temp->next;
        if(temp != NULL) {     // Inserting next player into heap if available

            item.node = temp;
            insertHeap(heap, &heapSize, item);
        }
    }
    printf("============================================================================================\n");
    printf("Total %s Players: %d\n", roleName, count);
}

void freeMemory(){     // fun to free all dynamic memory

    PlayerNode *temp;
    PlayerNode *nextNode;

    for(int i = 0; i < teamCount; i++){

        temp = teamList[i].batsmen;    // free all batsmen
        while(temp != NULL){
            nextNode = temp->next;    
            free(temp->currentNewName);    
            free(temp);               
            temp = nextNode;
        }

        temp = teamList[i].bowlers;     // Free all bowlers 
        while(temp != NULL){
            nextNode = temp->next;
            free(temp->currentNewName);
            free(temp);
            temp = nextNode;
        }

        temp = teamList[i].allRounders;  // free all rounders
        while(temp != NULL){
            nextNode = temp->next;
            free(temp->currentNewName);
            free(temp);
            temp = nextNode;
        }
        teamList[i].batsmen = NULL;
        teamList[i].bowlers = NULL;
        teamList[i].allRounders = NULL;
        teamList[i].totalPlayers = 0;
    }
    printf("\nAll dynamically allocated memory freed successfully!\n");
}

int main(){
    int choice;
    initializeTeams();
    initializePlayers();

    printf("\n================================================\n");
    printf("     ICC ODI PLAYER PERFORMANCE ANALYZER\n");
    printf("=================================================\n");
    printf("1. Add Player to Team\n");
    printf("2. Display Players of a Specific Team\n");
    printf("3. Display Teams by Average Batting Strike Rate\n");
    printf("4. Display Top K Players of a Specific Team by Role\n");
    printf("5. Display All Players of a Specific Role Across Teams\n");
    printf("6. Exit\n");
    do{
        printf("====================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                addPlayer();
                break;

            case 2:
                displayTeamPlayers();
                break;

            case 3:
                displayTeamsByStrikeRate();
                break;

            case 4:
                displayTopKPlayers();
                break;

            case 5:
                displayAllPlayersByRole();
                break;

            case 6:
                printf("Exiting the program...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 6);

    freeMemory();
    return 0;
}

