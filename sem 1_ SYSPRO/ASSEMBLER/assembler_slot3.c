//Assembler for smac0
//Set A Q.4.:
//Display content of symbol table, literal table

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct symtabentry
{
 char symbol[20];
 int addr;
 int value;
 int used;
} symtab[30];

struct literalentry
{
  char literal[10];
  int addr;
} littab[30];


char scode[100][80];
char opcode[][16]={"","add","sub","mul","mover","movem","comp","bc",
	       "div", "read","print","stop","dc","ds","start","org","ltorg"};
char fname[20];
int i,lc=1,si=0,sti=0,lti=0,cpptr=1,pooltab[10];


void loadscode();
void pass1();
void addlabel(char []);
int getopcode(char []);
int addopd2(char t[]);
int getopd2(char t[]);
void printsymtab();
void printlittab();
void litaddr();

void main()
 { printf("******************");
  loadscode();
  pass1();
  printsymtab();
  printlittab();
}


void loadscode()
{
 FILE *fp;

 //clrscr();
 printf("Enter Asm program filename:");
 scanf("%s",fname);
   //printf("******************");
 fp=fopen(fname,"r");
 if (fp==NULL)
 { printf("File not found..");
   exit(0);
 }
 while(!feof(fp))
 {
   fgets(scode[++si],80,fp);

 }
 fclose(fp);

 printf("***Source code***\n");
 for(i=1; i<=si; i++)
   printf("%s",scode[i]);
 //getch();
}

void pass1()
{
  int curr,n,opc,opd2;
  char t1[15], t2[15], t3[15], t4[15];

  pooltab[cpptr]=1; //Initialize pooltab entry
   printf("******************");
  for(curr=1; curr<=si; curr++)
  { if (strlen(scode[curr])==0) continue;
    n=sscanf(scode[curr],"%s %s %s %s",t1,t2,t3,t4);
//printf("\n-----------------------------------");
    switch(n)
    {
     case 4: //label opcode opd1 opd2
	 addlabel(t1);
	 getopd2(t4);
	 lc++;
	 break;
     case 3://label opcode opd2      opcode opd1 opd2
	 opc=getopcode(t1);
	 if (opc==-1)//t1 is label
	 { addlabel(t1);
	   if (strcmp(t2,"ds")==0)
	     lc+=atoi(t3);
	   else
	   if (strcmp(t2,"dc")==0)
	     symtab[sti].value=atoi(t3);
	   else
	   { getopd2(t3);
	     lc++;
	   }
	 }
	 else //t1 is opcode
	 { getopd2(t3);
	   lc++;
	  }
	 break;
     case 2: //label opcode       opcode opd2
	opc=getopcode(t1);
	if (opc==-1)//t1 is label
	{ addlabel(t1);
	  if(strcmp(t2,"ltorg")==0)
	    litaddr();
	  else
	   lc++;
	}
	else //t1 is opcode
	{
if (opc==14||opc==15)//start or org
	    lc=atoi(t2);
	  else //READ A   PRINT A
	  { getopd2(t2);
	    lc++;
	   }
	}
       break;
     case 1: //opcode
	if (strcmp(t1,"ltorg")==0)
	  litaddr();
	else
	if(strcmp(t1,"end")==0)
	  {
	   litaddr();
	   return;
	  }
	else
	 lc++;
    }//switch
  }//for curr
  litaddr();
}//pass1


void addlabel(char t[])
{

  for(i=1; i<=sti; i++)
   { if (strcmp(symtab[i].symbol,t)==0)//symbol found
      { if(symtab[i].addr!=0)
	 {  //printf("\nError:Redeclaration of symbol: %s",t);
	   //getch();
	   return;
	 }
	 else
	  { symtab[i].addr=lc;
	     return;
	  }
       }//if
   }//for i

   //symbol Not found
  strcpy(symtab[++sti].symbol,t);
  symtab[sti].addr=lc;
}//addlabel


int getopcode(char t[])
{ for (i=1; i<=16; i++)
  { if (strcmp(opcode[i],t)==0)
      return(i);
   }
  return(-1);

}//getopcode


int getopd2(char t[])
{
   char *ptr;
  if (t[0]=='=')//Literal
   {
     strcpy(littab[++lti].literal,t);
  //   return(lti);
   }
  else //symbol
  {
     for(i=1; i<=sti; i++)
       if (strcmp(symtab[i].symbol,t)==0)
	{ symtab[i].used=1;
	  return(i);
	}
     strcpy(symtab[++sti].symbol, t);
     symtab[sti].addr=0;
     symtab[sti].used=1;
   //  return(sti);
   }
}//getopd2

void printsymtab()
{
  printf("\n*** Symbol Table ***\n");
  printf("Symbol\tAddress\tValue\tUsed\n");
  for(i=1; i<=sti; i++)
   printf("%s\t%d\t%d\t%d\n",symtab[i].symbol,symtab[i].addr,symtab[i].value,symtab[i].used);
  //getch();
}

void litaddr()
{
  for(i=pooltab[cpptr]; i<=lti; i++)
   littab[i].addr=lc++;

  //prepare new pool
  cpptr++;
  pooltab[cpptr]=lti+1;
}

void printlittab()
{
  printf("\n********* Pool Table ***********\n");
  printf("PoolIndex  LiteralIndex\n");
  for(i=1;i<=cpptr;i++)
  printf("%d\t\t%d\n",i,pooltab[i]);
  printf("\n********** Literal Table *********\n");
  printf("\tLiteral\t\tAddress\n");
  for(i=1; i<=lti; i++)
    printf("\t%s\t\t%d\n",littab[i].literal, littab[i].addr);
  //getch();
}

/****************************************OUTPUT*****************************************************************/
/*

kkw-pc88@kkwpc88-HP-dx2480-MT-FN870PA:~/Assignment3_ Assembler$ cc assembler_slot3.c
kkw-pc88@kkwpc88-HP-dx2480-MT-FN870PA:~/Assignment3_ Assembler$ ./a.out
******************Enter Asm program filename:a4.asm
***Source code***
START 100
L1 MOVER AREG =5
MOVER BREG =1
MOVER BREG A
LTORG
MOVER CREG =4
MOVER DREG =1
MOVER BREG B
PRINT A
STOP
A DS 1
B DC 2
END
******************
*** Symbol Table ***
Symbol	Address	Value	Used
START	1	0	0
L1	2	0	0-
MOVER	3	0	0
A	11	0	1
B	12	0	1
PRINT	9	0	0
1	0	0	1
2	0	0	1

*** Pool Table ***
PoolIndex  LiteralIndex
1	1
2	5

*** Literal Table ***
Literal	Address
1	=5	14
2	=1	15
3	=4	16
4	=1	17
kkw-pc88@kkwpc88-HP-dx2480-MT-FN870PA:~/Assignment3_ Assembler$

*/







