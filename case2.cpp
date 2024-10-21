#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
	char sent[200];
	node* next;
}*head, *tail;

node* createNewNode (char sent[]){
	
	node *NewNode = (node*) malloc(sizeof(node));
	
	strcpy(NewNode->sent, sent); 
	NewNode-> next = NULL;
	return NewNode;
} 

void pushTail(char sent[]){
	if(!head){
		struct node* Node = createNewNode(sent);
		head= tail = Node;
	}
	else{
		struct node* Node = createNewNode(sent);
		Node->next = head;
		head= Node;
	}
} 

void popTail(char sent[]){
	if(!head){
		printf("There is no Data\n");
	}else if(head == tail){
		free(head);
		head = tail = NULL;
	}else{
		struct node* temp = head;
		while(temp->next != tail){
			temp = temp->next;
		} 
		free(tail);
		tail= temp;
		tail->next = NULL;
	} 
}

void ViewAll(){
	
	struct node* temp = head;
	while(temp){
		printf("%s ", temp->sent);
		node* curr = temp;
		head = temp->next;
		temp= temp->next;
		free(curr);
		curr= NULL;
	}
}


int main(){
	char word[500];
	char temp[500];
	char cont[200];
	int n=0;
	
	printf("Reverse Sentence\n");
	printf("================\n");
	printf("\n");
	do{
	printf("Input sentence[minimum 5 words]: ");
	scanf("%[^\n]", word); getchar();
	strcpy(temp, word);
	char *count = strtok(temp, " ");
	while(count){		
		n++;
		count = strtok(NULL, " ");
	}
	if(n<5){
		n=0;
	}
	}while(n<5);
	
	char *input = strtok(word, " ");
	while(input){
		pushTail(strrev(input));
		input = strtok(NULL, " ");
	}
	ViewAll();
	
	printf("\nDo you want to continue [yes|no]? %s");
	scanf("%s", cont);
	if(strcmp(cont, "yes")==0){
		main();
	}else{
		exit(0);
	}	
	
	return 0;
}
