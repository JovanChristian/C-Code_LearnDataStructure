#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct cust{
	char name[200];
	int prio;
	cust *next;
	cust *prev;
}*head, *tail;

cust *newcust(int prio, char *name){
	cust *temp = (cust*) malloc(sizeof(cust));
	temp->prio = prio;
	strcpy(temp->name, name);
	temp->next = NULL;
	temp->prev = NULL;
	return temp;
}

void Insert(cust *newcust){
	
	if(!head){
		head = tail = newcust;
	}
	else if(newcust->prio < head->prio){
		cust *temp = head;
		head = newcust;
		head->next = temp;
		temp->prev = head;
	}
	else if(newcust->prio >= tail->prio){
		cust *temp = tail;
		tail = newcust;
		tail->prev = temp;
		temp->next = tail;
	}
	else{
		cust *curr = head;
		while(curr->next && (newcust->prio < head->prio)){
			curr = curr->next;
		}
		cust *temp = curr;
		newcust->next = curr->next;
		curr->next->prev = newcust;
		curr->next = newcust;
		temp->prev = curr;
	}
}

void printAll(){
	
	if(!head){
		return;
	}
	else{
		while(head){
			if(head->prio == 1){
				printf("Attention! %s is being served at VVIP table.\n", head->name);	
			}
			else if(head->prio == 2){
				printf("Attention! %s is being served at VIP table.\n", head->name);	
			}
			else if(head->prio == 3){
				printf("Attention! %s is being served at Regular table.\n", head->name);	
			}
			else if(head->prio == 4){
				printf("Attention! %s is being served at Regular table.\n", head->name);	
			}
			cust *temp = head;
			head = head->next;
			free(temp);
		}
		puts("");
	}
} 

void print1(){
	
		
	if(!head){
		return;
	}
	else{
	
			if(head->prio == 1){
				printf("Attention! %s is being served at VVIP table.\n", head->name);	
			}
			else if(head->prio == 2){
				printf("Attention! %s is being served at VIP table.\n", head->name);	
			}
			else if(head->prio == 3){
				printf("Attention! %s is being served at Regular table.\n", head->name);	
			}
			else if(head->prio == 4){
				printf("Attention! %s is being served at Regular table.\n", head->name);	
			}
			cust *temp = head;
			head = head->next;
			free(temp);
		
		puts("");
	}
}
void dismiss(){
	
	if(!head){
		head = tail = NULL;
		free(head);
		puts("End of the day!!");
	}
}
int main(){
	
	return 0;
}
