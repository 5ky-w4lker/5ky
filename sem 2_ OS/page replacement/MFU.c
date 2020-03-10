/*Demand Paging- Page Replacement Algorithm--MFU(Most Frequently Used)*/ 
#include<stdio.h> 
#include<conio.h> 
#define SIZE 5 
int n,t=0; 
struct frame 
{ 
    int pno,refcount; 
}flist[SIZE]={{-1,99},{-1,99},{-1,99},{-1,99},{-1,99}}; 
struct frame pagerefstring[20]; 
int pagefound(int pno) 
{ 
    int i; 
    for(i=0;i<n;i++) 
        if(flist[i].pno==pno) 
            return i; 
    return -1; 
} 
int getmfupage() 
{ 
    int i,maxindex=0; 
    for(i=1;i<n;i++) 
    { 
        if(flist[i].refcount>flist[maxindex].refcount) 
            maxindex=i; 
    } 
    return maxindex; 
} 
int updaterefstring(int pno) 
{ 
    int i; 
    for(i=0;i<t;i++) 
    { 
        if(pagerefstring[i].pno==pno) 
        { 
            pagerefstring[i].refcount++; 
            return pagerefstring[i].refcount; 
        } 
    } 
    if(i==t) 
    { 
        pagerefstring[i].pno=pno; 
        pagerefstring[i].refcount=1; 
        t++; 
        return 1; 
    } 
} 
void main() 
{ 
    int i,j,pfcount=0,pno,k,n1; 
    int refstring[20]; 
    clrscr(); 
    printf("\n Enter how many no's you want in reference string:"); 
    scanf("%d",&n1); 
    printf("\n Enter No.'s:"); 
    for(i=0;i<n1;i++) 
    { 
        scanf("%d",&refstring[i]); 
    } 
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
                j=getmfupage(); 
                flist[j].pno=pno; 
                pfcount++; 
                for(k=0;k<n;k++) 
                    printf("%5d",flist[k].pno); 
            } 
            flist[j].refcount=updaterefstring(pno); 
        } 
        printf("\n-----------------------------"); 
        printf("\n\n Total Page Faults=%d",pfcount); 
    } 
    getch(); 
} 
/*OUTPUT:- 
 Enter how many no's you want in reference string:                               
20                                                                               
 Enter No.'s:7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1                             
 Enter no of frames:3 
Page No Page Frames 
-------------------------------- 
     7      7   -1   -1 
     0      7    0   -1 
     1      7    0    1 
     2      2    0    1 
     0 
     3      2    3    1 
     0      0    3    1 
     4      4    3    1                                                          
     2      2    3    1                                                          
     3                                                                           
     0      0    3    1                                                          
     3                                                                           
     2      2    3    1                                                          
     1                                                                           
     2 
     0      0    3    1                                                          
     1 
     7      7    3    1 
     0      7    0    1 
     1 
----------------------------- 
 Total Page Faults=13 
*/ 


