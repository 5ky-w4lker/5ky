// Bankers Algorithm

#include<stdio.h> 
//#include<conio.h> 
int max[10][10],need[10][10],allocation[10][10],available[10],work[10],finish[10],request[10]; 
int np,nr,i,j,k,l,m,n,pid; 
int ch,cnt=0; 
void safety(); 
void rr(); 
int main() 
{ 
    //clrscr(); 
    printf("\n Enter the no of processes:"); 
    scanf("%d",&np); 
    printf("\n Enter the no of resources:"); 
    scanf("%d",&nr); 
    printf("\n Enter the max matrix:"); 
    for(i=0;i<np;i++) 
    { 
        for(j=0;j<nr;j++) 
        { 
            scanf("%d",&max[i][j]); 
        } 
    } 
    printf("\n Enter the allocation matrix:"); 
    for(i=0;i<np;i++) 
    { 
        for(j=0;j<nr;j++) 
        { 
            scanf("%d",&allocation[i][j]); 
        } 
    } 
    printf("\n Enter the available matrix:"); 
    for(i=0;i<nr;i++) 
    { 
        scanf("%d",&available[i]); 
    } 
    do 
    { 
        printf("\n\n--------MENU------------"); 
        printf("\n\n1.safety  algo:\n2.resource request:\n3.exit:"); 
        printf("\n\n Enter your choice:"); 
        scanf("%d",&ch); 
        switch(ch) 
        { 
            case 1: safety(); 
                break; 
            case 2: rr(); 
                break; 
        } 
    }while(ch!=3); 
    return 0; 
} 
void safety() 
{ 
    int flag=0; 
    for(i=0;i<nr;i++) 
    { 
        work[i]=available[i]; 
    } 
        printf("\n Need Array is\n"); 
    for(i=0;i<np;i++) 
    { 
        for(j=0;j<nr;j++) 
        { 
            printf(" %d\t\t ", need[i][j]=max[i][j]-allocation[i][j]); 
        } 
          printf("\n\n"); 
    } 
    for(i=0;i<np;i++) 
    { 
        finish[i]=0; 
    } 
    printf("\n\n Process safe sequence is:\n"); 
    algo: 
    for(i=0;i<np;i++) 
    { 
        for(j=0;j<nr;j++) 
        { 
            if(need[i][j]<=work[j]&&finish[i]!=1) 
            { 
                flag=1; 
            } 
            else 
            { 
                flag=0; 
                break; 
            } 
        } 
             if(flag==1) 
             { 
            printf("\n Process P%d is executing",i); 
            finish[i]=1; 
            for(k=0;k<nr;k++) 
            { 
                 work[k]=work[k]+allocation[i][k]; 
            } 
           } 
    } 
    for(i=0;i<np;i++) 
    { 
        if(finish[i]==0) 
        { 
            goto algo; 
        } 
    } 
    printf("\n\n Execution is completed:"); 
        printf("\n\n System is in a safe state. so request can be granted immediately:"); 
} 
void rr() 
{ 
    int flag1=0,flag2=0; 
    int cnt1=0,cnt2=0; 
    printf("\n\n Enter the process id :"); 
    scanf("%d",&pid); 
    printf("\n Enter the request:"); 
    for(i=0;i<nr;i++) 
    { 
        scanf("%d",&request[i]); 
    } 
    for(i=0;i<nr;i++) 
    { 
        if(request[i]<=need[pid][i]) 
        { 
            flag1=1; 
        } 
        else 
        { 
            flag1=0; 
            break; 
        } 
    } 
    if(flag1==0) 
    { 
        printf("\n Request can not be granted...!!!"); 
        exit(0); 
    } 
    for(i=0;i<nr;i++) 
    { 
        if(request[i]<=available[i]) 
        { 
            flag2=1; 
        } 
        else 
        { 
            flag2=0; 
            break; 
        } 
    } 
    if(flag2==0) 
    { 
        printf("\n Process should wait:"); 
        exit(0); 
    } 
    printf("\n Updating matrices:"); 
    for(i=0;i<nr;i++) 
    { 
        available[i]-=request[i]; 
        allocation[pid][i]+=request[i]; 
        need[pid][i]-=request[i]; 
    } 
    printf("\n Applying safety algorithm:"); 
    safety(); 
} 
/* 
kkw-pc88@kkwpc88-HP-dx2480-MT-FN870PA:~$ ./a.out 
 Enter the no of processes:5 
 Enter the no of resources:3 
 Enter the max matrix:7 5 3 
3 2 2 
9 0 2 
2 2 2 
4 3 3 
 Enter the allocation matrix:0 1 0 
2 0 0 
3 0 2 
2 1 1 
0 0 2 
 Enter the available matrix:3 3 2 
--------MENU------------ 
1.safety  algo: 
2.resource request: 
3.exit: 
 Enter your choice:1 
need array 7 need array 4 need array 3  
need array 1 need array 2 need array 2  
need array 6 need array 0 need array 0  
need array 0 need array 1 need array 1  
need array 4 need array 3 need array 1  
 Process safe sequence is: 
 Process P1 is executing 
 Process P3 is executing 
 Process P4 is executing 
 Process P0 is executing 
 Process P2 is executing 
 Execution is completed: 
--------MENU------------ 
1.safety  algo: 
2.resource request: 
3.exit: 
 Enter your choice:2 
 Enter the process id :1 
 Enter the request:1 0 2 
 Updating matrices: 
 Applying safety algorithm: 
need array 7 need array 4 need array 3  
need array 0 need array 2 need array 0  
need array 6 need array 0 need array 0  
need array 0 need array 1 need array 1  
need array 4 need array 3 need array 1  
 Process safe sequence is: 
 Process P1 is executing 
 Process P3 is executing 
 Process P4 is executing 
 Process P0 is executing 
 Process P2 is executing 
 Execution is completed: 
--------MENU------------ 
1.safety  algo: 
2.resource request: 
3.exit: 
 Enter your choice:3 
*/ 
