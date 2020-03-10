//-------------------------------ASS4FIFO-------------------------------- 
/*Demand Paging- Page Replacement Algorithm- First In First Out [FIFO]*/ 
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
int getfifopage() 
{ 
    int i,minindex=0; 
    for(i=1;i<n;i++) 
           if(flist[i].counter<flist[minindex].counter) 
               minindex=i; 
    return minindex; 
} 
void main() 
{ 
    int i,pfcount=0,j,n1,pno; 
    int refstring[25]; 
    //clrscr(); 
    printf("\n Enter how many no's you want in reference string:"); 
    scanf("%d",&n1); 
    printf("\n Enter reference string:"); 
    for(i=0;i<n1;i++) 
    { 
        scanf("%d",&refstring[i]); 
    } 
    printf("\n Enter number of frames:"); 
    scanf("%d",&n); 
    if((n>0)&&(n<=SIZE)) 
    { 
        printf("\n Page No.\t Page Frames"); 
        printf("\n-----------------------------------"); 
        for(i=0;i<n1;i++) 
        { 
            pno=refstring[i]; 
            printf("\n %6d \t",pno); 
            j=pagefound(pno); 
            if(j==-1) 
            { 
                j=getfifopage(); 
                flist[j].pno=pno; 
                flist[j].counter=i; 
                for(j=0;j<n;j++) 
                    printf("%5d",flist[j].pno); 
                pfcount++; 
            } 
            flist[j].counter=i; 
        } 
        printf("\n----------------------------------------"); 
        printf("\n Total page faults=%d",pfcount); 
        //getch(); 
    } 
} 
/***********************************************OUTPUT***************************/ 
/*kkw-pc88@kkwpc88-HP-dx2480-MT-FN870PA:~/Ass4_MemoryMang$ cc FIFO.c 
kkw-pc88@kkwpc88-HP-dx2480-MT-FN870PA:~/Ass4_MemoryMang$ ./a.out 
 Enter how many no's you want in reference string:12 
 Enter reference string:1 
2 
3 
4 
1 
2 
5 
1 
2 
3 
4 
5 
 Enter number of frames:3 
 Page No.     Page Frames 
----------------------------------- 
      1         1   -1   -1    
      2         1    2   -1    
      3         1    2    3   
      4         4    2    3   
      1         4    1    3   
      2         4    1    2   
      5         5    1    2   
      1                       
      2               
      3         3    1    2   
      4         3    4    2   
      5         3    4    5   
---------------------------------------------------- 
 Total page faults=10 */ 
