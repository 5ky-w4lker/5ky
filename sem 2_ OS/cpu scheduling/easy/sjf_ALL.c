//Title : SJF program.
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int process[10],proc1[10],proc[20],cbt[10],arrival[10],
    pri[10],time[10],wait[10],turn[10];
int n,m,i,j,k,ch,type,temp,diff,tq;
float avgw,avgt;
int main()
{   n=avgw=avgt=0;
    for(i=0;i<n;i++)
        time[i] = 0;
  printf("Enter the limit: \n");
  scanf("%d",&n);
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
         printf("Select type 1.Preemptive or 2.Non preemptive:-");
         scanf("%d",&type);
  if(type==1)
  { sort();
    sjf();
  }//if
  else  if(type==2)
        sjf();
  else
         printf("Invalid Option Try Again\n");
         printf("\n\n The Waiting Time of Processes: \n");
   for(i=0;i<n;i++)
    for(j=i+1;j<n;j++)
     if(proc1[i] == proc1[j])
     {  proc1[j] = proc1[j+1];
        n--;
     }//if
   for(i=0;i<n;i++)
   {    printf("Process %d = %d\n",proc1[i],wait[i]);
        avgw+=wait[i];
   }
   printf("\n The Turn Around Time of Processes:\n");
   for(i=0;i<n;i++)
   {    printf("Process %d = %d\n",proc1[i],turn[i]);
        avgt+=turn[i];
   }
   printf("\nThe Average Waiting Time of Processes = %f\n",avgw/n);
   printf("\nThe Average Turn Around Time of Processes = %f\n",avgt/n);
}//main

sort()
{   for(i=0;i<n;i++)
    for(j=i+1;j<n;j++)
    if(arrival[i] > arrival[j])
    {   temp = arrival[i];
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
{   if(type==1)
    {   time[0] = 0;
        for(i=0;i<n;i++)
         {  if(i != (n-1))
            {   diff = arrival[i+1] - arrival[i];
                if(diff >= 0)
                     {  cbt[i] = cbt[i]-diff;
                        if(cbt[i+1] < cbt[i])
                         {
                            time[k+1] = time[k] + diff;
                              k++;
                                proc[i] = process[i];
                           }//if
                           else
                            {
                            time[k+1] = time[k] + cbt[i] + diff;
                            cbt[i] = 0;
                            proc[i] = process[i];
                            k++;
     }    }     }   }//for
    m = n+1;
    for(j=0;j<m-1;j++)
    for(i=j;i<n;i++)
    if(cbt[i] == 0)
    {   proc[k+1] = process[i+1];
        process[i] = process[i+1];
        cbt[i] = cbt[i+1];
        cbt[i+1] = 0;
        m = m - 1;
      }//if
    for(i=0;i<n-1;i++)      //sort on cbt
     for(j=i+1;j<n-1;j++)
      if(cbt[i] > cbt[j] && cbt[j] != 0)
      {temp = process[i];
       process[i] = process[j];
       process[j] = temp;
       temp = cbt[i];
       cbt[i] = cbt[j];
       cbt[j] = temp;
      }//if
      for(i=0;i<m;i++)        //calculate remaining time
       for(j=0;j<m;j++)
       {    if(cbt[j] == 0)
	        {
	        process[j] = process[j+1];
	        cbt[j] = cbt[j+1];
	        cbt[j+1] = 0;
	        m--;
	   }//if
	if(cbt[j] != 0)
	{   time[k+1] = time[k] + cbt[j];
	    cbt[j] = 0;
	    proc[k] = process[j];
	     k++;
	 }//if
}//for
       for(i=0;i<k;i++)
       {
	    process[i] = proc[i];
	    proc1[i] = proc[i];
       }//for
       print();      
       m = k;    //calculate waiting & turn around time
       for(j=m-1;j>=0;j--)
	    for(i=j-1;i>=0;i--)
	    if(proc[j] == proc[i])
	    {
	    wait[j] = time[j] - time[i+1];
	    turn[j] = time[j+1];
	    m = i;
	    }//if
	    else
	    {   wait[j] = time[j];
	         turn[j] = time[j+1];
	    }//else
	 for(i=0;i<n;i++)
	 {
	  wait[i] = wait[i] - arrival[i];
	  turn[i] = turn[i] - arrival[i];
	 }//for
	 for(i=0;i<k;i++)
	  for(j=i+1;j<k-1;j++)
	   if(proc[i] == proc[j])
	   {
	    proc[i] = proc[j];
	    wait[i] = wait[j];
	    turn[i] = turn[j];
	    proc[j] = proc[j+1];
	    wait[j] = wait[j+1];
	    turn[j] = turn[j+1];
	   }//if
	   proc1[0] = proc[0];
	   j = n;
	   for(i=0;i<n;i++)
	   {
	    if(proc1[i] == proc1[j])
	    {
	     temp = wait[j];
	     wait[i] = temp;
	     temp = turn[j];
	     turn[i] = temp;
	    }//if
	    j--;	   }//for
	   for(i=0;i<k;i++)
	    for(j=i+1;j<k;j++)
	     if(proc[i] != proc[j])
	     {proc1[++m] = proc[j];
	      if(i == k-1)
	       proc1[i] = 0;
	     }//if
	     else
	     k--;
	     n = k;
	    }//if
	    else
	    if(type == 2)
	    {
	     for(i=0;i<n;i++)
	      for(j=i+1;j<n;j++)
	       if(cbt[i] > cbt[j])
	       {
		temp = process[i];
		process[i] = process[j];
		process[j] = temp;
		temp = cbt[i];
		cbt[i] = cbt[j];
		cbt[j] = temp;
	       }//if
	       for(i=0;i<n;i++)
		arrival[i] = 0;
	       m = n + 1;
	       for(i=0;i<m;i++)
		time[i] = time[i-1] + cbt[i-1];
	       k = m-1;
	       print();
	       //waiting & turn around time
	       for(i=0;i<n;i++)
	       {
		wait[i] = time[i] - arrival[i];
		turn[i] = time[i+1] - arrival[i];
	       }//for
	       for(i=0;i<n;i++)
		proc1[i] = process[i];
	      }//if
 return;
}//sjf
print()
{
 printf("\n Gantt Chart is \n");
 for(i=0;i<k;i++)
  printf("   %d\t",process[i]);
 printf("\n");
 for(i=0;i<k+1;i++)
  printf("%d\t",time[i]);
 //getch();
 return;
}
/*****************************output************************** [ty15@localhost jin-sjf & rr]$ cc sjf.c -o sjf.o
 [ty15@localhost jin-sjf & rr]$ ./sjf.o
Enter the limit:  4
Enter processes:  1 2 3 4
Enter CPU Burst Time:  4 1 2 1
Enter Arrival Time:  0 1 2 3
Processes       CPU Burst Time  Arrival Time
1               4               0
2               1               1
3               2               2
4               1               3
Select type 1.Preemptive or 2.Non-preemptive :-  1
 Gantt Chart is 
   1       2       3       4       1
0       1       2       4       5       8
 The Waiting Time of Processes: 
Process 1 = 4
Process 2 = 0
Process 3 = 0
Process 4 = 1
 The Turn Around Time of Processes:
Process 1 = 8
Process 2 = 1
Process 3 = 2
Process 4 = 2
The Average Waiting Time of Processes = 1.250000
The Average Turn Around Time of Processes = 3.250000
*************************************************************/
