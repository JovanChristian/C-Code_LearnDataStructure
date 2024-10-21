#include<stdio.h>
#include<stdlib.h>

struct tree{
	int value;
	tree *left;
	tree *right;
	int height;
};

tree* Newtree(int value){
	tree* temp = (tree*) malloc(sizeof(tree));
	temp->value = value;
	temp->left = NULL;
	temp->right = NULL;
	temp->height = 1;
	return temp;
}

int max(int a, int b){
	return a>b? a : b;
} 

int getHeight(tree* curr){
	
	if(!curr){
		return 0;
	}
	return curr->height;
}

int main(){
	
	return 0;
}
