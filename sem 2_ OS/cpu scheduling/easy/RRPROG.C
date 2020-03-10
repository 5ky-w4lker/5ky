//Title : Program for Round Robin
#include<stdio.h>
//#include<conio.h>
#include<stdlib.h>
#include<string.h>
int process[10],proc1[10],proc[20],cbt[10],arrival[10],ft[10],
pri[10],time[10],wait[10],turn[10];
int n,m,i,j,k,ch,type,temp,diff,tq,timeqtm;
float avgw,avgt;
main()
{
 //clrscr();
 n=avgw=avgt=0;
 for(i=0;i<n;i++)
  time[i] = 0;
  printf("Enter the limit: \n");
  scanf("%d",&n);  
printf("Enter the timequantum: \n");
  scanf("%d",&timeqtm);
  printf("Enter processes: \n");
  for(i=0;i<n;i++)
   scanf("%d",&process[i]);
  printf("Enter CPU Burst Time: \n");
  for(i=0;i<n;i++)
   scanf("%d",&cbt[i]);
  printf("Enter Arrival Time: \n");
  for(i=0;i<n;i++)
   scanf("%d",&arrival[i]);
   time[0] = 0;
  printf("Processes\tCPU Burst Time\tArrival Time\n");
  for(i=0;i<n;i++)
  printf("%d\t\t%d\t\t%d\n",process[i],cbt[i],arrival[i]);
  for(i=0;i<n;i++)
   proc1[i] = process[i];
  
  
   sort();
   sjf();
 
  
//=============
 for(i=0;i<n;i++)
  for(j=i+1;j<n;j++)
   if(proc[i] > proc[j])
   {
    temp = wait[i];
    wait[i] = wait[j];
    wait[j] = temp;
    temp = turn[i];
    turn[i] = turn[j];
    turn[j] = temp;
    temp = arrival[i];
    arrival[i] = arrival[j];
    arrival[j] = temp;
    temp = proc[i];
    proc[i] = proc[j];
    proc[j] = temp;
    temp = cbt[i];
    cbt[i] = cbt[j];
    cbt[j] = temp;
    temp = pri[i];
    pri[i] = pri[j];
    pri[j] = temp;
   }//if

//==============
   for(i=0;i<n;i++)

   {
   printf("Process %d = %d\n",proc1[i],wait[i]);
   avgw+=wait[i];
   }
   printf("\n The Turn Around Time of Processes:\n");
   for(i=0;i<n;i++)
 
  {  
    printf("Process %d = %d\n",proc1[i],turn[i]);
    avgt+=turn[i];
   }
   printf("\nThe Average Waiting Time of Processes = %f\n",avgw/n);
   printf("\nThe Average Turn Around Time of Processes = %f\n",avgt/n);
 //getch();
return ;}//main

sort()
{
 for(i=0;i<n;i++)
  for(j=i+1;j<n;j++)
   if(arrival[i] > arrival[j])
   {
    temp = arrival[i];
    arrival[i] = arrival[j];
    arrival[j] = temp;
    temp = process[i];
    process[i] = process[j];
    process[j] = temp;
    temp = cbt[i];
    cbt[i] = cbt[j];
    cbt[j] = temp;
    temp = pri[i];
    pri[i] = pri[j];
    pri[j] = temp;
   }//if
   return;
}//sort

sjf()
{
 
  time[0] = 0;
  for(i=0;i<n;i++)
  {
     for(j=0;j<n;j++)
     {

     if(cbt[j]!=0)
      {
       if(cbt[j]>timeqtm)
      {
      time[k+1] = time[k] + timeqtm;
	proc[k]=process[j];      
	
	ft[proc[k]]=time[k+1];
	
	k++;
      cbt[j] = cbt[j]-timeqtm;
      
     }//if
     else
     {
      time[k+1] = time[k] + cbt[j];
     proc[k]=process[j]; 
	 	ft[proc[k]]=time[k+1];
     cbt[j] = 0;
      k++;
     
     }//else
    }//if
   }//for
  }//for
  
       print();
       //calculate waiting & turn around time
       for(i=0;i<n;i++)
  {
	turn[i]=ft[i]-at[i];
	avgt+=turn[i];
	
	wait[i]=tat[i]-cbt[i];
		avgw+=wait[i];
	
	    }
	     
 return;
}
print()
{
 printf("\n Gantt Chart is \n");
 for(i=0;i<k;i++)
  printf("   %d\t",proc[i]);
 printf("\n");
 for(i=0;i<k+1;i++)
  printf("%d\t",time[i]);
  
   for(i=0;i<k;i++)
  printf("   %d\t",pri[i]);
 //getch();
 return;
}//sjf




/*****************************output***********************************************

[ty15@localhost jin-sjf & rr]$ cc rr.c -o rr.o
[ty15@localhost jin-sjf & rr]$ ./rr.o
Enter the limit: 
3
Enter the timequantum: 
2
Enter processes: 
1 2 3
Enter CPU Burst Time: 
3 2 5
Enter Arrival Time: 
1 2 0
Processes       CPU Burst Time  Arrival Time
1               3               1
2               2               2
3               5               0

 Gantt Chart is 
   3       1       2       3       1       3
0       2       4       6       8       9       10

 The Waiting Time of Processes: 
Process 1 = 4
Process 2 = 8
Process 3 = 2

 The Turn Around Time of Processes:
Process 1 = 8
Process 2 = 9
Process 3 = 4

The Average Waiting Time of Processes = 4.666667

The Average Turn Around Time of Processes = 7.000000
[ty15@localhost jin-sjf & rr]$ 
 

***********************************************************************************/
