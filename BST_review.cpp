#include <stdio.h>
#include <stdlib.h>

struct tnode {
    int val;
    struct tnode *left;
    struct tnode *right;
}*root;

struct tnode * newnode(int val){
    struct tnode *tmp = (struct tnode *)malloc(sizeof(struct tnode));
    tmp->val = val;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

int delExist = 1;

//search
struct tnode *search(struct tnode *curr, int x){
	
	if(!curr){
		return NULL;
	}else if(x < curr->val){
		search(curr->left, x);
	}else if(x > curr->val){
		search(curr->right, x);
	}else if(x == curr->val){
		return curr;
	}
}

int heightTree(tnode *curr){ 
	
	if(!curr){
		return 0;
	}else{
		int left;
		int right;
		left = heightTree(curr->left);
		right = heightTree(curr->right);
		if(left >= right){
			return left + 1;
		}
		else{
			return right +1;
		}
	}
} 

int cCounter = 0;
void count2Child(tnode *curr) {
	
	if(!curr){
		return;
	}else{
		if(curr->left && curr->right){
			cCounter++;
		}
		count2Child(curr->left);
		count2Child(curr->right);
	}
} 

void count1Child(tnode *curr){
	if(!curr){
		return;
	}else{
		if(curr->left && !curr->right){
			cCounter++;
		}
		else if(!curr->left && curr->right){
			cCounter++;
		}
		count1Child (curr->left);
		count1Child (curr->right);
	}
}

int lCounter = 0;
void countLeaf(tnode *curr) {

	if(!curr){
		return;
	}else{
		if(!curr->left && !curr->right){
			lCounter++;
		}
		countLeaf(curr->left);
		countLeaf(curr->right);
	}
}

void insert(struct tnode *curr,int x){
	
	if(!root){
		root = newnode(x);
	}
	else if( x < curr->val && !curr->left){
		curr->left = newnode(x);
	}
	else if(x > curr->val && !curr->right){
		curr->right = newnode(x);
	}
	else if(x < curr->val){
		insert(curr->left, x);
	}
	else if(x > curr->val){
		insert(curr->right, x);
	}
}

void inorder(int lev, struct tnode *curr){
    if(curr->left != NULL) inorder(lev+1, curr->left);
    printf("level: %d - data: %d\n",lev,curr->val);
    if(curr->right !=NULL) inorder(lev+1, curr->right);
} 

struct tnode *getMaxLeft(struct tnode *curr){
	
	tnode *iter = curr->left;
	while(iter->right){
		iter = iter->right;
	}
	return iter;
} 

struct tnode *deleter(struct tnode *curr, int val){
	
	if(!root){
		return NULL;
	}
	else if(val < curr->val && !curr->left || val > curr->val && !curr->right){
		delExist= 0;
		return curr;
	}else if(val < curr->val && !curr->left){
		curr->left = deleter(curr->left, val);
	}else if(val > curr->val && !curr->right){
		curr->right = deleter(curr->right, val);
	}else{
		if(!curr->left && !curr->right){
			free(curr);
			return NULL;
		}
		else if(!curr->left){
			return curr->right;
		}else if(!curr->right){
			return curr->left;
		}else{
			tnode *temp = getMaxLeft(curr);
			curr->val = temp->val;
			curr->left = deleter(curr->left, temp->val);
		}
	}
	return curr;
}

int main(){
	 int x;
    insert(root, 5);
    insert(root, 18);
    insert(root, 3);
    insert(root, 2);
    insert(root, 4);
    inorder(0,root);
    printf("\n");
    printf("%d\n",getMaxLeft(root)->val);
    printf("input integer data to be deleted: ");
    int y;
    scanf("%d",&y);
    //delete node dengan data y
    deleter(root, y);
    inorder(0,root);
    printf("data ada? %d",delExist);
    printf("\n");
}
