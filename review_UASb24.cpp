#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct dict{
	char lang[255];
	char word[255];
	int height;
	dict* left;
	dict* right;
}*root;

dict *newDict(char* lang, char* word){
	dict *temp = (dict*) malloc(sizeof(dict));
	strcpy(temp->lang, lang);
	strcpy(temp->word, word);
	temp->height = 1;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

int max(int a, int b){
	return (a > b)? a:b;
}

int height(dict *curr){
	if(!curr){
		return 0;
	}
	return 1 + max(height(curr->left), height(curr->right));
}

int balance(dict *curr){
	if(!curr){
		return 0;
	}
	return (height(curr->left) - height(curr->right));
}

dict *leftRotate(dict *curr){
	dict *rightChild = curr->right;
	dict *rightChildLeft = rightChild->left;
	
	rightChild->left = curr;
	curr->right = rightChildLeft;
	
	rightChild->height = height(rightChild);
	curr->height = height(curr);
	
	return rightChild;
}

dict *rightRotate(dict *curr){
	dict *leftChild = curr->left;
	dict *leftChildRight = leftChild->right;
	
	leftChild->right = curr;
	curr->left = leftChildRight;
	
	leftChild->height = height(leftChild);
	curr->height = height(curr);
	
	return leftChild;
}

dict *rebalance(dict *curr){
	curr->height = height(curr);
	int balanceValue = balance(curr);
	
	if(balanceValue > 1){
		if(balance(curr->left) >= 0){
			return rightRotate(curr);
		}
		else{
			curr->left = leftRotate(curr->left);
			return rightRotate(curr);
		}
	}
	else if(balanceValue < -1){
		if(balance(curr->right) <=0){
			return leftRotate(curr);
		}
		else{
			curr->right = rightRotate(curr->right);
			return leftRotate(curr);
		}
	}
	else{
		return curr;
	}
}

dict *Insert(dict *curr, dict *newDict){
	if(!curr){
		return newDict;
	}
	else{
		if(strcmp(curr->lang, newDict->lang) > 0){
			curr->left = Insert(curr->left, newDict);
		}
		else if(strcmp(curr->lang, newDict->lang) <0){
			curr->right = Insert(curr->right, newDict);
		}
		else{
			if(strcmp(curr->word, newDict->word) > 0){
				curr->left = Insert(curr->left, newDict);
			}
			else if(strcmp(curr->word, newDict->word) < 0){
				curr->right = Insert(curr->right, newDict);
			}
		}
		return rebalance(curr);
	}
}



int main(){
	
	return 0;
}
