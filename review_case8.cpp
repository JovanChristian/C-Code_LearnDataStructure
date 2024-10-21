#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct game{
	char id[100];
	char name[100];
	char genre[100];
	int stock;
	int height;
	game *left;
	game *right;
}*root;

game *newGame(char* id, char* name, char* genre, int stock){
	game *temp = (game*) malloc(sizeof(game));
	strcpy(temp->id, id);
	strcpy(temp->name, name);
	strcpy(temp->genre, genre);
	temp->stock = stock;
	temp->height = 1;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

int max(int a, int b){
	return (a > b)? a : b;
} 

int height(game *curr){
	if(!curr){
		return 0;
	}
	return 1 + max(height(curr->left), height(curr->right));
}

int balance(game *curr){
	if(!curr){
		return 0;
	}
	return (height(curr->left) - height(curr->right));
}

game *leftRotate(game *curr){
	game *rightChild = curr->right;
	game *rightChildLeft = rightChild->left;
	
	rightChild->left = curr;
	curr->right = rightChildLeft;
	
	rightChild->height = height(rightChild);
	curr->height = height(curr);
	
	return rightChild;
} 

game *rightRotate(game *curr){
	game *leftChild = curr->left;
	game *leftChildRight = leftChild->right;
	
	leftChild->right = curr;
	curr->left = leftChildRight;
	
	leftChild->height = height(leftChild);
	curr->height = height(curr);
	
	return leftChild;
}

game *rebalance(game *curr){
	curr->height = height(curr);
	int balanceValue = balance(curr);
	
	if(balanceValue > 1){
		if(balance(curr->left) <=0){
			return rightRotate(curr);
		}
		else{
			curr->left = leftRotate(curr);
			return rightRotate(curr);
		}
	}
	else if(balanceValue < -1){
		if(balance(curr->right) >=0){
			return leftRotate(curr);
		}
		else{
			curr->right = rightRotate(curr);
			return leftRotate(curr);
		}
	}
	else{
		return curr;
	}
}

game *Insert(game *curr, game *newGame){
	if(!curr){
		return newGame;
	}
	else{
		if(strcmp(curr->id, newGame->id) > 0){
		curr->left = Insert(curr->left, newGame);
	}
		else if(strcmp(curr->id, newGame->id) < 0){
		curr->right = Insert(curr->right, newGame);
		}	
	}
	rebalance(curr);
}

game *Inorder(game *curr){
	if(!curr){
		return NULL;
	}
	else{
		Inorder(curr->left);
		printf("| %-10s | %-25s| %-12s | %-8d|\n", curr->id, curr->name, curr->genre, curr->stock);
		Inorder(curr->right);
	}
}

game *search(game *curr, char* key){
	if(!curr || !strcmp(curr->id, key)){
		return curr;
	}	
	else if(strcmp(curr->id, key) > 0){
		return curr->left = search(curr->left, key);
	}
	else if(strcmp(curr->id, key) < 0){
		return curr->right = search(curr->right, key);
	}
}

int main(){
	
	return 0;
}


