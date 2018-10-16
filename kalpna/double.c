#include<stdio.h>
#include<stdlib.h>
struct Node  {
        int data;
        struct Node* ptr_next;
        struct Node* ptr_next_next;
};


void InsertAtTail(int x);
void Print();
void delete_end();
void node_swap(struct Node *ptr, struct Node *head);



struct Node* head; 


struct Node* GetNewNode(int x) {
	struct Node* newNode
		= (struct Node*)malloc(sizeof(struct Node));
	newNode->data = x;
	newNode->ptr_next_next = NULL;
	newNode->ptr_next = NULL;
	return newNode;
}

void InsertAtTail(int x) {
	struct Node* temp = head;
	struct Node* newNode = GetNewNode(x);
	if(head == NULL) {
		head = newNode;
		return;
	}
	while(temp->ptr_next != NULL) temp = temp->ptr_next; 
	temp->ptr_next = newNode;
	temp->ptr_next_next = newNode->ptr_next;
}


void Print() {
	struct Node* temp = head;
	while(temp != NULL) {
		printf("%d ",temp->data);
		temp = temp->ptr_next;
	}
	printf("\n");
	}

void delete_end()
{
         struct Node* temp;
         struct Node *end;

        temp=head;
        while(temp->ptr_next!=NULL)
        {
                end=temp;
                temp=temp->ptr_next;
        }
        end->ptr_next=NULL;
	end->ptr_next_next=NULL;
        free(temp);
}

void node_swap(struct Node *ptr, struct Node *head)
{
  	struct Node *tmp;
	struct Node *cur;
	struct Node *nxt;
	struct Node *prv;
	if(head->ptr_next==NULL)
	{
		printf("dont swap");
		}
		cur=head;
		nxt=head->ptr_next;
		prv=head;
		if(head==ptr)
		{
		
		cur->ptr_next=nxt->ptr_next;
		nxt->ptr_next=cur;
		cur->ptr_next_next=nxt->ptr_next_next;
		nxt->ptr_next_next=cur->ptr_next;
		head=nxt;
	}
	else
	{
		cur=head->ptr_next;
		nxt=cur->ptr_next;
		while(cur->ptr_next_next)
		if(cur==ptr)
	{
		break;
	}
	else{
		prv=cur;
		cur=nxt;
		nxt=nxt->ptr_next;
	}
		}
		prv->ptr_next=nxt;
		prv->ptr_next_next=cur;
		cur->ptr_next=nxt->ptr_next;
		nxt->ptr_next=cur;
		cur->ptr_next_next=nxt->ptr_next_next;
		nxt->ptr_next_next=cur->ptr_next;
	}



struct Node *addr(int num,struct Node *head)
{
struct Node *tmp = head;
	int i;
	for(i=0;(i<num)&&(tmp);i++)
		{ 
			tmp=tmp->ptr_next;
		}
		if(tmp=NULL)
		printf("node is not present");
		else
		return tmp;
}

int main() {

	
//	head = NULL; 
//	 struct Node *start = NULL;
	 struct Node *ptr = NULL;
	InsertAtTail(1);
	InsertAtTail(2);
	InsertAtTail(3);
	InsertAtTail(4);
	InsertAtTail(5);
	InsertAtTail(6);
	InsertAtTail(7);
	InsertAtTail(8);
	InsertAtTail(9);
	InsertAtTail(10); 
	Print();
         //ptr = addr(2,head);
	 //node_swap(ptr,head);
	//Print();
	delete_end(); 
	Print();
	
}
