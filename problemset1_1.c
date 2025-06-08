//testcase: testcase1.txt
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 55
typedef struct edge{
	int id;
	int to;
	int visited;
	struct edge *rev;
	struct edge *next;
}edge; 

edge *graph[N];
int deg[N];
int path[2000];
int path_idx;

void add_edge(int u, int v, int id){
	edge *e1 = (edge *)malloc(sizeof(edge));
	edge *e2 = (edge *)malloc(sizeof(edge));
	
	e1->to = v;
	e1->next = NULL;
	e1->visited = 0;
	e1->rev = e2;
	e1->id = id;
	e1->next = graph[u];
	graph[u] = e1;
	
	e2->to = u;
	e2->next = NULL;
	e2->visited = 0;
	e2->rev = e1;
	e2->id = id;
	e2->next = graph[v];
	graph[v] = e2;
}

int cmp(const void *a, const void *b){
	edge *e1 = *(edge **)a;
	edge *e2 = *(edge **)b;
	return e1->id - e2->id;
}

void sort_edge(int u){
	edge *temp[2000];
	int n = 0;
	for(edge *e = graph[u];e;e = e->next){
		temp[n++] = e;
	}
	qsort(temp, n, sizeof(edge *), cmp);
	graph[u] = NULL;
	for(int i=n-1;i>=0;i--){
		temp[i]->next = graph[u];
		graph[u] = temp[i];
	}
}

void dfs(int u){
	for(edge *e = graph[u];e;e=e->next){
		if(!e->visited){
			e->visited = 1;
			e->rev->visited = 1;
			dfs(e->to);
			path[path_idx++] = e->id;
		}
	}
}

void reset(){
	memset(graph, 0, sizeof(graph));
	memset(path, 0, sizeof(path));
	path_idx = 0;
	memset(deg, 0, sizeof(deg));
}

FILE *fin, *fout;
int main(){
	fin = fopen("testcase1.txt", "r");
	
	int u, v, w, start;
	while(fscanf(fin, "%d%d", &u, &v) && (u || v)){
		reset();
		fscanf(fin, "%d", &w);
		start = (u < v) ? u : v;
		add_edge(u, v, w);
		deg[u]++;
		deg[v]++;
		while(fscanf(fin, "%d%d", &u, &v) && (u || v)){
			fscanf(fin, "%d", &w);
			add_edge(u, v, w);
			deg[u]++;
			deg[v]++;
		}
		int ok = 1;
		for(int i=0;i<50;i++){
			if(deg[i]%2 != 0){
				ok = 0;
			}
		}
		if(!ok){
			printf("Round trip does not exist.\n\n");
			continue;
		}
		
		for(int i=0;i<50;i++)
			sort_edge(i);
		dfs(start);
		for(int i=--path_idx;i>=0;i--){
			printf("%d ", path[i]);
		}printf("\n\n");
	}
}


