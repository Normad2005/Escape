//read testcase69.txt
#include <stdio.h>
#include <stdlib.h>

enum{up, down,
	back, front,
	right, left
};

enum{false, true}bool;

typedef struct Node{
	int z, x, y;
	char val;
	int visited;
	struct Node *neighbors[6];
	struct Node *next;
}Node;

Node *head, *tail, *origin;

Node *newNode(int z, int x, int y, char ch){
	Node *n = (Node *)malloc(sizeof(Node));
	n->z = z;
	n->x = x;
	n->y = y;
	n->val = ch;
	for(int i=0;i<6;i++)
		n->neighbors[i] = 0;
	n->next = NULL;
	n->visited = 0;
	return n;
}

void enqueue(Node *node){
	if(tail)
		tail->next = node;
	tail = node;
	if(!head)
		head = tail;
}

Node *dequeue(){
	Node *temp = head;
	head = head->next;
	if(!head)
		tail = NULL;
	return temp;
}

Node *find(int z, int x, int y){
	Node *tmp = origin;
	while(z--) tmp = tmp->neighbors[up];
	while(x--) tmp = tmp->neighbors[back];
	while(y--) tmp = tmp->neighbors[right];
	return tmp;
}

int isEmpty(){
	return !head;
}
FILE *fin, *fout;

int main(){
	fin = fopen("testcase69.txt", "r");
	int h, r, c;
	char ch;
	Node *temp, *start, *exit, *adj;
	while(fscanf(fin, "%d%d%d", &h, &r, &c) && (h||r||c)){
		for(int z=0;z<h;z++)
		for(int x=0;x<r;x++)
		for(int y=0;y<c;y++){
			do ch = fgetc(fin);
			while(ch != '#' && ch != '.' && ch != 'S' && ch != 'E');
			
			temp = newNode(z, x, y, ch);
			
			if(!(x||y||z)) origin = temp;
			if(temp->val == 'S') start = temp;
			if(temp->val == 'E') exit = temp;

			if(z){
				adj = find(z-1, x, y);
				adj->neighbors[up] = temp;
				temp->neighbors[down] = adj;
			}
			if(x){
				adj = find(z, x-1, y);
				adj->neighbors[back] = temp;
				temp->neighbors[front] = adj;
			}
			if(y){
				adj = find(z, x, y-1);
				adj->neighbors[right] = temp;
				temp->neighbors[left] = adj;
			}
		}
		
		start->visited = 1;
		enqueue(start);
		int ok = false;
		
		while(!isEmpty()){
			temp = dequeue();
			if(temp->val =='E'){
				printf("Escaped in %d step(s).\n", temp->visited-1);
				ok = true;
				break;
			}
			for(int i=0;i<6;i++){
				adj = temp->neighbors[i];
				if(!adj || adj->visited || adj->val == '#') continue;
				adj->visited = temp->visited + 1;
				enqueue(adj);
			}
		}
		if(!ok)
			printf("Trapped!\n");
	}
	return 0;
}


