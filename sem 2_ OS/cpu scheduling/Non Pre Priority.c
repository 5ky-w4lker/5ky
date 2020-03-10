/* CPU Scheduling Algorithm- Non-Premtive Priority*/
#include<stdio.h>
//#include<conio.h>
#define MAX 100
int tat[MAX],bt[MAX],gt[MAX],pt[MAX],job[MAX];
int i,j,n,k,tot,high,maxp,minp,mj,mp,mb;
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
    printf("\n Now enter the PRIORITY :");
    for(i=0;i<n;i++)
    {
        printf("\n J%d :  ",i+1);
        scanf("%d",&pt[i]);
    }
    printf("\n Enter the highest priority : ");
    scanf("%d",&high);
    //clrscr();
        printf("\n  Considering all Jobs are arrived at 0 \n");
    printf("\n  Non preemptive Priority Job Scheduling is \n");
    printf("\n  ------------------------------------------------");
    printf("\n  |\tJOBS\t |  BURST TIME   |   PRIORITY   |");
    printf("\n  ------------------------------------------------");
    for(i=0;i<n;i++)
{
        printf("\n  |\t%d\t |\t%d\t |\t%d\t|",job[i],bt[i],pt[i]);
    }
    printf("\n  ------------------------------------------------");
    minp=pt[0];
    maxp=pt[0];
    for(i=0;i<n;i++)
    {
        if(minp>pt[i])
        {
            minp=pt[i];
        }
        if(maxp<pt[i])
        {
            maxp=pt[i];
        }
    }
    if(high==minp)
    {
        for(i=0;i<n-1;i++)
        {
            for(j=i+1;j<n;j++)
            {
                if(pt[i]>pt[j])
                {
                    mp=pt[i];
                    pt[i]=pt[j];
                    pt[j]=mp;
                    mj=job[i];
                    job[i]=job[j];
                    job[j]=mj;
                    mb=bt[i];
                    bt[i]=bt[j];
                    bt[j]=mb;
                }
            }
        }
    }
    else
      if(high==maxp)
    {
        for(i=0;i<n-1;i++)
        {
            for(j=i+1;j<n;j++)
            {
                if(pt[i]<pt[j])
                {
                    mp=pt[i];
                    pt[i]=pt[j];
                    pt[j]=mp;
                    mj=job[i];
                    job[i]=job[j];
                    job[j]=mj;
                    mb=bt[i];
                    bt[i]=bt[j];
                    bt[j]=mb;
                }
            }
        }
    }
    for(i=0;i<=n;i++)
    {
        if(i==0)
            gt[i]=0;
        else
        {
            gt[i]=bt[i-1]+gt[i-1];
        }
    }
    printf("\n\n\tGantt Chart\n");
    printf("\t---------------------------------\n\t");
    for(i=0;i<n;i++)
    {
        printf("|   J%d\t",job[i]);
    }
          printf("|\n");
            printf("\t---------------------------------\n\t");
           for(i=0;i<=n;i++)
    {
        printf("%d\t",gt[i]);
    }
    tot=0;
    for(i=0;i<n;i++)
    {
        tot=tot+gt[i];
    }
    avgw=(float)tot/n;
    printf("\n\n Total Waiting Time : %d",tot);
    printf("\n Average Waiting Time : %0.2f",avgw);
    tot=0;
    for(i=0;i<n;i++)
    {
        tot=tot+gt[i+1];
    }
    avgt=(float)tot/n;
    printf("\n\n Total Turn Around Time : %d",tot);
    printf("\n Average Turn Around Time : %0.2f",avgt);
    //getch();
  }
  /********************** OUTPUT  ********************
Enter the total number of jobs : 3
 Now enter the BURST TIME :
 J1 :  11
 J2 :  12
 J3 :  13
 Now enter the PRIORITY :
 J1 :  2
 J2 :  3
 J3 :  4
 Enter the highest priority : 4
  Considering all Jobs are arrived at 0 
  Non preemptive Priority Job Scheduling is 
  -------------------------------------------------------------------------
  |    JOBS     |  BURST TIME  |   PRIORITY  |
  ---------------------------------------------------------------------------
  |    1     |    11     |    2    |
  |    2     |    12     |    3    |
  |    3     |    13     |    4    |
  ------------------------------------------------
    Gantt Chart
    ---------------------------------
    |   J3    |   J2    |   J1    |
    ---------------------------------
    0    13    25    36    
 Total Waiting Time : 38
 Average Waiting Time : 12.67
 Total Turn Around Time : 74
 Average Turn Around Time : 24.67  */
