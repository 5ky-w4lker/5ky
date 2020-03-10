//Smac0 simulator Program

#include<stdio.h>
#include<stdlib.h>
//#include <conio.h>

long mem[1000], ireg;
int reg[5], cc[7], lc, max,temp,s;

void load();
void execute();
void main()
{
	int choice;
	while(1)
	{
   	
		printf("\n1.Load smac0 Program");
		printf("\n2.Execute smac0 Program");
		printf("\n0.Exit");
		printf("\nEnter Choice:");
		scanf("%d",&choice);
		switch(choice)
		{	
			case 1: load(); break;
    			case 2: execute(); break;
			case 0: exit(0);
		}//switch
	}//while

}//main


void load()
{
	int i;
	FILE *fp;
	char fname[30];//,buf[80];

	printf("\nEnter Smac0 program filename:");
	fflush(stdin); 
	scanf("%s",fname);
	fp=fopen(fname,"r");
	if(fp==NULL)
	{ 
		printf("File does not exist..");
		//getch(); 
		exit(0);
  	}

	max=0;
	while(!feof(fp))   //load instructions in memory
  	{
   		fscanf(fp,"%ld",&mem[++max]);
   	//	fgets(buf,80,fp);
  	}	

  	for(i=1;i<=max;i++)
	{   	
		printf("%06ld\n",mem[i]);
	}
  //getch();
}//load


void execute()
{
 	int opc,opd1,opd2,i,temp;

 	lc=1;
 	while(lc<=max)
 	{
  		ireg=mem[lc++];  //load inst into instruction reg
  		opc=ireg/10000;  //seperate opcode, opd1 and opd2
  		opd1=(ireg/1000)%10;
  		opd2=ireg%1000;
  		switch(opc)
  		{
   			case 1://add
     			reg[opd1]+=mem[opd2]; break;

   			case 2://sub
     			reg[opd1]-=mem[opd2]; break;

   			case 3://mul
     			reg[opd1]*=mem[opd2]; break;

   			case 4://mover
     			reg[opd1]=mem[opd2]; break;

   			case 5://movem
     			mem[opd2]=reg[opd1]; break;

   			case 6://comp
     			for(i=1;i<=5;i++) cc[i]=0; //Intialize cc

     			if(reg[opd1]<mem[opd2])
			cc[1]=cc[2]=cc[6]=1;
     			
			else
     			if(reg[opd1]>mem[opd2])
      			cc[4]=cc[5]=cc[6]=1;
     			else
      			cc[2]=cc[3]=cc[5]=1;cc[6]=1;
     			break;
   			case 7://bc

     			if(cc[opd1]==1)lc=opd2;  //jump to specified addr
      			break;

   			case 8://div
     			reg[opd1]/=mem[opd2]; break;

   			case 9://read
     			printf("\nEnter Input:");
     			scanf("%ld",&mem[opd2]);
     			break;

   			case 10://print
     			printf("\nOutput:%ld",mem[opd2]);
      
     			break;
   
	
			case 11://swap
			
			temp=reg[opd1];
			reg[opd1]=mem[opd2];
			mem[opd2]=temp;break;
		
			case 12://incr
			reg[opd1]=reg[opd1]+1;break;
			
			case 13://decr
			reg[opd1]=reg[opd2]-1;
			break;

			case 14://incm
       			mem[opd2]=mem[opd2]+1;
       			break;
   			
			case 15://decm
       			mem[opd2]=mem[opd2]-1;
       			break;
   
			case 16://addm
       			mem[opd2]+=reg[opd1];
       			break;
   
			case 17://subm
       			mem[opd2]-=reg[opd1];
       			break;
   
			case 18://multm
      			mem[opd2]*=reg[opd1];
      			break;
   			
			case 19://divm
      			mem[opd2]/=reg[opd1];
      			break;
			
			case 20://printr
     			printf("\n result is=%d",reg[opd1]);break;
    
   			case 21://readr
			printf("\n enter Input:");
			scanf("%d",&reg[opd1]);
                        break;

			case 22:
			reg[opd1]=0;break;
     			
			case 23:
			reg[opd1]=1;break;

   
  }//switch
 }//while
 //getch();

}//execute
   //sum of two nos
//enter Input:3

//Enter Input:4

 //result is=7
  //MAXIMUM NOS
//Enter Choice:2

 //enter Input:32

//Enter Input:12

 //result is=32


 //enter Input:12

//Enter Input:23

//result is=23
 
   //factoral no
 
//Enter Input:5

//result is=120





