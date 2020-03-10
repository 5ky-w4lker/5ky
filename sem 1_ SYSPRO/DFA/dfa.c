/* ASSIGNMENT:- DFA[ SETA 3]
 Implement DFA driver for following language :
L = { set of all strings over {0, 1} which contain even number of 0 and odd number of 1} */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
int i,j,k,no_of_states,no_of_input_symb,no_of_final_states,cur;
char input_symb[100];
int final_states[50];
char ch,c;
int transition[10][10],flag;
char test_string[100];
printf("\nenter Number of states\n");
scanf("\n%d",&no_of_states);
for(i=0;i<no_of_states;i++)
   {
      printf("\nEnter state no\n");
      scanf("\n%d",&transition[i]);
   }
printf("\nenter Number of input symbol\n");
scanf("\n%d",&no_of_input_symb);
for(i=0;i<no_of_input_symb;i++)
   {
      printf("\nEnter symbol \n");
      scanf("\n%c",&input_symb[i]);
   }
printf("\nenter Number of final states\n");
scanf("\n%d",&no_of_final_states);
for(i=0;i<no_of_final_states;i++)
   {
      printf("\nEnter final state \n");
      scanf("\n%d",&final_states[i]);
   }
 for(i=0;i<no_of_states;i++)
   {
       for(j=0;j<no_of_input_symb;j++)
            {
            printf("\nenter transition to flag q%d for symbol %c\n",i,input_symb[j]);
             scanf("%d",&transition[i][j]);
            }
   }
  printf("\nTransition Table\n");
  printf("\n------------------------\nAlpbabet ");
  
for(i=0;i<no_of_input_symb;i++)
   {
      printf(" %c  ",input_symb[i]);
   } 
printf("\nstates");
  printf("\n------------------------\n");
for(i=0;i<no_of_states;i++)
   {    printf("      q%d",i);         
       for(j=0;j<no_of_input_symb;j++)
            {
              printf("  q%d",transition[i][j]);
            }
        printf("\n");
   }
  printf("\n------------------------\n");
while(1)
{
cur=0;
flag=0;
printf("\nenter string to check valid or invalid\n");
scanf("%s",test_string);
i=0;
while(test_string[i]!='\0')
{
ch=test_string[i];
//printf("%c",ch);
for(k=0;k<no_of_input_symb;k++)
   {   if(ch==input_symb[k])
        {
          printf("\ncur state=%d  next character=%c",cur,input_symb[k]);
       cur=transition[cur][k];
        }       
   }
i++;
}
printf("\ncur state=%d",cur);
for(i=0;i<no_of_final_states;i++)
   {
     // printf("\nfinal state=%d",final_states[i]);
      if(cur==final_states[i])
       flag=1; 
   }
if(flag==1)
printf("\nvalid string\n");
else if(flag==0)
printf("\nINvalid string\n");
printf("\nare u checking another string if yes then press y  otherwise press n\n");
scanf("\n%c",&c);
if(c=='n')
break;
else if(c=='y')
continue;
}
return(0);
}



