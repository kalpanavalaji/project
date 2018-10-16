#include<stdio.h>
#include<stdlib.h>
void insert_end(int);
void dislay();
void delete_end();
struct node
{
	int data;
	struct node *next;
	struct node *prev;
};struct node* start;
	struct node* end;
struct node* getnode(int ele)
{
	struct node* newnode= (struct node*)malloc(sizeof(struct node));

        newnode->data=ele;
        newnode->next=NULL;
        newnode->prev=NULL;
	return newnode;	
}



void insert_end(int ele)
{	
	struct node* newnode;
	struct node* temp;	 

	newnode=getnode(ele);

	if(start==NULL)
	{
		
		start=newnode;
	}
	else
	{
	end->next=newnode;
	newnode->prev=end;
	end=newnode;
	}
	
}
void delete_end()
{
	 struct node* ptr;
	 struct node *end;

	ptr=start;
	while(ptr->next!=NULL)
	{
		end=ptr;
		ptr=ptr->next;
	}
	end->next=NULL;
	free(ptr);
}
void display()
	{
	struct node *ptr=NULL;
	ptr=start;
	while(ptr!=NULL)
	{
	printf("%d\n",ptr->data);
	ptr=ptr->next;
	}
}
	
/*int main()
{
	start=NULL;
	int ch;
	char ans='y';
	while(ans=='y'||ans=='Y')
	{
		printf("1 insert node at end\n");
		printf("2 delete node at end\n");
		printf("enter number\n");
		scanf("%d\n",&ch);
	switch(ch)
	{
	case 1:
		printf("insert node end");
		insert_end(6);
		display();
		break;
	case 2:
		printf("delete node");
		delete_end();
		display();
		break;

	default:
		printf("exit");
		break;
	}
	
	 printf("do you want to continue press y");
        scanf("%c",&ans);

	
	}
}*/
int main()
{
	start=NULL;
	insert_end(5);
	display();	
	insert_end(6);
	display();
	insert_end(7);
	display();
	delete_end();
	display();
	
}	
