#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define size 10

struct data{
	int age;
	char name[200];
	data* next;
}*hashTable[size];

data* NewNode(int age, char name[]){ 

	data* node = (data*) malloc(sizeof(data)); 
	node->age = age;
	strcpy(node->name, name);
	node->next = NULL;
	return node; 	
}

int hashing(char name[]){
	int key = 0;
	int len = strlen (name);
	for(int i=0; i< len; i++){
		key += name[i];
	}
	return key%size;
}

void InsertData(int age, char name[]){
	
	int key = hashing(name); 
	if(!hashTable){
		hashTable[key] = NewNode(age, name);
	} else{
	data* node = NewNode(age, name);
	node->next = hashTable[key];
	hashTable[key] = node;
	}
}

void DeleteData(char name[]){
	
	int key = hashing(name);
	if(hashTable[key] && strcmp(hashTable[key]->name, name)==0){
		data* temp = hashTable[key];
		hashTable[key] = hashTable[key]->next;
		free(temp);
	}else {
		if(hashTable[key]){
			if(hashTable[key]->next){
				data* temp = hashTable[key];
				
				while(temp->next && strcmp(temp->next->name, name)==0){
					temp = temp->next;
				}
				if(temp->next){
					data* Delete = temp->next;
					temp->next = Delete->next;
					free(Delete);
				}
				else{
					printf("Data Not Found\n");
				}
			}
		}
	}
}

void ViewData(){
	for(int i=0; i<size; i++){
		if(hashTable[i]){
			printf("%d. %s %d", i+1, hashTable[i]->name, hashTable[i]->age);
			if(hashTable[i]->next){
				data* temp = hashTable[i]->next;
				while(temp){
					printf(" -> %s %d", temp->name, temp->age);
					temp = temp->next;
				}
			}
			printf("\n");
		} else{
			printf("%d. Empty\n", i+1);
		}
	}
}
int main(){
	
	InsertData(20, "Alexs");
	InsertData(40, "Felix");
	InsertData(15, "Xilef");
	InsertData(10, "Budi");
	DeleteData("Felix");
	DeleteData("Alexs");
	DeleteData("Xilef");
	DeleteData("Budi");
	ViewData();
	return 0;
}
