#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct MemberNode{
	int id;
	struct MemberNode *next;
}MemberNode;

typedef struct TeamNode{
	int teamID;
	struct MemberNode *front;
	struct MemberNode *rear;
	struct TeamNode *next;
}TeamNode;

int team[1000001];

void enq(TeamNode *t, MemberNode *node){
	if(!t->front && !t->rear)
		t->front = t->rear = node;
	
	else{
		t->rear->next = node;
		t->rear = node;
	}
}

MemberNode *deq(TeamNode *t){
	MemberNode *n = t->front;
	t->front = t->front->next;
	if(!t->front)
		t->rear = NULL;
	return n;
}

MemberNode *newM(int id){
	MemberNode *n = (MemberNode *)malloc(sizeof(MemberNode));
	n->id = id;
	n->next = NULL;
	return n;
} 

TeamNode *newT(int id){
	TeamNode *t = (TeamNode *)malloc(sizeof(TeamNode));
	t->teamID = id;
	t->front = t->next = t->rear = NULL;
}

int main(){
	FILE *fin = fopen("testcase2_2.txt", "r");
	int n, m, a;
	char buff[20];
	while(fscanf(fin, "%d", &n) && n){
		for(int i=0;i<n;i++){
			fscanf(fin, "%d", &m);
			for(int j=0;j<m;j++){
				fscanf(fin, "%d", &a);
				team[a] = i;
			}
		}
		
		TeamNode *head = newT(-1);
		while(1){
			fscanf(fin, "%s", buff);
			if(!strcmp(buff, "CLOSE")){
				break;
			}
			else if(!strcmp(buff, "ARRIVE")){
				int a, tid, found = 0;
				fscanf(fin, "%d", &a);
				tid = team[a];
				MemberNode *temp = newM(a);
				TeamNode *cur = head;
				while(cur){
					if(cur->teamID == tid){
						enq(cur, temp);
						found = 1;
					}
					cur = cur->next;
				}
				if(!found){
					cur = head;
					while(cur->next) cur = cur->next;
					TeamNode *t = newT(tid);
					enq(t, temp);
					cur->next = t;
				}
			}
			else if(!strcmp(buff, "SERVE")){
				TeamNode *t = head->next;
				MemberNode *m = deq(t);
				if(!t->front && !t->rear){
					head->next = t->next;
					free(t);
				}
				printf("%d\n", m->id);
			}
		}
	}
	
}
