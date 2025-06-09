#include <stdio.h>
#include <stdlib.h>

enum{
	up, down,
	back, front,
	right, left
};

typedef struct Node{
	int z, x, y;
	char val;
	int visited;
	struct Node *neighbors[6];
	struct Node *next;
}Node;

Node *head, *tail, *origin;

Node *newNode(int z, int x, int y, char val){
	Node *n = (Node *)malloc(sizeof(Node));
	n->next = NULL;
	n->visited = 0;
	n->val = val;
	n->x = x;
	n->y = y;
	n->z = z;
	for(int i=0;i<6;i++)
		n->neighbors[i] = 0;
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

int isEmpty(){
	return !head;
}

Node *find(int z, int x, int y){
	Node *tmp = origin;
	while(z--) tmp = tmp->neighbors[up];
	while(x--) tmp = tmp->neighbors[back];
	while(y--) tmp = tmp->neighbors[right];
	return tmp;
}
FILE *fin, *fout;

int main(){
	fin = fopen("testcase69.txt", "r");
	int h, r, c;
	char ch;
	Node *start, *tmp, *adj, *exit;
	while(fscanf(fin, "%d%d%d", &h, &r, &c) && (h||r||c)){
		for(int z=0;z<h;z++)
		for(int x=0;x<r;x++)
		for(int y=0;y<c;y++){
			do ch = fgetc(fin);
			while(ch != '#' && ch != '.' && ch != 'S' && ch != 'E');
			
			tmp = newNode(z, x, y, ch);
			if(!(z||x||y)) origin = tmp;
			if(tmp->val == 'S') start = tmp;
			else if(tmp->val == 'E') exit = tmp;
			
			if(z){
				adj = find(z-1, x, y);
				adj->neighbors[up] = tmp;
				tmp->neighbors[down] = adj;
			}
			if(x){
				adj = find(z, x-1, y);
				adj->neighbors[back] = tmp;
				tmp->neighbors[front] = adj;
			}
			if(y){
				adj = find(z, x, y-1);
				adj->neighbors[right] = tmp;
				tmp->neighbors[left] = adj;
			}
		}
		
		start->visited = 1;
		enqueue(start);
		int found = 0;
		
		while(!isEmpty()){
			tmp = dequeue();
			if(tmp->val == 'E'){
				found = 1;
				printf("Escaped in %d step(s).\n", tmp->visited-1);
				break;
			}
			
			for(int i=0;i<6;i++){
				Node *n = tmp->neighbors[i];
				if(!n || n->visited || n->val == '#') continue;
				n->visited = tmp->visited+1;
				enqueue(n);
			}
		}
		
		if(!found) printf("Trapped!\n");
	} 
	
	
	return 0;
}


