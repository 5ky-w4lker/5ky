/*CPU Scheduling Algorithm- Nonpreemtive SJF*/ 
#include<stdio.h> 
//#include<conio.h> 
#define MAX 100 
void wtime(int gt[MAX],int at[MAX]); 
void ttime(int gt[MAX],int at[MAX]); 
void gantt(int bt[MAX]); 
int job[MAX],bt[MAX],at[MAX],wt[MAX],tat[MAX],gt[MAX]; 
int n,i,j,flag,mina,minb,minj; 
float avgw,avgt; 
void main() 
{ 
    //clrscr(); 
    printf("\n Enter the total number of jobs:"); 
    scanf("%d",&n); 
    for(i=0;i<n;i++) 
    { 
        job[i]=i+1; 
    } 
    printf("\n Now enter the BURST TIME :"); 
    for(i=0;i<n;i++) 
    { 
        printf("\n J%d :  ",i+1); 
        scanf("%d",&bt[i]); 
    } 
    printf("\n Now enter the ARRIVAL TIME :"); 
    for(i=0;i<n;i++) 
    { 
        printf("\n J%d :  ",i+1); 
        scanf("%d",&at[i]); 
    } 
    //clrscr(); 
    printf("\n  Non Premptive Shortest Job Scheduling is \n"); 
    printf("\n  ------------------------------------------------"); 
    printf("\n  |\tJOBS\t |  BURST TIME   |  ARRIVAL TIME |"); 
    printf("\n  ------------------------------------------------"); 
    for(i=0;i<n;i++) 
    { 
        printf("\n  |\t%d\t |\t%d\t |\t%d\t |",job[i],bt[i],at[i]); 
    } 
    printf("\n  ------------------------------------------------"); 
    for(i=0;i<n;i++) 
    { 
        if(at[i]==0) 
            flag=0; 
    } 
    if(flag==0) 
    { 
        for(i=0;i<n-1;i++) 
        { 
            for(j=i+1;j<n;j++) 
            { 
                if(bt[i]>bt[j]) 
                { 
                    minb=bt[i]; 
                    bt[i]=bt[j]; 
                    bt[j]=minb; 
                    minj=job[i]; 
                    job[i]=job[j]; 
                    job[j]=minj; 
                } 
            } 
        } 
        gantt(bt); 
    } 
    printf("\n\n\tGantt Chart\n"); 
    printf("\t--------------------------------------------------\n\t"); 
    for(i=0;i<n;i++) 
    { 
        printf("|   J%d\t",job[i]); 
    } 
    printf("|\n"); 
    printf("\t-------------------------------------------------\n\t"); 
    for(i=0;i<=n;i++) 
    { 
        printf("%d\t",gt[i]); 
    } 
    wtime(gt,at); 
    ttime(gt,at); 
    //getch(); 
} 
void wtime(int gt[MAX],int at[MAX]) 
{ 
    int tot=0; 
    for(i=0;i<n;i++) 
    { 
        wt[i]=gt[i]-at[i]; 
        tot=tot+wt[i]; 
    } 
    avgw=(float)tot/n; 
    printf("\n\n Total : %d",tot); 
    printf("\n Average Waiting Time : %0.2f\n",avgw); 
} 
void ttime(int gt[MAX],int at[MAX]) 
{ 
    int tot=0; 
    for(i=0;i<n;i++) 
    { 
        tat[i]=gt[i+1]-at[i]; 
        tot=tot+tat[i]; 
    } 
    avgt=(float)tot/n; 
    printf("\n\n Total : %d",tot); 
    printf("\n Average Turn Around Time : %0.2f\n",avgt); 
} 
void gantt(int bt[MAX]) 
{ 
    for(i=0;i<=n;i++) 
    { 
        if(i==0) 
            gt[i]=0; 
        else 
        { 
            gt[i]=gt[i-1]+bt[i-1]; 
        } 
    } 
} 
/***********************************OUTPUT*******************/ 
  /*Non Premptive Shortest Job First Job Scheduling is 
  ------------------------------------------------------------------------------ 
  |     JOBS     |  BURST TIME   |  ARRIVAL TIME | 
  ------------------------------------------------------------------------------ 
  |     1        |      4        |      0        | 
  |     2        |      1        |      0        | 
  |     3        |      2        |      0        | 
  |     4        |      1        |      0        | 
  ------------------------------------------------------------------------------------ 
        Gantt Chart 
        ------------------------------------------------- 
        |   J2  |   J4  |   J3  |   J1  | 
        ------------------------------------------------- 
           0       1       2       4       8 
 Total : 7 
 Average Waiting Time : 1.75 
 Total : 15 
 Average Turn Around Time : 3.75         */ 
