#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data{
	char name[200];
	int value;
	data* next;
	data* prev;
}*head, *tail;

data* newNode(char name[], int value){
	data* temp = (data*) malloc(sizeof(data)); 
	strcpy(temp->name, name);
	temp->value = value;
	temp->next = NULL;
	temp->prev = NULL;
	return temp;
} 

void pushHead(char *name, int value){
	
	if(!head){
		data *temp = newNode(name, value);
		head = tail = temp;
	} else{
		data *temp = newNode(name, value); 
		temp->next = head;
		head = temp;
	}
} 

void pushTail(char *name, int value){
	
	if(!head){
		data *temp = newNode(name, value);
		head = tail = temp;
	}else {
		data *temp = newNode(name, value);
		tail->next = temp;
		tail = temp;
	}
} 

void pushMid(char *name, int value){
	
	if(!head){
		data *temp = newNode(name, value);
		head = tail = temp;
	}else if(head->value > value){
		pushHead(name, value);
	}else if(tail->value < value){
		pushTail(name, value);
	}else {
		data *curr = head;
		while(curr->next && curr->next->value <= value){
			curr = curr->next;
		}
		data *temp = newNode(name, value);
		temp->next = curr->next;
		curr->next = temp;
	}
} 

void enqueue(char *name, int value){
	data *temp = newNode(name, value);
	if(!head){
		head = tail = temp;
	}else {
		if(value < head->value){
			pushHead(name, value);
		}else if(value > head->value){
			pushTail(name, value);
		}
		else{
			data *curr = tail;
			while(curr->value > value){
				curr = curr->prev;
			}
			temp->prev = curr;
			temp->next = curr->next;
			temp->next->prev = temp;
			curr->next = temp;
		}
	}
}

void dequeue(char *name, int value){
	
	if(!head){
		data *curr = head;
		head = head->next;
		curr->next = head->prev = NULL;
		free(curr);
	}
} 

void peek(){
	if(!head){
		printf("Peek (First Data) : %s %d\n", head->name, head->value);
	} 
	
}
void popHead(){
	
	if(!head){
		printf("There is no data . .\n");
	} 
	else if (head == tail){
		free(head);
		head = tail = NULL;
	} else {
		data *curr = head;
		head = head->next;
		free(curr);
	}
}

void popTail(){
	
	if(!head){
		printf("There is no data . .\n");
	} 
	else if(head == tail){
		free(head);
		head = tail = NULL;
	} else{
		data *curr = head;
		while(curr->next != tail){
			curr = curr->next;
		}
		free(tail);
		tail = curr;
		curr->next = NULL;
	}
} 

void popMid(int value){
	
	if(!head){
		printf("There is no data . .\n");
	}else if(head == tail){
		free(head);
		head = tail = NULL;
	}else if(head->value == value){
		popHead();
	}else if(tail->value == value){
		popTail();
	}else{
		data *curr = head;
		while(curr->next && curr->next->value != value){
			curr = curr->next;
		}
		if(curr->next == NULL){
			printf("There is no data . .\n");
		} else {
			data *Delete = curr->next;
			curr->next = Delete->next;
			free(Delete);
		}
	}
}

void search(int value){
	
	if(!head){
		printf("There is no data . . .\n");
	}else if(head == tail && head->value == value){
		printf("FOUND : %s - %d\n", head->name, head->value);
	}else if(head->value == value){
		printf("FOUND : %s - %d\n", head->name, head->value);
	}else if(tail->value, value){
		printf("FOUND : %s - %d\n", tail->name, tail->value);
	}else {
		data *curr = head;
		while(curr->next && curr->next->value != value){
			curr = curr->next;
		}
		if(!curr->next){
			printf("There is no data . .\n");
		} else{
			printf("FOUND : %s - %d", curr->next->name, curr->next->value);
		}
	}
}

void ViewAll(){
	
	data *temp = head;
	while(temp){
		printf("%s - %d\n", temp->name, temp->value);
		temp = temp->next;
	}
}
int main(){
	
	// Push Head -> Tempel Depan
    pushHead("Felix", 15);
    pushHead("Budi", 12);
    // Push Tail -> Tempel Belakang
    pushTail("Anton", 33);
    pushTail("Josua", 50);
    pushTail("Anderson", 80);
    // Untuk Insert Data PushMid datanya harus urut terlebih dahulu (disini age-nya yang berurut)
    pushMid("felix2", 70);
    pushMid("Julieta", 60);
    pushMid("Michell", 40); 
    
    popHead(); // Data Pertama Hilang
    popTail(); // Data Terakhir Hilang
    
    popMid(50); // Membuang Age 50 (Kondisi Age 50 Tidak Ada)
    popMid(80); // Membuang Age 80
    
    search(35); // Mencari Age 35 (Kondisi Age 35 Tidak Ada)
    search(33); // Mencari Age 33
    
    ViewAll(); 
    
	return 0;
}
