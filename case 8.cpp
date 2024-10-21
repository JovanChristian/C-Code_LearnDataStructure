#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct game{
	char name[100];
	char genre[100];
	char id[100];
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
		if(balance(curr->left) <= 0){
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
	return rebalance(curr);
}

void Preorder(game *curr){
	if(!curr){
		return; 
	}
	else{
		printf("| %-10s | %-25s | %-12s | %-10d |\n", curr->id, curr->name, curr->genre, curr->stock);
		Preorder(curr->left);
		Preorder(curr->right);
	}
}

void Inorder(game *curr){
	if(!curr){
		return; 
	}
	else{
		Inorder(curr->left);
		printf("| %-10s | %-25s | %-12s | %-10d |\n", curr->id, curr->name, curr->genre, curr->stock);
		Inorder(curr->right);
	}
}

void Postorder(game *curr){
	if(!curr){
		return; 
	}
	else{
		Postorder(curr->left);
		Postorder(curr->right);
		printf("| %-10s | %-25s | %-12s | %-10d |\n", curr->id, curr->name, curr->genre, curr->stock);
	}
}

game *search(game *curr, char *key){
	
	if(!curr || (!strcmp(curr->id, key))){
		return curr;
	}
	else if(strcmp(curr->id, key) > 0){
		return search(curr->left, key);
	}
	else if(strcmp(curr->id, key) <0){
		return search(curr->right, key);
	}
}

game *del(game *curr, char *key){
	
	if(strcmp(curr->id, key) > 0){
		curr->left = del(curr->left, key);
	}
	else if(strcmp(curr->id, key) < 0){
		curr->right = del(curr->right, key);
	}
	else{
		if(!curr->left || !curr->right){
			game *temp;
			
			if(curr->left){
				temp = curr->left;
			}
			else{
				temp = curr->right;
			}
			
			if(!temp){
				temp = curr;
				curr = NULL;
			}
			else{
				*curr = *temp;
			}
			free(temp);
		}
		else{ //predecessor
			game *temp = curr->left;
			
			while(temp->right){
				temp = temp->right;
			}
			
			strcpy(curr->id, temp->id);
			strcpy(curr->name, temp->name);
			strcpy(curr->genre, temp->genre);
			curr->stock = temp->stock;
			
			curr->left = del(curr->left, temp->id);
		}
		if(!curr){
			return curr;
		}
		else{
			rebalance(curr);
		}
	}
}

game *update(game *root, char *findname, char *key, int stock){
	if(strcmp(findname, root->id)==0 && strcmp(key, "add")==0){
		root->stock += stock;
		printf("Data Update Succesfully!\n");
		
		return root;
	}
	else if(strcmp(findname, root->id)==0 && strcmp(key, "remove")==0){
		root->stock -= stock;
		if(root->stock ==0){
		root = del(root, findname);
		printf("Data Update Succesfully!\n");
		printf("%s is removed from the warehouse\n", findname);	
		}
		else{
			printf("Data Update Succesfully!\n");
		}
	return root;
	}
	else if(strcmp(findname, root->id) > 0){
		root->left = update(root->left, findname, key, stock);
	}
	else if(strcmp(findname, root->id) < 0){
		root->right = update(root->right, findname, key, stock);
	}
	else if(!root){
		return NULL;
	}
}

int main(){
	srand(time(NULL));
	int choose;
	
	while(choose != 4){
		puts("Bluejack GShop");
		puts("==============");
		puts("1. Insert Game");
		puts("2. View Game");
		puts("3. Update Game");
		puts("4. Exit");
		printf(">>");
		scanf("%d", &choose); getchar();
		
		switch(choose){
			case 1:{
				
				char id[6];
				sprintf(id, "GM%d%d%d", rand()%10, rand()%10, rand()%10);
				
				char Game[100];
				char Genre[100];
				int stock;
				
				while(1){
					printf("Input game title[5-25][unique]: ");
					scanf("%[^\n]", Game); getchar();
					
					if(strlen(Game) > 4 && strlen(Game) < 20){
						break;
					}
				}
				
				while(1){
					printf("Input game type [Action|RPG|Adventure|Card Game]:");
					scanf("%[^\n]", Genre); getchar();
					
					if(strcmp(Genre, "Action")==0 || strcmp(Genre, "RPG")==0 || strcmp(Genre, "Adventure")==0 || strcmp(Genre, "Card Game")==0){
						break;
					}
					else{
						continue;
					}
				} 
				
				while(1){
					printf("Input game stock [>=1]: ");
					scanf("%d",&stock); getchar();
					
					if(stock > 0){
						break;
					}
				}
				
				root = Insert(root, newGame(id, Game, Genre, stock));
				printf("Insert Success!\n");
				getchar();
				
				break;
			}
			
			case 2: {
				if(!root) {
					puts("Warehouse is empty !\n");
				} else {
					puts("---------------------------------------------------------\n| ID		| Game Title                | Game Genre   | Game Stock |\n---------------------------------------------------------");
					Inorder(root);
					puts("---------------------------------------------------------\n");
				}
				
				puts("Press enter to continue...");
				getchar();
				
				break;
			}
			
			case 3:{
				
				int stock;
				char title[100];
				char key[100];
				
				printf("Input game title: ");
				scanf("%[^\n]",title); getchar(); 
				
				game *searchItem = search(root, title);
				
				if(searchItem){
					printf("Game stock = %d\n",searchItem->stock);
					
					while(1){
						printf("Input update type [add|remove][case insentive]: ");
						scanf("%s",key); getchar();
						
						if(strcmpi(key, "add")==0 || strcmpi(key, "remove")==0){
							break;
						}
					}
					
					if(strcmpi(key, "add")==0){
						while(1){
							printf("Input stock to add[>=1]: ");
							scanf("%d",&stock); getchar();
							
							if(stock > 0){
								break;
							}
						}
						root = update(searchItem, title, key, stock);
					}
					
					else if(strcmpi(key, "remove")==0){
					while(1){
						printf("Input stock to remove[1-%d]: ",searchItem->stock);
							scanf("%d",&stock); getchar();
							
							if(stock > 0 && stock <= searchItem->stock){
								break;
							}
					}
					root = update(searchItem, title, key, stock);
				}						
				getchar();

				}
				
				else if(!searchItem){
					printf("Data not found!\n");
					getchar();
					
				}

				break;
			}
		}
	}
	
	return 0;
}
