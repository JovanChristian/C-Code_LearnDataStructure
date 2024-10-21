#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define size 1007

struct book{
	char bookTitle[200];
	char bookAuthor[200];
	char bookISBN[200];
	char bookID[200];
	int pageNumber;
	book* next;
}*hashTable[size];

char globalTitle[200];
char globalAuthor[200];
char globalISBN[200];
char globalID[200];
int globalPage;
int count =0;
int Exist= 0;

void clear(){
	for(int i=0; i<30; i++){
		puts("");
	}
}

int generateID(){
	count++;
	if(globalTitle[0] >= 'a' && globalTitle[0] <='z'){
		globalTitle[0] -= ('a' - 'A');
	}
	sprintf(globalID, "B%05d-%s-%c%c", count, globalISBN, globalAuthor[0], globalTitle[0]);
} 

book *newBook(char *bookTitle, char *bookAuthor, char *bookISBN, int pageNumber){
	count++;
	book* temp = (book*) malloc(sizeof(book));
	strcpy(temp->bookTitle, bookTitle);
	strcpy(temp->bookAuthor, bookAuthor);
	strcpy(temp->bookISBN, bookISBN);
	temp->pageNumber = pageNumber;
	generateID();
	strcpy(temp->bookID, globalID);
	temp->next = NULL;
	return temp;
} 

int hashing(char *bookID){
	int key =0;
	int len = strlen(bookID);
	for(int i=0; i<len; i++){
		key += bookID[i];
	} 
	return key%size;
} 

book *InsertRec(book *curr, book *newBook){
	if(!curr){
		return newBook;
		curr->next = InsertRec(curr->next, newBook);		
	}
} 

void Insert(book *newBook){
	int key = hashing(newBook->bookID);
	hashTable[key] = InsertRec(hashTable[key], newBook);
}

book *SearchRec(book *curr, char *bookID){
	if(!curr){
		return NULL;
	}
	else if(strcmp(curr->bookID, bookID)==0){
		return curr;
	}
	return SearchRec(curr->next, bookID);
}

void Search(char *bookID){
	int key = hashing(bookID);
	book *SearchRecs = SearchRec(hashTable[key], bookID);
	if(!SearchRecs){
		printf("Book not found\n");
	}
}

book *delRec(book *curr, char *bookID){
	if(!curr){
		return NULL;
	}
	else if(strcmp(curr->bookID, bookID)==0){
		book* temp = curr->next;
		free(curr);
		return temp;
	}
	curr->next = delRec(curr->next, bookID);
}

int del(char *bookID){
	int key = hashing(bookID);
	if(SearchRec(hashTable[key], bookID)==0){
		return 0;
	}
	hashTable[key] = delRec(hashTable[key], bookID);
}

void print(){
	if(!Exist){
		printf("Haven't Insert yet\n'");
	}
	puts("-------------------------------------------------------------------------------------------------------------------------------------------");
	puts("| Book ID                 | Book Title                                         | Book Author               | ISBN           | Page Number |");
	puts("-------------------------------------------------------------------------------------------------------------------------------------------");
	for(int i=0; i<size; i++){
		book *curr= hashTable[i];
		while(curr){
			printf("|%-24s| %-51s| %-26s| %-15s| %-12d|\n", curr->bookID, curr->bookTitle, curr->bookAuthor, curr->bookISBN, curr->pageNumber);	
			puts("-------------------------------------------------------------------------------------------------------------------------------------------");
		curr= curr->next;
		}
	}
}

int main(){
	int choice;
	while(choice !=4){
		clear();
		puts("Bluejack Library");
		puts("================");
		puts("1. View");
		puts("2. Insert");
		puts("3. Remove");
		puts("4. Exit");
		printf(">>");
		scanf("%d", &choice); getchar();
		switch(choice){
			case 1:{
				clear();
				print();
				puts("");
				puts("Press Enter to continue . . .");
				getchar();
				clear();
				break;
			}
		}
	}
	return 0;
}















































