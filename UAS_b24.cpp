#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Dictionary {
	char lang[255], word[255];
	Dictionary *left, *right;
	int height;
} *root;

Dictionary *addDictionary(char *lang, char *word) {
	Dictionary *newDictionary = (Dictionary*)malloc(sizeof(Dictionary));
	
	strcpy(newDictionary->lang, lang);
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
		if(strcmp(curr->lang, newDictionary->lang) > 0) {
			curr->left = add(curr->left, newDictionary);
		} else if(strcmp(curr->lang, newDictionary->lang) < 0) {
			curr->right = add(curr->right, newDictionary);
		} else {
			if(strcmp(curr->word, newDictionary->word) > 0) {
				curr->left = add(curr->left, newDictionary);
			} else if(strcmp(curr->word, newDictionary->word) < 0) {
				curr->right = add(curr->right, newDictionary);
			}
		}
		
		return rebalance(curr);
	}
}

int countWord(Dictionary *curr, char *lang) {
	if(!curr) {
		return 0;
	} else {
		if(!strcmp(curr->lang, lang)) {
			return (countWord(curr->left, lang) + countWord(curr->right, lang) + 1);
		} else {
			return (countWord(curr->left, lang) + countWord(curr->right, lang));
		}
	}
}

Dictionary *searchLang(Dictionary *curr, char *lang) {
	if(!curr || !strcmp(curr->lang, lang)) {
		return curr;
	} else if(strcmp(curr->lang, lang) > 0) {
		return searchLang(curr->left, lang);
	} else {
		return searchLang(curr->right, lang);
	}
}

Dictionary *searchWord(Dictionary *curr, char *word) {
	if(!curr || !strcmp(curr->word, word)) {
		return curr;
	} else if(strcmp(curr->word, word) > 0) {
		return searchWord(curr->left, word);
	} else {
		return searchWord(curr->right, word);
	}
}

void showLang(Dictionary *curr, char *lang) {
	if(!curr) {
		return;
	} else {
		showLang(curr->left, lang);
		if(!strcmp(curr->lang, lang)) {
			printf("- %s\n", curr->word);
		}
		showLang(curr->right, lang);
	}
}

char currLang[255];
void showAll(Dictionary *curr) {
	if(!curr) {
		return;
	} else {
		showAll(curr->left);
		if(strcmp(curr->lang, currLang)) {
			printf("%s (%d):\n", curr->lang, countWord(root, curr->lang));
			showLang(root, curr->lang);
			strcpy(currLang, curr->lang);
		}
		showAll(curr->right);
	}
}

Dictionary *delWord(Dictionary *curr, char *lang, char *word) {
	if(strcmp(curr->lang, lang) > 0) {
		curr->left = delWord(curr->left, lang, word);
	} else if(strcmp(curr->lang, lang) < 0) {
		curr->right = delWord(curr->right, lang, word);
	} else {
		if(strcmp(curr->word, word) > 0) {
			curr->left = delWord(curr->left, lang, word);
		} else if(strcmp(curr->word, word) < 0) {
			curr->right = delWord(curr->right, lang, word);
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
				// Predecessor: most right child of left child
				Dictionary *temp = curr->left;
				
				while(temp->right) {
					temp = temp->right;
				}
				
				strcpy(curr->lang, temp->lang);
				strcpy(curr->word, temp->word);
				
				curr->left = delWord(curr->left, temp->lang, temp->word);
			}
		}
	}
	
	if(!curr) {
		return curr;
	} else {
		return rebalance(curr);
	}
}

void *delLang(char *lang) {
	Dictionary *findLang = searchLang(root, lang);
	
	while(findLang) {
		root = delWord(root, findLang->lang, findLang->word);
		findLang = searchLang(root, lang);
	}
}

int main() {
	int t;
	
	scanf("%d", &t);
	getchar();
	
	for(int i = 1; i <= t; i++) {	
		char operation[255], language[255], word[255];
		
		scanf("%s", operation);
		
		if(strcmp(operation, "ADD") == 0) {
			scanf("%s %s", language, word);
			getchar();
			
			root = add(root, addDictionary(language, word));
			
			printf("Case %d:\n", i);
			puts("Successfully Added");
		} else if(strcmp(operation, "SHOW-ALL") == 0) {
			printf("Case %d:\n", i);
			showAll(root);
		} else if(strcmp(operation, "SHOW-LANG") == 0) {
			scanf("%s", language);
			getchar();
			
			Dictionary *findLang = searchLang(root, language);
			
			printf("Case %d:\n", i);
			if(findLang) {
				printf("%s (%d):\n", language, countWord(root, language));
				
				showLang(root, language);
			} else {
				printf("%s language not found\n", language);
			}
		} else if(strcmp(operation, "DEL-LANG") == 0) {
			scanf("%s", language);
			getchar();
			
			Dictionary *findLang = searchLang(root, language);
			
			printf("Case %d:\n", i);
			if(findLang) {
				delLang(language);
				
				puts("Successfully Deleted");
			} else {
				printf("%s language not found\n", language);
			}
		} else if(strcmp(operation, "DEL-WORD") == 0) {
			scanf("%s %s", language, word);
			getchar();
			
			Dictionary *findLang = searchLang(root, language);
			
			printf("Case %d:\n", i);
			if(findLang) {
				Dictionary *findWord = searchWord(root, word);
				
				if(findWord) {
					root = delWord(root, language, word);
					
					puts("Successfully Deleted");
				} else {
					printf("Word (%s) not found\n", word);
				}
			} else {
				printf("%s language not found\n", language);
			}
		}
	}
	
	return 0;
}
