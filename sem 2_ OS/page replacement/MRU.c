/* Demand Paging- Page Replacement Algorithm--Most Recently Used [MRU] */ 
#include<stdio.h> 
//#include<conio.h> 
struct node 
{ 
  int pno,reftime; 
}frames[3]={{-1,-1},{-1,-1},{-1,-1}}; 
int page_found(int pno) 
{ 
  int i; 
  for(i=0;i<3;i++) 
    if(frames[i].pno==pno) 
       return i; 
    return -1; 
} 
 
int get_free_frame() 
{  int fno; 
  for (fno=0; fno<=2; fno++) 
    if (frames[fno].pno==-1) 
        return(fno); 
   return(-1); 
} 
 
int get_mru_Frame() 
{ 
  int maxfno=0,fno; 
  for (fno=1; fno<=2; fno++) 
  { 
     if(frames[fno].reftime>frames[maxfno].reftime) 
       maxfno=fno; 
    } 
  return maxfno; 
} 
void main() 
{ 
   int p_request[]={5,8,10,14,10,9,5,10,8,5,1,10,9,12,10}; 
   int size=15,currtime; 
   int page_falts=0,i,j; 
   //clrscr(); 
   printf("\nPageNo     Page Frames   Page Fault"); 
   printf("\n      0    1    2"); 
   printf("\n------------------------------"); 
   currtime=0; 
   for(i=0;i<size;i++) 
   { 
     j=page_found(p_request[i]); 
     if(j==-1)  //page fault occurs 
     { 
       j=get_free_frame(); 
       if (j==-1)//no free frame - do replacement 
          j=get_mru_Frame(); 
       page_falts++; 
       frames[j].pno=p_request[i]; 
       printf("\n%4d \t%4d %4d %4d    Yes",p_request[i],frames[0].pno,frames[1].pno,frames[2].pno); 
    } 
    else 
         printf("\n%4d \t%4d %4d %4d    No",p_request[i],frames[0].pno,frames[1].pno,frames[2].pno); 
    frames[j].reftime=currtime; 
    currtime++; 
   } 
  printf("\n------------------------------------------"); 
  printf("\n Number of Page_Falts=%d",page_falts); 
  //getch(); 
} 
 
 
/*******************OUTPUT***************************/ 
/*PageNo     Page Frames   Page Fault                                              
            0    1    2                                                            
------------------------------                                                   
   5       5   -1   -1    Yes 
   8       5    8   -1    Yes                                                    
  10       5    8   10    Yes                                                    
  14       5    8   14    Yes                                                    
  10       5    8   10    Yes                                                    
   9       5    8    9    Yes                                                    
   5       5    8    9    No                                                     
  10      10    8    9    Yes                                                    
   8      10    8    9    No                                                     
   5      10    5    9    Yes                                                    
   1      10    1    9    Yes                                                    
  10      10    1    9    No                                                     
   9      10    1    9    No                                                     
  12      10    1   12    Yes                                                    
  10      10    1   12    No                                                     
------------------------------------------                                       
 Number of Page_Falts=10      */                                                    
