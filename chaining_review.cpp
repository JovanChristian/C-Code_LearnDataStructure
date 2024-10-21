#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define size 15

struct data{
	int page;
	char book [200];
	data* next;
}*hashTable[size];

data* init(char book[], int page){
	data* NewNode = (data*) malloc(sizeof(data));
	strcpy(NewNode->book, book);
	NewNode->page = page;
	NewNode->next= NULL;
	return NewNode;
} 

int hashing(char book[]){
	int key =0;
	int len = strlen(book);
	for(int i=0; i<len; i++){
		key+= book[i];
	}
	return key%size;
} 

void pushData(char book[], int page){
	
	int key = hashing (book);
	if(!hashTable[key]){
		hashTable[key] = init(book, page);
	}else{
		data* NewNode = init(book, page);
		NewNode->next = hashTable[key];
		hashTable[key] = NewNode;
	}
} 

void popData(char book[]){
	int key = hashing(book);
	
	if(hashTable[key] && strcmp(hashTable[key]->book, book)==0){
		data* temp = hashTable[key];
		hashTable[key] = hashTable[key]->next;
		free(temp);
	}else{
		if(hashTable[key]){
			if(hashTable[key]->next){
				data* temp = hashTable[key];
				while(temp && strcmp(temp->next->book, book)==0){
					temp = temp->next;
				}
				if(temp->next){
					data* Delete = temp->next;
					temp->next = Delete->next;
					free(Delete);
				}else{
					printf("Data Not Found\n");
				}
			}
		}
	}
} 

void ViewData(){
	for(int i=0; i<size; i++){
		if(hashTable[i]){
			printf("%d. Title : %s  page : %d", i+1, hashTable[i]->book, hashTable[i]->page);
			if(hashTable[i]->next){
				data* temp = hashTable[i]->next;
				while(temp){
					printf(" ->%s page: %d", temp->book, temp->page);
				}
			}
			printf("\n");
		}
		else{
			printf("%d. Empty\n");
		}
	}
}

int main(){
	
	char title[200];
	char name[200];
	int menu;
	data* move;
	while(1){
		printf("Bluejack Library\n");
		printf("================\n");
		printf("1. View Book\n");
		printf("2. Insert Book\n");
		printf("3. Remove Book\n");
		printf("4. Exit\n");
		printf(">>");
		scanf("%d", &menu); getchar();
		switch(menu){
			case 1:
			if(!move){
				printf("There is no book(s) !\n\n");
				printf("Press Enter to continue ...\n");
			}	
			case 2: 
			printf("Input book title [5-50][unique]: ");
			scanf("%[^\n]", title);
			printf("Input author name [3-25][Mr. |Mrs. ]: ");
			scanf("%[^\n]", name);
			
			if(strlen(title) >50 || strlen(title) <5){
				printf();
			}
//			case 3:
//				printf("Input book id to delete: ");
//				scanf("%[^\n]", name);
//				move = popData(name);
//				if(!move){
//					printf("Book not found !\n");
//				}
			case 4:
				return 0;
			default:
			printf("Try Again\n");
			break;	
				
		}
	}
	return 0;
}
