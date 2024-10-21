#include<stdio.h>
#include<stdlib.h>

struct node{
	int value;
	node* left;
	node* right;
	int totalChild;
}*root = NULL; 

struct node* init(int value){
	struct node* top = (struct node*) malloc(sizeof(node));
	top->value = value;
	top->left= NULL;
	top->right = NULL; 
	return top;
} 

node* insert(int value, node* curr){
	if(!root){
		return root;
	}else{
		if(value < curr->value){
			if(!curr->left){
			curr->left = init(value);
			}else{
			insert(value, curr->left);	
			}
		}else if(value > curr->value){
			if(!curr->right){
				curr->right = init(value);
			}else{
				insert(value, curr->right);
			}
		}
	}
} 

node* InOrder(int level, node* curr){
	if(curr != NULL){
		InOrder(level+1, curr->left);
		printf("level : %d - data %d - total child: %d\n", level, curr->value, curr->totalChild); 
		InOrder(level+1, curr->right);
	}
} 

int UpdateTotalChild(node* curr){
	if(!curr){
		return 0;
	} else{
		curr->totalChild = UpdateTotalChild(curr->left) + UpdateTotalChild(curr->right);
		return curr->value + curr->totalChild;
	}
}
int main(){
	
	insert(10, root); 
	UpdateTotalChild(root);
	insert(20, root);
	UpdateTotalChild(root);
	insert(30, root);
	UpdateTotalChild(root);
	InOrder(0, root);
	UpdateTotalChild(root); 
	
	return 0;
}
