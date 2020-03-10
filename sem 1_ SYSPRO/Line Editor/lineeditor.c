/* Line Editor */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

 struct node
  {
     char l[500];
     struct node *next;
  } *head,*temp,*curr;

  static cnt;

   void create()  //to create a single
    {
      struct node *nw;
      int i;
      nw=(struct node *)malloc(sizeof(struct node));
      //printf("\n In create function");
      gets(nw->l);
      nw->next=NULL;
      if(head==NULL)
      temp=head=nw;
       else
	{
	 curr=nw;
	 temp->next=curr;
	 temp=curr;
	}
   }

 void disp(int s, int e)  //print the lines in between range
      {
       int i;
       curr=head;
       for(i=1;i<s && curr!=NULL;i++,curr=curr->next);
       for(i=s;i<=e && curr!=NULL;i++,curr=curr->next)
	{
	 printf("\n %d.%s",i,curr->l);
	}
      }

 void print() //to print all the lines
	{
	 int i=1;
	 curr=head;
	 while(curr)
	  {
	    printf("\n %d.%s",i,curr->l);
	    curr=curr->next;
	    i++;
	  }
       }

 void del(int pos) //to delete a line
	 {
	  int cnt,i;
	  if(pos==1)
	  {
	    curr=head;
	    head=head->next;
	    free(curr);
	  }
	   else
	   {
	    for(i=1,curr=head;i<pos-1 && curr;i++,curr=curr->next);
	    temp=curr->next;
	    curr->next=temp->next;
	    free(temp);
	   }
	}

 void del1(int s,int e)  //to delete a lines between the ranges
	  {
	    struct node *temp1,temp2;
	    int cnt,i;
	    while(s!=e+1)
	     {
	     if(s==1)
	      {
	      for(i=1,curr=head;i<=e && curr!=NULL;i++,curr=curr->next);
	       {
		temp=head;
		head=head->next;
		free(temp);
	       }
	  }
	    else
	     {
	      for(i=s,curr=head;i<s-1 && curr;i++,curr=curr->next);
	      temp=curr->next;
	      curr->next=temp->next;
	      free(temp);
	    }
	    e--;
	    }//while
       }//del


 void insert(int pos)   //insert a line in between
	{
	 int i;
	 struct node *nw;
	 nw=(struct node *)malloc(sizeof(struct node));
	// flushall();
	 gets(nw->l);
	 nw->next=NULL;

	  if(pos==1)
	   {
	    nw->next=head;
	    head=nw;
	   }
	    else
	    {
	    for(i=1,curr=head;i<pos-1 && curr;i++,curr=curr->next);
	    temp=curr->next;
	    curr->next=nw;
	    nw->next=temp;
	  }
       }

  void move(int s,int e) //move a line from possition s to possition e
	 {
	  struct node *prev,*temp1;
	  int i;
	  if(s<e)
	   {
	    if(s==1)
	     {
	     for(i=1,temp=head;i<e && temp!=NULL;i++,temp=temp->next);
	       prev=head;
	       head=head->next;
	       prev->next=temp->next;
	       temp->next=prev;
	     }
	     else
	      {
	       for(i=1,prev=head;i<s-1 && prev!=NULL;i++,prev=prev->next);
	       for(i=1,temp=head;i<e && temp!=NULL;i++,temp=temp->next);
		curr=prev->next;
		prev->next=curr->next;
		curr->next=temp->next;
		temp->next=curr;
	     }
	  }
	  else
	  if(s>e)
	   {
	     if(e==1)
	      {
	       for(i=1,temp=head;i<s-1 && temp!=NULL;i++,temp=temp->next);
		temp1=temp->next;
		temp->next=temp1->next;
		temp1->next=head;
		head=temp1;
	      }
	       else
	       {
		for(i=1,temp=head;i<e-1 && temp!=NULL;i++,temp=temp->next);
		for(i=1,prev=head;i<s-1 && prev!=NULL;i++,prev=prev->next);
		       curr=prev->next;
		       prev->next=curr->next;
		       curr->next=temp->next;
		       temp->next=curr;
		     }
		 }
	     }

  void copy(int s, int e)  //copy a line from possition s to possition e
	     {
	      struct node *prev,*temp1,*nw;
	      int i;
	      nw=(struct node *)malloc(sizeof(struct node));
	      if(e==1)
	       {
		for(i=1,temp=head;i<s && temp!=NULL;i++,temp=temp->next);
		  strcpy(nw->l,temp->l);
		  nw->next=head;
		  head=nw;
	     }
	      else
	       {
	       for(i=1,prev=head;i<s && prev!=NULL;i++,prev=prev->next);
		 strcpy(nw->l,prev->l);
		 nw->next=NULL;
		 for(i=1,temp=head;i<e-1 && temp!=NULL;i++,temp=temp->next);
		 nw->next=temp->next;
		 temp->next=nw;
	       }
	    }

   void save(char s[20])
	      {
	       FILE *fp;
	       fp=fopen(s,"w");
	       curr=head;
	       while(curr)
		{
		fprintf(fp,curr->l);
		curr=curr->next;
	     }
	      fclose(fp);
	    }

    void append() //append a line at the end of the line
	      {
	       temp=head;
	       while(temp->next!=NULL)
		{
		 temp=temp->next;
		}
		 create();
	       }

	       void search(char str[50])
	       {
		struct node *temp,*temp1;
		int i,j,lent,lens,k=0;
		lens=strlen(str);
		for(temp=head;temp!=NULL;temp=temp->next);
		{
		 lent=0;
		 k++;
		 lent=strlen(temp->l);
		 i=0;
		 for(j=0;j<lent;j++)
		  {
		   if(temp->l[j]==' ')
		   i=0;
		   if(temp->l[j]==str[i])
		   {
		     i++;
		     temp1=temp;
		   }

		   //if(i==lens)
		  if(temp1->l==str)
		    {
		     printf("\n $:> Word Found");
		     printf("\n $:> Line Number : %d",k);
		     printf("\n $:> %d.%s",k,temp1->l);
		     break;
		  }
		}
	     }
	     printf("\n");
	   }

	   void help()
	 {
	    printf("\n c : To Create a New Line ");
	    printf("\n p : To print all the lines ");
	    printf("\n d : To delete a line d<line no.> .");
	    printf("\n i : To insert a new line, i<pos>.");
	    printf("\n m : To move any line from pos1 to pos2, m<pos1 pos2>");
	    printf("\n r : To copy from pos1 to pos2, r<pos1 pos2>");
	    printf("\n a : To append new line");
	    printf("\n s : To Save all the lines in a File");
	    printf("\n f : To search a pattern & display that line number");
	    printf("\n e : To Exit");
	 }

	 void main()
	 {
	  int s,e;
	  char ch,c,l,fname[17],str[50];
	  //clrscr();
	  head=temp=curr=NULL;
	  do
	  {
	     printf("\n $:>");
	     //flushall();
	     scanf("%c",&c);
	      switch(c)
	       {
		case 'c':  //create a new line
		case 'C':    
				create();
				break;
		case 'p':
		case 'P': //print all the lines
				scanf("%c",&l);
				if(l=='\n')
				{
				   print();
				}
				else
				{
				 scanf("%d%d",&s,&e);
				 if(s>0 && e>0 && s<e)
				 disp(s,e);
				 else
				  disp(1,49);
				}
				break;

		case 'd':
		case 'D': //delete a line
				scanf("%d",&s);
				scanf("%c",&l);
				if(l=='\n')
				{
				 del(s);
				}
				else
				{
				 scanf("%d",&e);
				 del1(s,e);
				}
				



		break;

		case 'I':
		case 'i': //insert a line in between 
				scanf("%d",&s);
				insert(s);
				break;

		case 'M':
		case 'm': //move a line from 1 possition to another
				scanf("%d%d",&s,&e);
				move(s,e);
				break;

		case 'r':
		case 'R':  //to copy a line from 1 possition to another
				scanf("%d%d",&s,&e);
				copy(s,e);
				break;

		case 's':
		case 'S': //to save a file 
				printf("\n Enter the file Name: ");
				//flushall();
				gets(fname);
				save(fname);
				printf("\n File is Saved Successfully");
				break;


		case 'f':
		case 'F': //to search a patten
				//flushall();
				gets(str);
				search(str);
				break;


		case 'a':
		case 'A': //append a line at the end
				append();
				break;

		case 'h':
		case 'H':
		case '?':
				help();
				break;

		case 'e':
		case 'E':
				exit(0);
	  
			 default:
				break;
		 
     }
	       }while(1);
          }



