#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
	char name[101];
	float rate;
	node *right;
	node *left;
} *root = NULL;

node *createNode(char name[], float rate)
{
	node *tmp = (node *) malloc(sizeof(node));
	tmp->rate = rate;
	strcpy(tmp->name, name);
	tmp->right = tmp->left = NULL;
}
void insertNode(node *curr, char name[], float rate)
{
	
	if(!root) root = createNode(name, rate);
	else
	{
		if(strcmp(name , curr->name) > 0)
		{
			if(curr->left == NULL)
			{
				curr->left = createNode(name,rate);
			}
			else
			{
				insertNode(curr->left,name,rate);
			}
		}
		else if(strcmp(name , curr->name) < 0)
		{
			if(curr->right == NULL)
			{
				curr->right = createNode(name,rate);
			}
			else
			{
				insertNode(curr->right,name,rate);
			}
		}
		else if(strcmp(name , curr->name) == 0)
		{
			curr->rate = rate;
		}
	}
}
node *search(node* curr, char name[])
{
	if(!curr) return NULL;
	else if(strcmp(curr->name, name) == 0) return curr;
	else
	{
		if(strcmp(name , curr->name) > 0)
		{
			return search(curr->left, name);
		}
		else if(strcmp(name , curr->name) < 0)
		{
			return search(curr->right, name);
		}
	}
}
void inorder(int lev, struct node *curr)
{
	if(curr != NULL)
	{
		inorder(lev+1, curr->left);
		printf("level: %d - Movie Name: %s - Movie Rate: %.2f\n", lev, curr->name, curr->rate);
		inorder(lev+1, curr->right);
	}
}

int main()
{
	FILE *fp = fopen("movie_data.csv", "r");
	
	fscanf(fp, "%*[^,],%*s\n");
	
	char name[101];
	float rate;
	
	for(int i = 0; i < 50; i++)
	{
		fscanf(fp, "%[^,],%f\n", &name, &rate);
		insertNode(root, name, rate);
	}
	inorder(0,root);
	
	int menu;
	node *tmp;
	while(1)
	{
		puts("1.Insert");	
		puts("2.Search");	
		puts("3.Exit");
		scanf("%d", &menu); getchar();
		switch(menu)
		{
			case 1:
				puts("Masukan Judul Film:");
				scanf("%[^\n]", &name);
				puts("Masukan Rating Film:");
				scanf("%f", &rate);
				if(strlen(name) > 100 || rate > 10 || rate < 1 || strlen(name) < 1) puts("Data tidak berhasil dimasukkan");
				else 
				{
					insertNode(root, name, rate);
					puts("Data berhasil dimasukkan");
					inorder(0,root);
				}
				break;
			case 2:
				puts("Masukan Judul Film:");
				scanf("%[^\n]", &name);
				tmp = search(root, name);
				if(tmp == NULL) puts("Data tidak ditemukan");
				else printf("Movie Name: %s, Movie Rate: %.2f\n", tmp->name, tmp->rate);
				break;
			case 3:
				return 0;
			default:
				puts("Wrong Input");
				break;
		}
	}
	
}
