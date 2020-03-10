
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node
{
char symb[20];
int add,len,val,used,decl;
struct node *link;
}NODE;
char addtab[][7]={"START","END","ORIGIN","EQU","LTORG"};

char regtab[][6]={"AREG","BREG","CREG","DREG"};
char optab[18][6] = 	{"STOP", "ADD", "SUB", "MULT", "MOVER","MOVEM",
			 "COMP", "BC", "DIV", "READ", "PRINT"};
char condtab[][6]={"LT","LE","EQ","GT","GE","ANY"};
char buff[80],t1[20],t2[20],t3[20],t4[20],fname[20];
int lc;
FILE *fp;
NODE *first,*last;
void add_symb1(char *s,int add,int len,int val)
{
	NODE *p;
	p=(NODE *)malloc(sizeof(NODE));
	strcpy(p->symb,s);
	p->add=add;
	p->len=len;
	p->val=val;
	p->used=0;
	p->decl=1;
	p->link=NULL;
	if(first==NULL)
	first=p;
	else
	last->link=p;
	last=p;
}
void add_symb2(char *s)
{
	NODE *p;
	p=(NODE *)malloc(sizeof(NODE));
	strcpy(p->symb,s);
	p->add=	p->len=	p->val=	p->decl=0;
	p->used=1;
	p->link=NULL;
	if(first==NULL)
	first=p;
	else
	last->link=p;
	last=p;
}

NODE *search_symb(char *s)
{
	NODE *p;
	p= first;
	while(p!=NULL)
	{
	if(strcmp(p->symb,s)==0)
	break;
	p=p->link;
	}
return p;
}

int search_optab(char *s)
{
	int i;
	for(i=0;i<11;i++)
	{
     //	printf("\n optab[%d] is %s",i,optab[i]);
	if(strcmp(optab[i],s)==0)
	return i;
	}
	return -1;

}

int search_regtab(char *s)
{
	int i;
	for(i=0;i<4;i++)
	{
//printf("\n regtab[%d] is %s",i,regtab[i]);
	if(strcmp(regtab[i],s)==0)
	return i;
	}
	return -1;
}

int search_condtab(char *s)
{
	int i;
	for(i=0;i<6;i++)
	if(strcmp(condtab[i],s)==0)
	return i;
	return -1;

}

int search_addtab(char *s)
{
	int i;
	for(i=0;i<5;i++)
	if(strcmp(addtab[i],s)==0)
	return i;
	return -1;
}
void print_symbtab()
{
	NODE *p;
	int i=1;
	printf("\n *\tsymb\tadd\tlen\tval\tdecl\tused\n");
	p=first;
	while(p!=NULL)
	{
		printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",i,p->symb,p->add,p->len,p->val,p->decl,p->used);
		i++;
		p=p->link;
	}
	p=first;
	while(p!=NULL)
	{
		if(p->decl==1 && p->used==0)
			printf("\n symbol %s is declared but not used ",p->symb);
		if(p->decl==0 && p->used==1)
			printf("\n symbol %s is used but not declared ",p->symb);
		p=p->link;
	}
}

void main()
{
	FILE *fp1;
	int n,i;
	NODE *p;
	  //clrscr();
	printf("\n Enter source filename..\n");
	scanf("%s",fname);
	fp=fopen(fname,"r");
		fp1=fopen(fname,"r");
	if(fp==NULL)
	{
		printf("\n File %s is not present...",fname);
		exit(0);
	}

	while (fgets(buff,80,fp1)!=NULL)
	puts(buff);

	while (fgets(buff,80,fp)!=NULL)
	{
//	puts(buff);
		n=sscanf(buff,"%s %s %s %s",t1,t2,t3,t4);
		switch(n)
		{
			case 2:
				if(strcmp(t1,"START")==0)
				{
					lc=atoi(t2)-1;
					//printf("\n lc=%d",lc);
					break;
				}
				i=search_optab(t1);
				if(i==9 || i==10)
				{
					p=search_symb(t2);
					if(p==NULL)
						add_symb2(t2);
					else
						p->used=1;
					break;
				}
				p=search_symb(t1);
				if(p==NULL)
					add_symb1(t1,lc,0,0);
				else
				{
					if(p->decl==1)
						printf("\n %d redeclaration of symbol %s",lc,t1);
					else
					{
						p->add=lc;
						p->decl=1;
					}
				}
				break;
			case 3:
				if(strcmp(t2,"DS")==0)
				{
					p=search_symb(t1);
					if(p==NULL)
					{
						add_symb1(t1,lc,atoi(t3),0);
						lc=lc+atoi(t3)-1;
					}
					else
					{
						if(p->decl==1)
						printf("\n %d Redeclaration of symbol %s:",lc,t1);
						else
						{
							p->add=lc;
							p->len=atoi(t3);
							p->decl=1;
							lc=lc+atoi(t3)-1;
						}
					}
					break;
				}
				if(strcmp(t2,"DC")==0)
				{
					p=search_symb(t1);
					if(p==NULL)
						add_symb1(t1,lc,1,atoi(t3+1));
					else
					{
						if(p->decl==1)
						printf("\n %d redeclaration of symbol %s",lc,t1);
						else
						{
							p->add=lc;
							p->len=1;
							p->val=atoi(t3+1);
							p->decl=1;
						}
					}
					break;
				}
				i=search_optab(t1);
				if(i==-1)
				printf("\n%s is Invalid mnemonic....at %d",t1,lc);
				if((i>=1) && (i<=9))
				{
					p=search_symb(t3);
				       //	printf("\n ..t3 is %s\n",t3);
					if(p==NULL)
					 {
			if(search_optab(t3)==-1 && search_addtab(t3)==-1  && search_regtab(t3)==-1 && search_condtab(t3)==-1)
				add_symb2(t3);
				else
				printf("\n %d is invalid symbol name %s",lc,buff);
				}
				       ///	add_symb2(t3);
					else
					p->used=1;
					break;
				}
				p=search_symb(t3);
				if(p==NULL)
					add_symb2(t3);
				else
					p->used=1;
				break;
			case 4:
				p=search_symb(t1);
				if(p==NULL)
					add_symb1(t1,lc,0,0);
				else
				{

					if(p->decl==1)
						printf("\n %d redeclaration of symbol %s",lc,t1);
					else
					{
						p->add=lc;
						p->decl=1;
					}
				}
				p=search_symb(t4);
				if(p==NULL)
					add_symb2(t4);
				else
					p->used=1;
			}//switch..
		lc++;

	}//while.

	fclose(fp);
	print_symbtab();
}//main


/*Output

   Enter source filename..
as1.asm
START 100

READ X

READ Y

L MOVER AREG x

ADD AREG Y

MOVEM AREG A

PRINT X

STOP

X DS 1

Y DS 1

END

 *	symb	add	len	val	decl	used
1	X	107	1	0	1	1
2	Y	108	1	0	1	1
3	L	102	0	0	1	0
4	x	0	0	0	0	1
5	A	0	0	0	0	1

 symbol L is declared but not used 
 symbol x is used but not declared 
 symbol A is used but not declared */




