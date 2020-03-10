// program for  FCFS(First Come First Serve) 
#include<stdio.h> 
#include<stdlib.h> 
//#include<conio.h> 
void main() 
{ 
  int n,i,j,tmp,tmp2,tmp3,tmp4; 
  float avgwt=0,avgtt=0; 
  int pro[100],at[100],bt[100],st[100],wt[100],ft[100],tt[100]; 
  //clrscr(); 
  printf("\n Enter the no of processes: "); 
  scanf("%d",&n); 
  printf("\nPr B.T  A.T\n"); 
  for(i=1;i<=n;i++) 
  { 
    scanf("%d  %d  %d",&pro[i],&bt[i],&at[i]); 
  } 
  for(i=1;i<=n;i++) 
  { 
    for(j=i+1;j<=n;j++) 
    { 
    if(at[i]>at[j]) 
    { 
         tmp=at[i]; 
         at[i]=at[j]; 
         at[j]=tmp; 
         tmp2=bt[i]; 
         bt[i]=bt[j]; 
         bt[j]=tmp2; 
         tmp3=pro[i]; 
         pro[i]=pro[j]; 
         pro[j]=tmp3; 
    } 
    } 
     printf("\n%d\t%d\t%d",pro[i],bt[i],at[i]); 
  } 
 printf("\n\nGantt Chart:\n"); 
 printf("-----------------------\n"); 
 for(i=1;i<=n;i++) 
 { 
   printf("p%d\t|",pro[i]); 
 } 
 printf("\n-----------------------\n"); 
printf("0\t"); 
st[1]=0; 
for(i=2;i<=n+1;i++) 
{ 
    j=i-1; 
    st[i]=st[j]+bt[j]; 
    //st[i]=bt[j]+bt[i]; 
    printf("%d\t",st[i]); 
} 
for(i=1;i<=n;i++) 
{ 
    wt[i]=st[i]-at[i]; 
    ft[i]=st[i]+bt[i]; 
    tt[i]=ft[i]-at[i]; 
    avgwt=avgwt+wt[i]; 
    avgtt=avgtt+tt[i]; 
} 
avgwt=avgwt/n; 
avgtt=avgtt/n; 
  printf("\n------------------------------------------------------------"); 
  printf("\nProcess|B.T.|\tA.T.|\tS.T.|\tW.T.|\tF.T|\tT.T.|"); 
  printf("\n------------------------------------------------------------"); 
  for(i=1;i<=n;i++) 
  { 
    printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d",pro[i],bt[i],at[i],st[i],wt[i],ft[i],tt[i]); 
  } 
  printf("\n------------------------------------------------------------"); 
                                    
printf("\n\n Average Wait time is : %f",avgwt); 
printf("\n Average Turn around time is : %f",avgtt); 
//getch(); 
} 
