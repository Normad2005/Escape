#include <stdio.h>
#include <stdlib.h> 

typedef struct Node{
	int val;
	struct Node *left, *right;
}Node;

int inid[600060];

Node *newNode(int val){
	Node *n = (Node *)malloc(sizeof(Node));
	n->val = val;
	n->left = n->right = 0;
	return n; 
}

Node *build(int *postorder, int *index, int start, int end){
	if((*index) < 0  || !(start <= end)) return NULL;
	
	int root_val = postorder[*index];
	int mid = inid[root_val];
	Node *root = newNode(root_val);
	(*index)--;
	
	root->right = build(postorder, index, mid+1, end);
	root->left = build(postorder, index, start, mid-1);
	return root;
}

void preorder(Node *root){
	if(root){
		printf("%d ", root->val);
		preorder(root->left);
		preorder(root->right);
	}
}



FILE *fin, *fout;

int main(){
	int t, n, a;
	fin = fopen("testcase72.txt", "r");
	fout = fopen("eeooeeoo.txt", "w");
	
	fscanf(fin, "%d", &t);
	while(t--){
		
		fscanf(fin, "%d", &n);
		int postorder[n];
		for(int i=0;i<n;i++){
			fscanf(fin, "%d", &a);
			inid[a] = i;
		}
		for(int i=0;i<n;i++){
			fscanf(fin, "%d", &a);
			postorder[i] = a;
		}
		int index = n-1;
		
		Node *root = build(postorder, &index, 0, n-1);
		
		preorder(root);
		printf("\n");
	}
	return 0;
}
