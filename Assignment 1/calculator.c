#include<stdio.h>
#include<ctype.h>
#include<string.h>

int isvalidch(char c)             // checks if input ch is invalid
{
    if (isdigit(c))  return 1;           
    if (c=='+' || c=='-' || c=='/' || c=='*')   return 1;    
    if (isspace(c))  return 1;      //isblank only checks the " " but not "\n"

    return 0; }     

int precedence(char c)             // for operator precedence
{
    if (c=='+' || c=='-')  return 1;
    if (c=='*' || c=='/')   return 2;    

    return 0;}

int basicCalc(char c,int a, int b)   // basic add,sub,mul,div
{
    if(c == '+')  return a+b;
    if(c == '-')  return a-b;
    if(c == '*')  return a*b;
    if(c == '/')  return a/b;    // div by zero handled in calc,becoz return 0--will give 0 to calc which will incorrect o/p ,without any return,the calc will still proceed even after error
    return 0;  }

int calc(char expr[])    // checks if the expression is invalid, storing in 2 stacks, checking opr precedence, zero div error, calculating
{
    int i=0;
    int num[50];
    char op[50];
    int Topnum= -1;
    int Topop= -1; 
    int check = 1;        // 1 means next expecting no. ; 0 means next expecting opr

    while(expr[i]!='\0')
    {
        if (isspace(expr[i])){        // skipp the whitespace
        i++;
        continue;}
        
        if(isdigit(expr[i])){         // if there is a no
            
            if (check != 1){
            printf("\nInvalid expression");
             return 0;}

            int n=0;                // to check complete numbers with multidigit before a certain operator
            while(isdigit(expr[i])){
                n = n*10 + (expr[i] - '0');
                i++;
            }
            num[++Topnum]=n;
            check = 0;            
        }
        
        if (expr[i] == '+' || expr[i] == '-' ||expr[i] == '*' || expr[i] == '/')  // if there is an opr
        {
            if (check !=0){
            printf("\n Invalid Expression");
            return 0;}
            
            if (Topop == -1)
            op[++Topop] = expr[i];

            else if (precedence(op[Topop]) >= precedence(expr[i])){            
                    char curr = op[Topop];
                    Topop--;
                    int right = num[Topnum];
                    Topnum--;
                    int left = num[Topnum];
                    Topnum--;
                    if (curr =='/' && right == 0) {printf("\nError division by zero");  return 0;}
                    int result = basicCalc(curr,left,right);
                    num[++Topnum]= result;
                    op[++Topop]= expr[i];
                }

            else{
            op[++Topop] = expr[i];}

            check = 1;
            i++;
            }  
        }

    if (check ==1)                // means at the end num is expected but string ended
    {printf("\nInvalid expression");
    return 0;}

    while (Topop != -1){
        char curr = op[Topop];
        Topop--;
        int right = num[Topnum];
        Topnum--;
        int left = num[Topnum];
        Topnum--;
        if (curr =='/' && right == 0) {printf("\nErorr div by zero"); return 0;}
        int result = basicCalc(curr,left,right);
        num[++Topnum]= result;
        }
    int result = num[Topnum];
    printf("\n Result: %d", result);    
    return 0;
}

int main()
{
    char expr[100]; 
    printf("enter the expresssion:");
    fgets(expr,sizeof(expr),stdin);     // scanf("%s",expr) will not accept the whitespaces

    int n = strlen(expr);     //using sizeof() will give n=100

    for(int i=0;i<n;i++)
    {
        if (isvalidch(expr[i])==0){
            printf("\nInvalid Expression");
            return 0;}
        }
    calc(expr);
    return 0;
    }

