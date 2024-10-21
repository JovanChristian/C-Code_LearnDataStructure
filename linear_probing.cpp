#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define size 10

struct data{
	int age;
	char name[200];
}*hashTable[size];

data* init(char name[], int age){
	data* node = (data*) malloc(sizeof(data));
	strcpy(node->name, name);
	node->age = age;
	return node;
} 

int hashing(char name[]){
	
	int key = 0;
	int len = strlen(name); 
	for(int i=0; i<len; i++){
		key += name[i];
	}
	return key%size;
}

void InsertData(char name[], int age){
	
	int key = hashing(name);
	int pos = key;
	if(!hashTable[key]){
		hashTable[key] = init(name, age);
	} else{
		do{
			pos = (pos + 1)%size;
			if(!hashTable[pos]){
				hashTable[pos] = init(name, age);
				break;
			}
		}while(key!=pos);
		if(key == pos){
			printf("HashTable Already FULL\n");
		}
	}
} 

void DeleteData(char name[]){
	
	int key = hashing(name);
	int pos = key;
	
	if(hashTable[key] && strcmp(hashTable[key]->name, name)==0){
		free(hashTable[key]);
		hashTable[key] = NULL;
	} else{
		do{
			pos = (pos + 1)%size;
			if(hashTable[pos] && strcmp(hashTable[pos]->name, name)==0){
				free(hashTable[pos]);
				hashTable[pos] = NULL;
				break;
			}
		}while( key!=pos);
			if(key == pos){
				printf("Data not Found\n");
			}
	}
} 

void ViewData(){
	
	for(int i=0; i<size; i++){
		if(hashTable[i]){
			printf("%d. %s %d\n", i+1, hashTable[i]->name, hashTable[i]->age);
		} else{
			printf("%d. Empty\n", i+1);
		}
	}
}
int main(){
	
	InsertData("alexs", 20);
	InsertData("felix", 30);
	InsertData("xilef", 15);
	DeleteData("alexshbh");
//	DeleteData("felix");

	ViewData();
	return 0;
}
