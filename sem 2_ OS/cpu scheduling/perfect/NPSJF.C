/* Simulation of Non Preemptive SJF CPU Scheduling Algorithm
                                                 */
#include<stdio.h>
#include<conio.h>
#include<process.h>
#include<time.h>
#include <alloc.h>
#include <stdlib.h>

struct proc_info
{
  int cpub;
  int atime;
  int inrq;
} proc[20];

struct gantt_chart
{ int pid;
  int stime;
  int etime;
 } gchart[20];

 struct rqnode
 { int pid;
   struct rqnode *link;
 } *first, *curr, *prev, *last;

int n,i,ctime,front=-1,rear=-1,gi=0;
int wtime[20],ttime[20],flag[20];

void get_procs();
void start_exec();
void execute_proc(int p);
int finished_procs();
void print_gchart();
void find_times();

void main()
{  clrscr();
  get_procs();
  ctime=0;
  start_exec();
  print_gchart();
  find_times();

}//main

void get_procs()
{ printf("\nHow many processes: "); scanf("%d",&n);
  printf("\nPID\tCPUB\tA.TIME\n");
  for (i=0; i<n; i++)
  { printf("%d\t",i);
	scanf("%d%d",&proc[i].cpub,&proc[i].atime);
	proc[i].inrq=0;
   }

}//get_proc

void start_exec()
{ int p;
  first=NULL;
 while (!finished_procs())
 { //add arrived processes for exec in ready queue
   last=first;
   while(last->link!=NULL) last=last->link;
  for (i=0; i<n; i++)
	if (proc[i].cpub!=0 && proc[i].atime<=ctime &&proc[i].inrq==0)
	 { curr=(struct rqnode *)malloc(sizeof(struct rqnode));
	   curr->pid=i; curr->link=NULL; proc[i].inrq=1;
	   if (first==NULL)
	   { first=curr;
		 last=curr;
	   }
	   else
		 last->link=curr;
		last=curr;

	  }//if

  //select shortest process for execution
   p=sel_proc();
  if (p!=-1)
   execute_proc(p);
  else
   ctime++;
 }//while
}//fn

int sel_proc()
{ int p;
  struct rqnode *selp,*pselp;
 if (first==NULL)
   return(-1);
  curr=first;  selp=curr;  pselp=NULL;
  while (curr!=NULL)
  {	if (proc[curr->pid].cpub < proc[selp->pid].cpub)
	 { pselp=prev;
	   selp=curr;
	}
	prev=curr;
	curr=curr->link;
   }
  if (first==selp)
	 first=first->link;
  else
	pselp->link=selp->link;
  p=selp->pid;
  free(selp);
  return(p);
}//sel_proc

void execute_proc(int p)
{ //process p started
  //find wtime
  wtime[p]+=(ctime-proc[p].atime);
  gchart[gi].stime=ctime;
  gchart[gi].pid=p;
  //process p finishes
  proc[p].inrq=0;
  ctime+=proc[p].cpub;
  proc[p].cpub=0;
  gchart[gi].etime=ctime;
  gi++;
  //find ttime
  ttime[p]+=(ctime-proc[p].atime);

  //proc p does io operation for 2 time units
  // It arrives at time ctime+2 with new cpu burst
 if (flag[p]==0)
 {
  proc[p].atime=ctime+2;
  randomize();
  proc[p].cpub=random(10);
  printf("\nProcess %d next cpu burst is %d Arival time %d",p,proc[p].cpub,proc[p].atime);
  flag[p]=1;
 }

}

int finished_procs()
{
  for (i=0;i<n; i++)
   if (proc[i].cpub!=0)
	 return(0);
  return(1);

}

void print_gchart()
{
printf("\nGantt Chart:\n");

 for (i=0; i<gi-1; i++)
  printf("%5d",gchart[i].etime);
  printf("\n");

  for (i=0; i<gi; i++)	printf("|----");

  printf("|\n|");
  for (i=0; i<gi; i++)
	printf("%4d|",gchart[i].pid);
  printf("\n");
   for (i=0; i<gi; i++)
	printf("|----");
  printf("|\n");
  for (i=0;i<gi; i++)
   printf("%d    ",gchart[i].stime);
  printf("%d",gchart[i-1].etime);
}

void find_times()
{ int p;
  int sumwt=0, sumtt=0;
  for (p=0; p<n; p++)
  { ttime[p]+=2; //add iotime 2 into ttime
	sumwt+=wtime[p];
	sumtt+=ttime[p];
  }
  printf("\nPID\tWTIME\tTATIME\n");
  for (p=0; p<n; p++)
  printf("%d\t%d\t%d\n",p,wtime[p],ttime[p]);
  printf("\nAVG WTIME=%.2f\tAVG TTIME=%.2f",(float)sumwt/n,(float)sumtt/n);
  getch();

}


