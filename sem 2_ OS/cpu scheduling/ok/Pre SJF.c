//CPU Scheduling Algorithm- preemptive Shortest Job First(SJF) 
#include <stdio.h> 
#include <stdlib.h> 
//#include <time.h> 
#define MAX 100 
struct process_info 
{ 
  int atime; 
  int cpub; 
} proc[10]; 
int orgatime[10]; 
struct gantt_chart 
{ 
  int procno; 
  int stime; 
  int etime; 
} gchart[30]; 
int i, n, currtime=0, gindex,p, ttime[10], wtime[10], prevp=-1; 
void get_process_input(); 
find_proc_toexec(); 
void print_gantt_chart(); 
finished_procs(); 
void print_times(); 
void gen_next_cpub(); 
void cpub_exec_proc(int p); 
void main() 
{ 
  int etime; 
  //clrscr(); 
  get_process_input(); 
  while (!finished_procs()) 
  { 
     p=find_proc_toexec(); //find Shortest process to execute 
     if (p!=-1) //if process found 
        cpub_exec_proc(p); 
    else currtime++; 
  } 
  gchart[gindex++].etime=currtime; 
  printf("After Excecution of First CPU burst:\n"); 
  print_gantt_chart(); 
  print_times(); 
  //getch(); 
/*  gen_next_cpub(); //generate next cpu burst 
  prevp=-1; 
  while (!finished_procs()) 
  { 
    p=find_proc_toexec(); 
    if (p!=-1) 
       cpub_exec_proc(p); 
    else 
       currtime++; 
  }*/ 
  gchart[gindex++].etime=currtime; 
/*  printf("\nAfter Excecution of Next CPU burst:\n"); 
  print_gantt_chart(); 
  print_times(); 
  //getch(); 
  */ 
} 
void get_process_input() 
{ 
  int pno; 
  printf("\nHow many processes : "); 
  scanf("%d",&n); 
  printf("Proc   Arrival   First CPU   \n"); 
  printf("No.    Time      Burst        \n"); 
  pno=1; 
  for(i=0; i<n; i++) 
  { 
    printf("\n%d",pno++); 
    scanf("%d%d",&proc[i].atime,&proc[i].cpub); 
    orgatime[i]=proc[i].atime; 
  } 
} 
find_proc_toexec() 
{ 
  int mincpub=11, selproc=-1; 
   for (i=0; i<n; i++) 
   { if (proc[i].cpub!=0 && proc[i].atime<=currtime && proc[i].cpub<mincpub) 
     { 
       mincpub=proc[i].cpub; 
       selproc=i; 
     } 
   } 
  return selproc; 
} 
void cpub_exec_proc(int p) 
{       int etime; 
  //submit proc p for execution 
   if (prevp!=p) 
   { 
     if (prevp!=-1) gchart[gindex++].etime=currtime; 
     wtime[p]+=(currtime-getetime(p)); 
     gchart[gindex].procno=p; 
     gchart[gindex].stime=currtime; 
     prevp=p; 
   } 
  currtime++; 
  proc[p].cpub-=1; //proc p cpub decr by 1 
  //ttime[p]=ttime[p]+1; 
  if (proc[p].cpub==0) 
  { 
    proc[p].atime=currtime+2; //next cpu burst arrival time is currtime+iotime 
    ttime[p]=currtime-orgatime[p]; 
  } 
} 
finished_procs() 
{ 
  for (i=0; i<n; i++) 
   if (proc[i].cpub!=0) 
     return (0); 
  return (1); 
} 
void gen_next_cpub() 
{ 
//  randomize(); 
  printf("\n"); 
  printf("\nProc.No.\tNext CPU Burst"); 
  for (i=0; i<n; i++) 
   { 
     proc[i].cpub=rand()%10; 
     printf("\n%d\t\t%d",i,proc[i].cpub); 
   } 
} 
getetime(int p) 
{ 
   for (i=gindex-1; i>=0; i--) 
     if (gchart[i].procno==p) 
          return(gchart[i].etime); 
  return proc[p].atime; 
} 
void print_gantt_chart() 
{ 
  printf("\n|----|----|----|----|----|----|----|----|----------\n"); 
  printf("|"); 
  for (i=1; i<gindex; i++) 
  { 
    printf(" %d  |",gchart[i].procno); 
  } 
  printf("\n|----|----|----|----|----|----|----|----|------------\n"); 
  printf("%d",gchart[0].stime); 
  for (i=0; i<gindex; i++) 
  { 
    printf("%5d",gchart[i].etime); 
  } 
} 
void print_times() 
{ 
   int totwtime=0,totttime=0; 
  printf("\nProc   Waiting   TurnAround\n"); 
  printf("No.    Time      Time       \n"); 
  for (i=0; i<n; i++) 
   { 
    printf("%d\t%d\t%d\n",i,wtime[i],ttime[i]); 
    totwtime+=wtime[i]; 
    totttime+=ttime[i]; 
   } 
   printf("\nAverage Waiting Time = %.2f",(float)totwtime/n); 
   printf("\nAverage Turnaround Time = %.2f",(float)totttime/n); 
} 
/*********************OUTPUT************************************/ 
/* 
How many processes : 5 
Proc   Arrival   First CPU    
No.    Time      Burst         
P0       1          5 
P1       0          3 
P2       2          2 
P3       3          4 
P4       2          8 
After Excecution of First CPU burst: 
|------|------|------|------|-------| 
| P1 | P2 | P3 | P0| P4 | 
|------|------|------|------|-------| 
0   3    5    9   14   22 
Proc   Waiting   TurnAround 
No.    Time      Time        
0    8    13 
1    0    3 
2    1    3 
3    2    6 
4    12    20 
Average Waiting Time = 4.60 
Average Turnaround Time = 9.00 */ 
