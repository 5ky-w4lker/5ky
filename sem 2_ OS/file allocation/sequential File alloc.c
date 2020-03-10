//File Allocation Methods- Sequential File Allocation
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct allocated_blocks
{
    char name[20];
    int start,len,flag;
    struct allocated_blocks *next;
}DIR;
typedef struct free_blocks
{
    int start,len;
    struct free_blocks *next;
}NODE;
int d;
DIR *head,*last;
NODE *head1,*last1;
void disp_free_blocks()
{
    NODE *temp;
    printf("\nFree blocks list");
    printf("\nStart\tLength");
    temp = head1;
    while(temp!=NULL)
    {
        printf("\n%d\t%d",temp->start,temp->len);
        temp=temp->next;
    }
}
void disp_allocated_blocks()
{
    DIR *temp;
    printf("\nDir List");
    printf("\nName\tStart\tLength");
    temp=head;
    while(temp!=NULL)
    {
        if(temp->flag==0)
            printf("\n%s\t%d\t%d",temp->name,temp->start,temp->len);
        temp=temp->next;
    }
}
main ()
{
    int ch,tno;
    char tfn[20];
    NODE *temp;
    DIR *newn;
    system("clear");
    printf("Enter no.of disk blocks:");
    scanf("%d",&d);
    head1 = last1 = (NODE*)malloc(sizeof(NODE)); // ************************
    head1->start = 0;
    head1->len = d;
    head1->next = NULL;
    while(1)
    {
        printf("\n1.Insertion\n2.Deletion\n3.Display\n4.Exit\nEnter your choice (1-4):");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
            printf("Enter file name:");
            scanf("%s",tfn);
            printf("Enter file size in no.of blocks:");
            scanf("%d",&tno);
            temp = head1;
            while(temp!=NULL)
            {
                if(temp->len >= tno) break;
                temp=temp->next;
            }
            if(temp==NULL)
            {
                printf("Failed to create file %s\n",tfn);
            }
            else
            {
                newn = (DIR*)malloc(sizeof(DIR));
                strcpy(newn->name,tfn);
                newn->len = tno;
                newn->start = temp->start;
                newn->flag = 0;
                newn->next = NULL;
                if(head==NULL) head=newn;
                else last->next = newn;
                last = newn;
                temp->start += tno;
                temp->len -= tno;
                printf("File %s created successfully.\n",tfn);
            }
            break;
        case 2:
            printf("Enter file name you want to delete:");
            scanf("%s",tfn);
            newn = head;
            while(newn!=NULL)
            {
                if(strcmp(newn->name,tfn)==0 && newn->flag==0) break;
                newn=newn->next;
            }
            if(newn==NULL)
            {
                printf("File %s not found.\n",tfn);
            }
            else
            {
                newn->flag = 1;
                temp = (NODE*)malloc(sizeof(NODE));
                temp->start = newn->start;
                temp->len = newn->len;
                temp->next = NULL;
                last1->next = temp;
                last1 = temp;
                printf("File %s deleted successfully.\n",tfn);
            }
            break;
        case 3:
            disp_allocated_blocks();
            disp_free_blocks();
                  break;
        case 4:
            exit(0);
        }
    }
}
/************output*****************/
/*
pc95@pc95-HP-dx2480-MT-FN870PA:~$ ./a.out
Enter no.of disk blocks:5
1.Insertion
2.Deletion
3.Display
4.Exit
Enter your choice (1-4):1
Enter file name:a.txt
Enter file size in no.of blocks:2
File a.txt created successfully.
1.Insertion
2.Deletion
3.Display
4.Exit
Enter your choice (1-4):1
Enter file name:b.txt
Enter file size in no.of blocks:2
File b.txt created successfully.
1.Insertion
2.Deletion
3.Display
4.Exit
Enter your choice (1-4):3
Dir List
Name    Start    Length
a.txt    0    2
b.txt    2    2
Free blocks list
Start    Length
4    1
1.Insertion
2.Deletion
3.Display
4.Exit
Enter your choice (1-4):1
Enter file name:c.txt
Enter file size in no.of blocks:1
File c.txt created successfully.
1.Insertion
2.Deletion
3.Display
4.Exit
Enter your choice (1-4):3
Dir List
Name    Start    Length
a.txt    0    2
b.txt    2    2
c.txt    4    1
Free blocks list
Start    Length
5    0
1.Insertion
2.Deletion
3.Display
4.Exit
Enter your choice (1-4):2
Enter file name you want to delete:b.txt
File b.txt deleted successfully.
1.Insertion
2.Deletion
3.Display
4.Exit
Enter your choice (1-4):3
Dir List
Name    Start    Length
a.txt    0    2
c.txt    4    1
Free blocks list
Start    Length
5    0
2    2
1.Insertion
2.Deletion
3.Display
4.Exit
Enter your choice (1-4):2
Enter file name you want to delete:c.txt
File c.txt deleted successfully.
1.Insertion
2.Deletion
3.Display
4.Exit
Enter your choice (1-4):3
Dir List
Name    Start    Length
a.txt    0    2
Free blocks list
Start    Length
5    0
2    2
4    1
1.Insertion
2.Deletion
3.Display
4.Exit
*/

