#include <stdio.h>

char* isValid(char* s) {   // function to check if the string is valid or not
    int freq[26] ={0};
    int count[100001] = {0};
    int i =0;
    int maxfreq = 0;
    
    for(i=0; s[i] !='\0'; i++){  // counting freq of each character
        freq[s[i]- 'a']++;
    }
    for(i=0; i<26;i++){
        if (freq[i]>maxfreq){
        maxfreq = freq[i];}
        
        if (freq[i]>0){     // counting the how many times each ch has a freq
        count[freq[i]]++;}
    }
    int diffFreq = 0;                     // counting distinct freq values
    for (i = 1; i <= maxfreq; i++) {
        if (count[i] > 0) {
            diffFreq++;
        } }
        
    if (diffFreq == 1){         // if all freq are equal of all ch
    return "YES";}
    
    
    if (count[1]==1){           //  counting if any ch occurs only once
        int otherFreq = 0;
        for (i=2; i<=maxfreq;i++){
            if(count[i]>0)
            otherFreq++;
        }
        if (otherFreq == 1){
            return "YES";
        }   
        }
    
    if ( (maxfreq>1) &&(count[maxfreq]==1) &&(count[maxfreq -1]>0) ){      //checking if the highest freq can be reduced by 1
        int otherFreq = 0;
        for(i = 1;i<maxfreq; i++){
            if (count[i]>0){
                otherFreq++; }    
        }
        if (otherFreq == 1){
            return "YES"; }    
    } 
    return "NO"; 
}
     

int main() {
    char s[100001];         // since the constarint was s<=10**5

    scanf("%100000s", s);

    char* result = isValid(s);

    printf("%s\n", result);

    return 0;
}

