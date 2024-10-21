#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Dictionary {
	char language[31], word[51];
	int height;
	Dictionary *left, *right;
} *root;

Dictionary *createDictionary(char *language, char *word) {
	Dictionary *newDictionary = (Dictionary*)malloc(sizeof(Dictionary));
	
	strcpy(newDictionary->language, language);
	strcpy(newDictionary->word, word);
	newDictionary->left = newDictionary->right = NULL;
	newDictionary->height = 1;
	
	return newDictionary;
}

int max(int left, int right) {
	if(left >= right) {
		return left;
	} else {
		return right;
	}
}

int height(Dictionary *curr) {
	if(!curr) {
		return 0;
	} else {
		return (max(height(curr->left), height(curr->right)) + 1);
	}
}

int balance(Dictionary *curr) {
	if(!curr) {
		return 0;
	} else {
		return (height(curr->left) - height(curr->right));
	}
}

Dictionary *rightRotate(Dictionary *curr) {
	Dictionary *leftChild = curr->left;
	Dictionary *leftChildRight = leftChild->right;
	
	leftChild->right = curr;
	curr->left = leftChildRight;
	
	leftChild->height = height(leftChild);
	curr->height = height(curr);
	
	return leftChild;
}

Dictionary *leftRotate(Dictionary *curr) {
	Dictionary *rightChild = curr->right;
	Dictionary *rightChildLeft = rightChild->left;
	
	rightChild->left = curr;
	curr->right = rightChildLeft;
	
	rightChild->height = height(rightChild);
	curr->height = height(curr);
	
	return rightChild;
}

Dictionary *rebalance(Dictionary *curr) {
	curr->height = height(curr);
	int balanceValue = balance(curr);
	
	if(balanceValue > 1) {
		if(balance(curr->left) >= 0) {
			return rightRotate(curr);
		} else {
			curr->left = leftRotate(curr->left);
			return rightRotate(curr);
		}
	} else if(balanceValue < -1) {
		if(balance(curr->right) <= 0) {
			return leftRotate(curr);
		} else {
			curr->right = rightRotate(curr->right);
			return leftRotate(curr);
		}
	} else {
		return curr;
	}
}

Dictionary *add(Dictionary *curr, Dictionary *newDictionary) {
	if(!curr) {
		return newDictionary;
	} else {
		if(!strcmp(curr->language, newDictionary->language)) {
			if(strcmp(curr->word, newDictionary->word) > 0) {
				curr->left = add(curr->left, newDictionary);
			} else if(strcmp(curr->word, newDictionary->word) < 0) {
				curr->right = add(curr->right, newDictionary);
			}
		} else if(strcmp(curr->language, newDictionary->language) > 0) {
			curr->left = add(curr->left, newDictionary);
		} else {
			curr->right = add(curr->right, newDictionary);
		}
		
		return rebalance(curr);
	}
}

int countWords(Dictionary *curr, char *language) {
	if(!curr) {
		return 0;
	} else {
		int countWordsLeft = countWords(curr->left, language);
		int countWordsRight = countWords(curr->right, language);
		
		int words = countWordsLeft + countWordsRight;
		
		if(!strcmp(curr->language, language)) {
			return (words + 1);
		} else {
			return words;
		}
	}
}

char currLanguage[31];

void showAll(Dictionary *curr) {
	if(!curr) {
		return;
	} else {
		showAll(curr->left);
		if(!currLanguage || strcmp(currLanguage, curr->language)) {
			strcpy(currLanguage, curr->language);
			
			printf("%s (%d):\n", currLanguage, countWords(root, currLanguage));
		}
		printf("- %s\n", curr->word);
		showAll(curr->right);
	}
}

void showLang(Dictionary *curr, char *language) {
	if(!curr) {
		return;
	} else {
		showLang(curr->left, language);
		if(!strcmp(curr->language, language)) {
			printf("- %s\n", curr->word);
		}
		showLang(curr->right, language);
	}
}

Dictionary *searchLang(Dictionary *curr, char *language) {
	if(!curr || !strcmp(curr->language, language)) {
		return curr;
	} else if(strcmp(curr->language, language) > 0) {
		return searchLang(curr->left, language);
	} else {
		return searchLang(curr->right, language);
	}
}

Dictionary *searchWord(Dictionary *curr, char *word) {
	if(!curr || !strcmp(curr->word, word)) {
		return curr;
	} else {
		Dictionary *searchWordLeft = searchWord(curr->left, word);
		Dictionary *searchWordRight = searchWord(curr->right, word);
		
		if(searchWordRight) {
			return searchWordRight;
		} else {
			return searchWordLeft;
		}
	}
}

