#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define size 1007

struct book{
	char Title[200];
	char Author[200];
	char ISBN[200];
	char ID[200];
	int page;
	book* next;
}*hashTable[size];

//rand() %100 + '0'
//rand() %100 + 'A'

void clear(){
	for(int i=0; i<30; i++){
		puts("");
	}
}

char global_ID[200];
char global_Title[200]; 
char global_Author[200];
char global_ISBN[200];
int global_page;
int count;
int Exist = 0;

void generateID(){
	//mengubah huruf kapital
	if(global_Title[0] >= 'a' && global_Title[0] <='z'){
		global_Title[0] -=('a' - 'A');
	}
	//membuat ID
	sprintf(global_ID, "B%05d-%s-%c%c", count, global_ISBN, global_Title[0], global_Author[0]);
}

book* newbook(char Title[], char Author[], char ISBN[], int page){
	count++;
	Exist++;
	book* temp = (book*) malloc(sizeof(book));
	strcpy(temp->Title, Title);
	strcpy(temp->Author, Author);
	strcpy(temp->ISBN, ISBN);
	temp->page = page;
	generateID();
	strcpy(temp->ID, global_ID);
	temp->next=NULL;
	return temp;
}

int hashing(char ID[]){
	int key=0;
	int len = strlen(ID);
	for(int i=0; i<len; i++){
		key += ID[i];
	}
	return key%size;
}

book *InsertRec(book *curr, book *newbook){	
	if(!curr){
		return newbook;
		curr->next = InsertRec(curr->next, newbook);
	}
} 

void Insert(book *newbook){
	int key = hashing(newbook->ID); //index
	hashTable[key] = InsertRec(hashTable[key], newbook);
}

book *SearchRec(book *curr, char ID[]){
	if(!curr){ //ga ketemu
		return NULL;
	}
	else if(strcmp(curr->ID, ID)==0){ //ketemu, kita return punya si curr
		return curr;
	}
	return SearchRec(curr->next, ID); //kalo misalnya ga ketemu, kita cari ke curr berikutnya
}

void Search(char ID[]){
	int key = hashing(ID);
	book *SearchRecs = SearchRec(hashTable[key], ID);
	if(!SearchRecs){
		printf("Book not found\n");
	}
}

book *delRec(book *curr, char ID[]){
	if(!curr){
		return NULL;
	}
	else if(strcmp(curr->ID, ID)==0){
		book *temp = curr->next;
		free(curr);
		return temp;
	}
	curr->next = delRec(curr->next, ID);
} 

int del(char ID[]){
	int key = hashing(ID);
	if(SearchRec(hashTable[key], ID)==NULL){ // ga ketemu
		return 0;
	}
	hashTable[key] = delRec(hashTable[key], ID); // kalo ketemu
}

void print(){
	if(!Exist){
		printf("Haven't data Insert yet\n");
		return;
	}
	puts("-------------------------------------------------------------------------------------------------------------------------------------------");
	puts("| Book ID                 | Book Title                                         | Book Author               | ISBN           | Page Number |");
	puts("-------------------------------------------------------------------------------------------------------------------------------------------");
	
	for(int i=0; i<size; i++){
		book *curr = hashTable[i];
		while(curr){
		printf("|%-24s| %-51s| %-26s| %-15s| %-12d|\n", curr->ID, curr->Title, curr->Author, curr->ISBN, curr->page);	
		puts("-------------------------------------------------------------------------------------------------------------------------------------------");
		curr= curr->next;
		}
	}
}

int main(){
	srand(time(NULL));
	int choose;
	while(choose !=4){
		clear();
		puts("Bluejack Library");
		puts("================");
		puts("1. View");
		puts("2. Insert");
		puts("3. Remove");
		puts("4. Exit");
		printf(">>");
		scanf("%d", &choose); getchar();
		switch(choose){
			case 1: {
				clear();
				print();
				puts("");
				puts("Press Enter to continue . . .");
				getchar();
				clear();
				break;
			}
			
			case 2:{
				int len_Title;
				int validate_Title=1;
				clear();
				do{ 
				//bagian book title				
					printf("Input book title[5-50][unique]: ");
					scanf("%[^\n]", global_Title); getchar();
					for(int i=0; i<size; i++){
						book *curr = hashTable[i];
						while(curr){
							if(strcmp(global_ID, curr->Title)==0){
								printf("Book Already Exist\n");
								validate_Title =0;
							}
							curr = curr->next;
						}
					}
					len_Title = strlen(global_Title);
				}while(len_Title < 5 || len_Title > 50 || validate_Title == 0);
				
				//bagian book author
				int validateMr = 0;
				int len_Author = 0;
				while(true){
					printf("Input author name[3-25][Mr. |Mrs. ]: ");
					scanf("%[^\n]",global_Author); getchar();
					len_Author = strlen(global_Author);
					if(strncmp(global_Author, "Mr. ",4)==0){
						validateMr = 1;
					} 
					else if(strncmp(global_Author, "Mrs. ", 5)==0){
						validateMr = 2;
					}
					if(validateMr == 1){
						len_Author -= 4;
					} 
					else if(validateMr == 2){
						len_Author -= 5;
					}
					
					if(len_Author >= 3 && len_Author <= 25 && validateMr != 0){
						break;
					}
				} 
				
				int len_ISBN = 0;
				int noAlpha =0;
				do{
					printf("Input ISBN[10-13][numeric]: ");
					scanf("%s", global_ISBN); getchar();
					len_ISBN = strlen(global_ISBN);
					int validateISBN=0; 
					
					for(int i =0; i<len_ISBN; i++){
						if(global_ISBN[i] >= '0' && global_ISBN[i] <= '9'){
							validateISBN+=1;
						}
					}
					
					if(len_ISBN == validateISBN){
						noAlpha = 1;
					}
					
				}while(len_ISBN < 10 || len_ISBN > 13 || noAlpha == 0);
			
					
				do{
					printf("Input page number[>= 16]: ");
					scanf("%d",&global_page); getchar();
				}while(global_page < 16); 
				Insert(newbook(global_Title, global_Author, global_ISBN, global_page));
				puts("");
				puts("Insert Success!");
				getchar();
				break;
			}
			
			case 3:{
				char findBook[200];
				char yesno;
				printf("Input book id to delete: ");
				scanf("%[^\n]",findBook); getchar();
				for(int i=0; i<size; i++){
					book *curr = hashTable[i];
					while(curr){
						if(strcmp(findBook, curr->ID)==0){
							printf("Book Id: %s\n",curr->ID);
							printf("Book Title: %s\n",curr->Title);
							printf("Book Author: %s\n",curr->Author);
							printf("Book ISBN: %s\n",curr->ISBN);
							printf("Page Number: %d\n",curr->page);
							while(true){
								
							printf("Are you sure [y|n]? ");
							scanf("%c",&yesno); getchar();
							if(yesno == 'y'){
								del(findBook);
								Exist -=1;
							}
							else if(yesno == 'n'){
								break;
							}
							
						}
							}
						curr = curr->next;
					}
				}
				getchar();
				clear();
				break;
			}	
		}
	}
	return 0;
}
