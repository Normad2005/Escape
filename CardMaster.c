//read testcase.txt
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int order, num;
	struct Node *prev, *next;
}Node; 

struct LinkedList{
	struct Node *head;
}Cards;

int ans[1001];
int idx = 0;
FILE *fin, *fout; 

int gcd(int a, int b){
	int r = a%b;
	if(!r) return b;
	else return gcd(b, r);
}

Node *newNode(int order, int num){
	Node *n = (Node *)malloc(sizeof(Node));
	n->next = NULL;
	n->prev = NULL;
	n->order = order;
	n->num = num;
	return n;
}

void delNode(Node *node){
	node->prev->next = node->next;
	node->next->prev = node->prev;
	ans[idx++] = node->order;
	free(node);
}

int main(){
	fin = fopen("testcase.txt", "r");
	fout = fopen("fuck1.txt", "w");
	int t, n, preG, curG, a;
	Node *prev, *cur, *temp, *last;
	fscanf(fin, "%d", &t);
	while(t--){
		fscanf(fin, "%d", &n);
		idx = 0;
		Cards.head = newNode(0, -1);
		last = Cards.head;
		for(int i=1;i<=n;i++){
			fscanf(fin, "%d", &a);
			temp = newNode(i, a);
			last->next = temp;
			temp->prev = last;
			last = temp;
		}
		last->next = Cards.head;
		Cards.head->prev = last;
		
		
		int removed = 2;
		cur = Cards.head->next->next;
		preG = 0;
		while(removed > 0 && cur->next->next != cur){
			removed -= 1;
			while(cur != Cards.head){
				prev = (cur->prev == Cards.head) ? cur->prev->prev : cur->prev;
				curG = gcd(cur->num, prev->num);
				if(curG == preG && curG > 1){
					removed = 1;
					cur = cur->next;
					delNode(cur->prev);
				}
				else{
					cur = cur->next;
					preG = curG;
				}
			}
			cur = cur->next;
		}
		printf("%d ", idx);
		for(int i=0;i<idx;i++){
			printf("%d ", ans[i]);
		}printf("\n");
		free(Cards.head);
	}
	
}
