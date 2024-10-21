#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Node{
	int prio;
	char move[100];
	Node* next;
}*head;
 
Node *createNewNode(int prio, char move[]){
	Node *temp = (Node*) malloc(sizeof(struct Node));
	temp->prio = prio;
	strcpy(temp->move,move);
	temp->next = NULL;
	return temp;
}

void pushMid(char prio[], char move[]){
	int prio2=0;
	
	if(strcmp(prio, "CRITICAL")==0){
		prio2 =1;	
	}else if(strcmp(prio, "HIGH")==0){
		prio2 = 2;
	}else if(strcmp(prio, "NORMAL")==0){
		prio2 = 3;
	}else if(strcmp(prio, "LOW")==0){
		prio2 = 4;
	} 
	
	Node *NewNode = createNewNode(prio2,move);
	if(!head){
		head = NewNode;
		return;
	}
		if(prio2 < head->prio){
		NewNode->next = head;
		head = NewNode;
		return;
	}
	Node *temp = head;
	while(temp->next != NULL && temp->next->prio <= prio2){
		temp = temp->next;
	} 
	NewNode->next = temp->next;
	temp->next = NewNode;
} 

void print(){
	
	Node *temp = head;
	int x =0, y=0;
	while(temp){
		if(strcmp(temp->move, "up")==0){
			y = y+1;
		}else if(strcmp(temp->move, "right")==0){
			x = x+1;
		}else if(strcmp(temp->move, "down")==0){
			if(y-1<0){
				y = 0; 
			}else{
			y = y-1;	
			}
		}else if(strcmp(temp->move, "left")==0){
			if(x-1<0){
				x = 0;
			}else{
				x = x-1;
			}
		}
		printf("%d %d\n",x,y);
		temp = temp->next;
	}
	printf("final position : X = %d , Y = %d\n",x,y);
}
int main(){
	
	char validate[10];
	char prio[20];
	char move[10];
	while(1){
		printf("Do you want to input?\n");
		scanf("%s",validate); getchar();
		if(strcmp(validate,"Yes")==0||strcmp(validate,"yes")==0 ||strcmp(validate,"YES")==0 ){
			
			scanf("%s %s", prio, move);getchar(); 		
			pushMid(prio,move);
		}else{
			print();
			break;
		}
	}
	return 0;
} 