// output:
 //$:>c Hii

// $:>c Wellcome in k.k.wagh college

 //$:>c have a nice day                   

// $:>c good bye

 //$:>c It is a first practical

 //$:>p

 //1. Hii
 //2. Wellcome in k.k.wagh college
 //3. have a nice day
 //4. good bye
 //5. It is a first practical
// $:>i have nice day

 //$:>p

 //1. Hii
 //2.have nice day
 //3. Wellcome in k.k.wagh college
 //4. have a nice day
 //5. good bye
 //6. It is a first practical
 //$:>m 6 5

 //$:>
 //$:>p

 //1. Hii
 //2.have nice day
 //3. Wellcome in k.k.wagh college
 //4. have a nice day
 //5. It is a first practical
// 6. good bye
 //$:>r 4 3

 //$:>
 //$:>p

 //1. Hii
 //2.have nice day
 //3. have a nice day
 //4. Wellcome in k.k.wagh college
 //5. have a nice day
 //6. It is a first practical
 //7. good bye
 //$:>d 5

 //$:>p

 //1. Hii
 //2.have nice day
 //3. have a nice day
 //4. Wellcome in k.k.wagh college
 //5. It is a first practical
 //6. good bye
 //$:>p 2 3

 //4. Wellcome in k.k.wagh college
 //$:>
 //$:>p

 //1. Hii
 //2.have nice day
 //3. have a nice day
 //4. Wellcome in k.k.wagh college
 //5. It is a first practical
 //6. good bye
 //$:>i 2 most welcome

 //$:>p

 //1. Hii
 //2. most welcome
 //3.have nice day
 //4. have a nice day
 //5. Wellcome in k.k.wagh college
 //6. It is a first practical
 //7. good bye
 //$:>i 7 Thank u so much

 //$:>p

 //1. Hii
 //2. most welcome
 ///3.have nice day
 //4. have a nice day
 //5. Wellcome in k.k.wagh college
 //6. It is a first practical
 //7. Thank u so much
 //8. good bye
 //$:>a  Thank u so much

 //$:>p

 //1. Hii
 //2. most welcome
 //3.have nice day
 //4. have a nice day
 //5. Wellcome in k.k.wagh college
 //6. It is a first practical
 //7. Thank u so much
 //8. good bye
 //9.  Thank u so much
 //$:>i 3 Wellcome in k.k. wagh college

 //$:>p

 //1. Hii
 //2. most welcome
 //3. Wellcome in k.k. wagh college
 //4.have nice day
 //5. have a nice day
 //6. Wellcome in k.k.wagh college
 //7. It is a first practical
 //8. Thank u so much
 //9. good bye
 //10.  Thank u so much
 //$:>


