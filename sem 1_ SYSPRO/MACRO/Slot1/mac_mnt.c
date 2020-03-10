 //Program To display Macro Name Table, Macro Defination Table, Keyword Parameter Table*/

#include <stdio.h>
//#include <conio.h>
//#include <process.h>
#include <string.h>
#include <stdlib.h>

int lc;
int t_code[150],t_index;

char s_code[150][80],fname[15],sm_code[150][80],mdt[100][80],t[20];
char *ptr,*p1,str[100],t1[20],t2[20],t3[20],t4[20];
int s_index,sm_index,mdt_index,curr;

struct mac_info
{
	char name[20];
	int mdt_ptr;
	int pp_cnt;
	int kp_cnt;
	int kpt_ptr;
}mnt[10];
int mnt_index;

struct param
{
	char name[20];
	char value[20];
}kpt[50],apl[50];
int kpt_index;

int pp_cnt,kp_cnt,kpt_ptr,mdt_ptr,tot_param,cp,entry_no;
int i;

void main()
{
	//clrscr();
	sm_index = s_index = mnt_index = mdt_index = kpt_index = curr = 1;
	load_sm_code(); //.....load source code with marco
	print_sm_code(); // ... print source code with macro
	//getch();
	mac_pre_pro();
	print_mdt();
	print_kpt();
	print_mnt();
} // main

load_sm_code()
{
	FILE *fp;
	printf("\nEnter a filename :");
         scanf("%s",fname);
	//flushall();
	//gets(fname);

	if( (fp= fopen(fname,"r") ) == NULL)
	{
		printf("\nFile not found");
		exit(0);
	}
	while ( !feof(fp))
		fgets(sm_code[sm_index++], 80, fp);
	fclose(fp);
	return;
} // laod sm_code

print_sm_code()
{
	printf("\n----- The source code with macro is---------\n");
	for(i=1;i < sm_index ; i++)
		printf("%s",sm_code[i]);
	return;
} // print sm_code

mac_pre_pro()
{
	curr = 1;
	while ( curr < sm_index)
	{
		//.... extract first word
		sscanf(sm_code[curr],"%s",t);
		if( strcmp( t,"MACRO") == 0 ) // macro def
		//       curr++;
			define_mac();

		else
	     /*	if ( search_mac(t) != 0 ) // mac call
			expand_mac(t);
		else*/
		normal_stmt();
	} // while
	return;
} // mac_pre_pro

define_mac()
{
	curr++; //.. skip the word macro
	//copy macro header into mdt
	strcpy(mdt[mdt_index],sm_code[curr]);
	set_kpt_mnt();
	curr++;
	mdt_index++;
	//...copy remaining stmts into mdt
	do
	{
		strcpy(mdt[mdt_index],sm_code[curr]);
		sscanf(sm_code[curr],"%s",t);
		curr++;
		mdt_index++;
	}while( strcmp(t,"MEND") != 0 );
	return;
} // define mac

set_kpt_mnt()
{
	sscanf(sm_code[curr],"%s",t); // extract macro name
	strcpy(mnt[mnt_index].name,t); // copy macro name into mnt
	mnt[mnt_index].mdt_ptr = mdt_index; // set mdt ptr in mnt
	pp_cnt = kp_cnt = kpt_ptr = 0;
	ptr = sm_code[curr];
	while ( ptr != NULL)
	{
		ptr = strstr(ptr,"&");
		if( ptr == NULL)
			break;
		sscanf(ptr,"%s",t);
		ptr++;  // kips &
		p1 = strstr(t,"=");
		if ( p1 == NULL )  // pos
			pp_cnt++;
		else
		{
			kp_cnt++;
			if( kp_cnt == 1 )
				kpt_ptr = kpt_index;
			*p1 = '\0';
			p1++;
			strcpy(kpt[kpt_index].name,t);
			strcpy(kpt[kpt_index].value,p1);
			kpt_index++;
		}
	} // while
	mnt[mnt_index].pp_cnt = pp_cnt;
	mnt[mnt_index].kp_cnt = kp_cnt;
	mnt[mnt_index].kpt_ptr= kpt_ptr;
	mnt_index++;
	return;
} // set kpt mnt

normal_stmt()
{
	strcpy(s_code[s_index], sm_code[curr]);
	curr++;
	s_index++;
	return;
} // normal stmt

print_mdt()
{
	printf("\n---------------The content of mdt is----------\n");
	for(i=1;i<mdt_index;i++)
		printf("%s",mdt[i]);
		//getch();
	return;
} // print mdt

print_kpt()
{
	printf("\n-------------The content of kpt is -----------\n");
	printf("\nName\tValue");
	for(i=1;i<kpt_index;i++)
		printf("\n%s\t%s",kpt[i].name,kpt[i].value);
		//getch();
	return;
} // print kpt

print_mnt()
{
	printf("\n ----------------- The content of mnt is-----------\n");
	printf("\nName\tmdt_ptr\tpp_cnt\tkp_cnt\tkpt_ptr\n");
	for(i=1;i<mnt_index;i++)
		printf("\n%s\t%d\t%d\t%d\t%d\n",   mnt[i].name,mnt[i].mdt_ptr,
			    mnt[i].pp_cnt,mnt[i].kp_cnt, mnt[i].kpt_ptr);
	printf("\n");
		//getch();
	return;
} // print mnt

search_mac( char t[])
{
	for(i=1;i<mnt_index; i++)
	{
		if( strcmp(mnt[i].name,t) == 0 )
			return(i);
	}
	return(0);
} // search macro

process_token(char t[])
{
	if( t[0] != '&')
		return;
	for(i=1;i<=tot_param;i++)
		if( strcmp(apl[i].name,t) == 0 )
		{
			strcpy(t,apl[i].value);
			return;
		}
	return;
}

print_s_code()
{
	printf("\n------ Final source code is -----\n");
	for(i=1;i<s_index;i++)
		printf("%s",s_code[i]);
	//getch();
	return;
} // pritn s_code

/*
Enter a filename :mac2.txt

----- The source code with macro is---------
MACRO
COPY & ONE,& TWO,& REG=BREG
MOVER & REG,& ONE
MOVEM & REG,& TWO
MEND
MACRO
CHANGE & FIRST,& SECOD,& REG=AREG,& OP=ADD
MOVER & REG,& FIRST
& OP & REG,& SECOND
MOVEM & REG,& FIRST
MEND

---------------The content of mdt is----------
COPY & ONE,& TWO,& REG=BREG
MOVER & REG,& ONE
MOVEM & REG,& TWO
MEND
CHANGE & FIRST,& SECOD,& REG=AREG,& OP=ADD
MOVER & REG,& FIRST
& OP & REG,& SECOND
MOVEM & REG,& FIRST
MEND

-------------The content of kpt is -----------

Name	Value
 ----------------- The content of mnt is-----------

Name	mdt_ptr	pp_cnt	kp_cnt	kpt_ptr
COPY	1	3	0	0
CHANGE	5	4	0	0
*/



