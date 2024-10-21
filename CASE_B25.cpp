#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct cust{
	char name[200];
	int prio;
	cust *next;
	cust *prev;
}*head, *tail;

cust *newcust(char *name, int prio){
	cust *temp = (cust*) malloc(sizeof(cust));
	strcpy(temp->name,name);
	temp->prio = prio;
	temp->next =NULL;
	temp->prev = NULL;
	return temp;
}

void Insert(cust *newcust){
	if(!head){
		head = tail = newcust;
	}else{
		//VVIP = 1
		//VIP = 2
		//MEMBER =3
		//GUEST = 4
		if(newcust->prio < head->prio){
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
		}else{
			cust *curr = head;
			while(curr->next && (newcust->prio < curr->prio)){
				curr= curr->next;
			}
			cust *temp = curr;
			newcust->next = curr->next;
			curr->next->prev = newcust;
			curr->next = newcust;
			newcust->prev = curr;
		}
	}
} 

void printAll(){
	
	if(!head){
		return;
	}else{
	while(head){
		if(head->prio == 1){
			printf("Attention! %s is being served at VVIP table.\n", head->name);
		}else if(head->prio == 2){
			printf("Attention! %s is being served at VIP table.\n", head->name);
		}else if(head->prio == 3){
			printf("Attention! %s is being served at regular table.\n", head->name);
		}else if(head->prio == 4){
			printf("Attention! %s is being served at regular table.\n", head->name);
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
	}else{
		if(head->prio == 1){
			printf("Attention! %s is being served at VVIP table.\n", head->name);
		}else if(head->prio == 2){
			printf("Attention! %s is being served at VIP table.\n", head->name);
		}else if(head->prio == 3){
			printf("Attention! %s is being served at regular table.\n", head->name);
		}else if(head->prio == 4){
			printf("Attention! %s is being served at regular table.\n", head->name);
		}
		cust *temp = head;
		head = head->next;
		free(temp);
	
	puts("");		
	}
} 


void waitingLine(){
	puts("Waiting Lines:");
	if(!head){
		puts("Queue is Empty");
	}else{
		cust *curr = head;
		int number = 1;
		while(curr){
			printf("%d. %s\n", number, curr->name);
			curr = curr->next;
			number++;
		}
	}
	puts("");
}

void dismiss(){
	if(!head){
		head = tail = NULL;
		free(head);
		puts("End of the Day!");
	}
}

int main(){
	while(1){
	system("cls");	
	puts("============================");
	puts("SUNIB Restaurant Reservation");
	puts("============================\n");	
	
	
	waitingLine();
	puts("1. Add Customer to Queue");
	puts("2. Serve One");
	puts("3. Serve All");
	puts("4. Dismiss Queue");
	puts("0. Exit");
	
	int choose = -1;
	do{
	printf("Input menu Number: ");
	scanf("%d", &choose); getchar();
	
	}while((choose < 0 )|| (choose > 4));
	
	if(choose == 1){
		char status[200]; 
		char name[200];
		
		scanf("%s %[^\n]", status, name);getchar();
		
		int prio;
		if(strcmp("VVIP", status)==0){
			prio = 1;
		}
		else if(strcmp("VIP", status)==0){
			prio = 2;
		}
		else if(strcmp("Member", status)==0){
			prio = 3;
		}
		else if(strcmp("Guest", status)==0){
			prio = 4;
		}
		Insert(newcust(name, prio));
	}else if(choose == 2){
		print1();
		getchar();
	}else if(choose == 3){
		printAll();
		getchar();
	}else if(choose == 4){
		dismiss();
		getchar();
	}else if(choose ==0){
		break;
	}
}
	return 0;
}
