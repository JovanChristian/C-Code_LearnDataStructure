#include<stdio.h>
#include<stdlib.h>

struct node{
	int value;
	node* next;
	node* prev;
}*head, *tail;

node* createNewnode(int value){
	node* Newnode = (node*) malloc(sizeof(node));
	Newnode->value = value; 
	Newnode->next = NULL;
	Newnode->prev = NULL;
	return Newnode;
} 

void printLL(){
	
	node* temp = head;
	while(temp != NULL){
		printf("%d -> ", temp->value);
		temp = temp->next;
	}
}
void pushHead(int value){
	
	node* Newnode = createNewnode(value);
	if(head == NULL){
		head = tail = Newnode;
	}else{ 
	Newnode->next = head;
	head->prev = Newnode;
	head = Newnode;
	}
} 

void pushTail(int value){
	
	node* Newnode = createNewnode(value); 
	if(head == NULL){
		head = tail = Newnode;
	}else{
		tail->next = Newnode;
		Newnode->prev = tail;
		tail= Newnode;
	}
} 

void pushMid(int value){
	
	node* Newnode = createNewnode(value);
	if(head == NULL){
		head = tail = Newnode;
	}else if(value < head->value){
		pushHead(value);
	}else if(value > tail->value){
		pushTail(value);
	}else{
		node* temp = head;
		while(temp->next->value < value){
			temp = temp->next;
		}
		Newnode->next = temp->next;
		Newnode->prev = temp;
		temp->next = Newnode;
		Newnode->next->prev = Newnode;
	} 
}
	
void search(int value){
	if(head == NULL){
		printf("Linked list is empty!\n");
	} else if(value == head->value){
		printf("Value found (head)\n");
	} else if(value == tail->value){
		printf("Value found (tail)\n");
	}else{
		int index = 0;
		node* temp = head;
		while(temp->value != value && temp != tail){
			temp = temp->next;
			index++;
		}
		if(temp->value == value){
			printf("Value found (idx : %d)\n", index);
		} else{
			printf("There is no %d inside the Linked List\n", value);
		}
	}
}	
int main(){
	
	pushMid(100);
	pushMid(90);
	pushMid(80);
	pushMid(70);
	pushMid(60);
	pushMid(50);
	pushMid(40);
	pushMid(30);
	pushMid(20); 
	pushMid(10);
	
	search(50);
	search(200);
	
	printLL();
	return 0;
}
