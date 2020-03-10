/*CPU Scheduling Algorithm - Round Robin (It is preemtive algorithm).   */ 
#include<stdio.h> 
//#include<conio.h> 
#define MAX 100 
void gantt(int bt[MAX],int tq); 
void wtime(int jj[MAX],int gt[MAX]); 
void tatime(int jj[MAX],int gt[MAX]); 
int job[MAX],bt[MAX],jj[MAX],wt[MAX],tat[MAX],gt[MAX]; 
int n,i,j,mina,minb,minj,tq,cnt; 
float avgw,avgt; 
 void main() 
    { 
    //clrscr(); 
    printf("\n Enter the total number of jobs : "); 
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
    printf("\n Enter the TIME QUANTUM :"); 
    scanf("%d",&tq); 
    //clrscr(); 
    printf("\n  Round Robin Job Scheduling is \n"); 
    printf("\n  -------------------------------"); 
    printf("\n  |\tJOBS\t |  BURST TIME  |"); 
    printf("\n  -------------------------------"); 
           for(i=0;i<n;i++) 
    { 
        printf("\n  |\t%d\t |\t%d\t|",job[i],bt[i]); 
    } 
    printf("\n  -------------------------------"); 
    gantt(bt,tq); 
    //getch(); 
   } 
 void gantt(int bt[MAX],int tq) 
    { 
    int flag=0,k=0,temp; 
    cnt=0; 
    i=-1; 
    while(flag==0) 
    { 
        i++; 
        k=0; 
        if(i==0) 
        { 
            gt[cnt]=0; 
            cnt++; 
        } 
        else 
        { 
            if(bt[i-1]!=0) 
            { 
                temp=bt[i-1]; 
                if(temp>tq) 
                { 
                    gt[cnt]=gt[cnt-1]+tq; 
                    bt[i-1]=bt[i-1]-tq; 
                } 
                else 
                { 
                    gt[cnt]=gt[cnt-1]+bt[i-1]; 
                    bt[i-1]=bt[i-1]-temp; 
                } 
                jj[cnt]=job[i-1]; 
                cnt++; 
            } 
            if(i==n) 
                i=0; 
                                 for(j=0;j<n;j++) 
            { 
                if(bt[j]==0) 
                { 
                    k++; 
                } 
                else 
                { 
                    flag=0; 
                    break; 
                } 
            } 
            if(k==n) 
                flag=1; 
        } 
    } 
    printf("\n\nGantt Chart\n"); 
    printf("---------------------------------------------------------\n"); 
    for(i=1;i<cnt;i++) 
    { 
        printf("|   J%d\t",jj[i]); 
    } 
    printf("|\n"); 
    printf("---------------------------------------------------------\n"); 
    for(i=0;i<cnt;i++) 
    { 
        printf("%d\t",gt[i]); 
    } 
    wtime(jj,gt); 
    tatime(jj,gt); 
 } 
 void wtime(int jj[MAX],int gt[MAX]) 
 { 
    int k=0,temp=0,tot; 
    while(k<=n) 
    { 
        temp=0; 
        for(i=0;i<cnt-1;i++) 
        { 
            if(jj[i+1]==(k+1)) 
            { 
                 tot=gt[i]-temp; 
                wt[k]=wt[k]+tot; 
                temp=gt[i+1]; 
            } 
        } 
        k++; 
    } 
    tot=0; 
    for(i=0;i<n;i++) 
    { 
        tot=tot+wt[i]; 
    } 
    printf("\n\n Total Waiting Time : %d",tot); 
    avgw=(float)tot/n; 
    printf("\n Average Waiting Time : %0.2f",avgw); 
      } 
 void tatime(int jj[MAX],int gt[MAX]) 
   { 
    int k=0,tot; 
    while(k<=n) 
    { 
        for(i=0;i<cnt-1;i++) 
        { 
            if(jj[i+1]==(k+1)) 
            { 
                tat[k]=gt[i+1]; 
            } 
        } 
        k++; 
    } 
    tot=0; 
    for(i=0;i<n;i++) 
    { 
        tot=tot+tat[i]; 
    } 
    printf("\n\n Total Turn Around Time : %d",tot); 
    avgt=(float)tot/n; 
    printf("\n Average Turn Around Time : %0.2f",avgt); 
}   
/******************** OUTPUT  ************************* 
 Enter the total number of jobs : 3 
 Now enter the BURST TIME : 
 J1 :  11 
 J2 :  12 
 J3 :  13 
 Enter the TIME QUANTUM :3 
  Round Robin Job Scheduling is 
  ------------------------------------------------ 
  |     JOBS     |  BURST TIME  | 
  -------------------------------------------------     
  |     1        |      11        | 
  |     2        |      12        | 
  |     3        |      13        | 
  ------------------------------------------------ 
Gantt Chart 
------------------------------------------------------------------------------------------------------------------------------------------------ 
|   J1  |   J2  |   J3  |   J1  |   J2  |   J3  |   J1  |   J2  |   J3  |   J1 |   J2  |   J3  |   J3  | 
----------------------------------------------------------------------------------------------------------------------------------------------- 
0      3      6       9      12     15      18      21     24     27     29     32    35      36 
 Total Waiting Time : 61 
 Average Waiting Time : 20.33 
 Total Turn Around Time : 97 
 Average Turn Around Time : 32.33   */ 
