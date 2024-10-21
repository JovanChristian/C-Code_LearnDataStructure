#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
	int key;
	node *left;
	node *right;
}*root;

node *newnode(int key){
	node *temp = (node*) malloc(sizeof(node));
	temp->key;
	temp->left=NULL;
	temp->right=NULL;
	return temp;
}

void Insert(node *newnode){
	
	if(!root){
		root = newnode;
	}
}

int main(){
	
	return 0;
}
