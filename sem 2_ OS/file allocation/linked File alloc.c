//File Allocation Methods- Linked File Allocation 
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
typedef struct file_allocation_table 
{ 
    char name[20]; 
    int start,end,flag; 
    struct file_allocation_table *link; 
}DIR; 
int d,fat[200],free_blocks; 
DIR *first,*last; 
void disp_dir() 
{ 
    DIR *p; 
    printf("\nDir List"); 
    printf("\nName\tStart\tEnd"); 
    p=first; 
    while(p!=NULL) 
    { 
        if(p->flag==0) 
            printf("\n%s\t%d\t%d",p->name,p->start,p->end); 
        p=p->link; 
    } 
} 
main () 
{ 
    int ch,tno,i,j; 
    char tfn[20]; 
    DIR *q; 
    //clrscr(); 
    system("clear"); 
    printf("Enter no.of disk blocks:"); 
    scanf("%d",&d); 
    for(i=0;i<d;i++) 
        fat[i]=-999;     
    free_blocks=d; 
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
            if(tno<=free_blocks) 
            { 
                for(i=0;i<d;i++) 
                { 
                    if(fat[i]==-999) 
                    { 
                        tno--; 
                        break; 
                    } 
                } 
                q = (DIR*)malloc(sizeof(DIR)); 
                strcpy(q->name,tfn); 
                q->flag = 0; 
                q->start = j = i; 
                i++; 
                while(tno!=0) 
                { 
                    if(fat[i]==-999) 
                    { 
                        fat[j]=i; 
                        j=i; 
                        tno--; 
                    } 
                    i++; 
                } 
                fat[j]=-1; 
                q->end=j; 
                q->link=NULL; 
                if(first==NULL) first = q; 
                else last->link = q; 
                last = q; 
                printf("File %s created successfully.\n",tfn); 
                free_blocks-=tno; 
            } 
            else 
            { 
                printf("Failed to create file %s\n",tfn); 
            } 
            break; 
        case 2: 
            printf("Enter file name you want to delete:"); 
            scanf("%s",tfn); 
            q = first; 
            while(q!=NULL) 
            { 
                if(strcmp(q->name,tfn)==0 && q->flag==0) break; 
                q=q->link; 
            } 
            if(q==NULL) 
            { 
                printf("File %s not found.\n",tfn); 
            } 
            else 
            { 
                q->flag = 1; 
                i=q->start; 
                tno=0; 
                while(i!=-1) 
                { 
                    j=fat[i]; 
                    fat[i]=-999; 
                    i=j; 
                    tno++; 
                    printf("Hello!\n"); 
                } 
                printf("File %s deleted successfully.\n",tfn); 
                free_blocks+=tno; 
            } 
            break; 
        case 3: 
            disp_dir(); 
            break; 
        case 4: 
            exit(0);  
        } 
    } 
} 
/******output****/ 
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
Name    Start    End 
a.txt    0    1 
b.txt    2    3 
c.txt    4    4 
1.Insertion 
2.Deletion 
3.Display 
4.Exit 
Enter your choice (1-4):2 
Enter file name you want to delete:a.txt 
Hello! 
Hello! 
File a.txt deleted successfully. 
1.Insertion 
2.Deletion 
3.Display 
4.Exit 
Enter your choice (1-4):3 
Dir List 
Name    Start    End 
b.txt    2    3 
c.txt    4    4 
1.Insertion 
2.Deletion 
3.Display 
4.Exit 
Enter your choice (1-4):2 
Enter file name you want to delete:c.txt 
Hello! 
File c.txt deleted successfully. 
1.Insertion 
2.Deletion 
3.Display 
4.Exit 
Enter your choice (1-4):3 
Dir List 
Name    Start    End 
b.txt    2    3 
1.Insertion 
2.Deletion 
3.Display 
4.Exit 
Enter your choice (1-4):1 
Enter file name:d.txt 
Enter file size in no.of blocks:3 
File d.txt created successfully. 
1.Insertion 
2.Deletion 
3.Display 
4.Exit 
Enter your choice (1-4):3 
Dir List 
Name    Start    End 
b.txt    2    3 
d.txt    0    4 
1.Insertion 
2.Deletion 
3.Display 
4.Exit 
Enter your choice (1-4):4 
*/ 