Dictionary *Delete(Dictionary *curr, char *language, char *word) {
	if(strcmp(curr->language, language) > 0) {
		curr->left = Delete(curr->left, language, word);
	} else if(strcmp(curr->language, language) < 0) {
		curr->right = Delete(curr->right, language, word);
	} else {
		if(strcmp(curr->word, word) > 0) {
			curr->left = Delete(curr->left, language, word);
		} else if(strcmp(curr->word, word) < 0) {
			curr->right = Delete(curr->right, language, word);
		} else {
			if(!curr->left || !curr->right) {
				Dictionary *temp;
				
				if(curr->right) {
					temp = curr->right;
				} else {
					temp = curr->left;
				}
				
				if(!temp) {
					temp = curr;
					curr = NULL;
				} else {
					*curr = *temp;
				}
				
				free(temp);
			} else {
				Dictionary *temp = curr->left;
				
				while(temp->right) {
					temp = temp->right;
				}
				
				strcpy(curr->language, temp->language);
				strcpy(curr->word, temp->word);
				
				curr->left = Delete(curr->left, temp->language, temp->word);
			}
			
			if(!curr) {
				return curr;
			} else {
				return rebalance(curr);
			}
		}
	}
}

int main() {
	root = add(root, createDictionary("English", "Park"));
	root = add(root, createDictionary("English", "Choose"));
	root = add(root, createDictionary("Indonesia", "Duduk"));
	root = add(root, createDictionary("Indonesia", "Makan"));
	root = add(root, createDictionary("Spanish", "Medico"));
	root = add(root, createDictionary("English", "Chalk"));
	root = add(root, createDictionary("Indonesia", "Minum"));
	root = add(root, createDictionary("French", "Cuisinier"));
	
//	showAll(root);
	
//	showLang(root, "Indonesia");
	
//	root = delLang(root, "English");
	
//	root = delWord(root, "Minum");

//	Dictionary *findWord = searchWord(root, "Park");
//	if(findWord) {
//		puts("ada");
//	}
//	
//	root = Delete(root, findWord->language, "Park");
	
//	Dictionary *findLang = searchLang(root, "Japanese");
//	while(findLang) {
//		root = Delete(root, "Japanese", findLang->word);
//		
//		findLang = searchLang(root, "Japanese");
//	}
//	
//	showAll(root);
	
//	printf("%d\n", countWords(root, "French"));
	
	int T;
	
	scanf("%d", &T);
	getchar();
	
	for(int i = 0; i < T; i++) {
		char operation[96];
		
		scanf("%[^\n]", operation);
		getchar();
		
		int operationLen = strlen(operation);
		
		printf("Case %d:\n", (i + 1));
		
		if(!strcmp(operation, "SHOW-ALL")) {
			showAll(root);
			
			int currLanguageLen = strlen(currLanguage);
			
			for(int j = 0; j < currLanguageLen; j++) {
				currLanguage[j] = '\0';
			}
		} else {
			if(!strncmp(operation, "SHOW-LANG ", 10)) {
				char language[31] = {'\0'};
				
				for(int j = 10; j < operationLen; j++) {
					language[j - 10] = operation[j];
				}
				
				Dictionary *findLang = searchLang(root, language);
				if(!findLang) {
					printf("%s language not found\n", language);
				} else {
					printf("%s (%d):\n", language, countWords(root, language));
					
					showLang(root, language);
				}
			} else if(!strncmp(operation, "DEL-LANG ", 9)) {
				char language[31] = {'\0'};
				
				for(int j = 9; j < operationLen; j++) {
					language[j - 9] = operation[j];
				}
				
				Dictionary *findLang = searchLang(root, language);
				if(!findLang) {
					printf("%s language not found\n", language);
				} else {
					while(findLang) {
						root = Delete(root, language, findLang->word);
						
						findLang = searchLang(root, language);
					}
					
					puts("Successfully Deleted");
				}
			} else if(!strncmp(operation, "ADD ", 4)) {
				char language[31] = {'\0'}, word[51] = {'\0'};
				
				int j = 4;
				while(operation[j] != ' ') {
					language[j - 4] = operation[j];
					
					j++;
				}
				j++;
				
				int k = j;
				for(j; j < operationLen; j++) {
					word[j - k] = operation[j];
				}
				
				root = add(root, createDictionary(language, word));
				
				puts("Successfully Added");
			} else if(!strncmp(operation, "DEL-WORD ", 9)) {
				char language[31] = {'\0'}, word[51] = {'\0'};
				
				int j = 9;
				while(operation[j] != ' ') {
					language[j - 9] = operation[j];
					
					j++;
				}
				j++;
				
				int k = j;
				for(j; j < operationLen; j++) {
					word[j - k] = operation[j];
				}
				
				Dictionary *findWord = searchWord(root, word);
				if(!findWord) {
					printf("Word (%s) not found\n", word);
				} else {
					root = Delete(root, findWord->language, word);
						
					puts("Successfully Deleted");
				}
			}
		}
	}
	
	return 0;
}
