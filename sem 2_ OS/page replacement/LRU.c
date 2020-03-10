/*Demand Paging- Page Replacement Algorithm---LRU (Least Recently Used)*/ 

#include<stdio.h> 
//#include<conio.h> 
#define SIZE 5 
int n; 
struct frame 
{ 
    int pno,counter; 
}flist[SIZE]={{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}}; 
int pagefound(int pno) 
{ 
    int i; 
    for(i=0;i<n;i++) 
        if(flist[i].pno==pno) 
            return i; 
    return -1; 
} 
int getlrupage() 
{ 
    int i,minindex=0; 
    for(i=1;i<n;i++) 
    { 
        if(flist[i].counter<flist[minindex].counter) 
            minindex=i; 
    } 
    return minindex; 
} 
void main() 
{ 
    int i,j,pfcount=0,pno,k,n1; 
    int refstring[20]; 
    //clrscr(); 
    printf("\n Enter how many pages do you want in reference string:"); 
    scanf("%d",&n1); 
    printf("\n Enter No.'s:"); 
    for(i=0;i<n1;i++) 
    { 
        scanf("%d",&refstring[i]); 
    } 
    printf("\n"); 
    printf("\n Enter no of frames:"); 
    scanf("%d",&n); 
    if((n>0)&&(n<=SIZE)) 
    { 
        printf("\nPage No\tPage Frames\n"); 
        printf("--------------------------------"); 
        for(i=0;i<n1;i++) 
        { 
            pno=refstring[i]; 
            printf("\n%6d\t",pno); 
            j=pagefound(pno); 
            if(j==-1) 
            { 
                j=getlrupage(); 
                flist[j].pno=pno; 
                for(k=0;k<n;k++) 
                    printf("%5d",flist[k].pno); 
                pfcount++; 
            } 
            flist[j].counter=i; 
        } 
        printf("\n-----------------------------"); 
        printf("\n\n Total Page Faults=%d",pfcount); 
    } 
    //getch(); 
} 
/********************************OUTPUT****************************/ 
 
/* Enter No.'s: 
7                                                                   
0                                                                                
1                                                                                
2                                                                                
0                                                                                
3 
0 
4 
2 
3 
0 
3 
2 
1 
2 
0 
1 
7 
0 
1 
 
 Enter no of frames:3 
 
Page No Page Frames 
-------------------------------- 
     7      7   -1   -1 
     0      7    0   -1 
     1      7    0    1 
     2      2    0    1 
     0 
     3      2    0    3 
     0 
     4      4    0    3 
     2      4    0    2 
     3      4    3    2 
     0      0    3    2 
     3 
     2 
     1      1    3    2 
     2 
     0      1    0    2 
     1 
     7      1    0    7 
     0 
     1 
----------------------------- 
 
 Total Page Faults=12 
*/
