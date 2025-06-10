#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Edge{
	int u, v, w;
}Edge;

int id[1010], idx = 0, ans[40000];
Edge e[40000];

int find(int i){
	while(id[i] != i) i = id[i];
	return i;
}

void Union(int u, int v){
	int rootu = find(u);
	int rootv = find(v);
	if(rootu != rootv)
		id[rootu] = rootv;
}

void init(){
	for(int i=0;i<1010;i++)
		id[i] = i;
	idx = 0;
	memset(e, 0, sizeof(e));
	memset(ans, 0, sizeof(ans));
}

int cmp(const void *a, const void *b){
	Edge ea = *(Edge *)a;
	Edge eb = *(Edge *)b;
	return ea.w - eb.w;
}

int main(){
	FILE *fin, *fout;
	fin = fopen("testcase70.txt", "r");
	fout = fopen("eeoo1.txt", "w");
	 
	int n, m, u, v, w;
	while(fscanf(fin, "%d%d", &n, &m) && (n || m)){
		init();
		
		for(int i=0;i<m;i++){
			fscanf(fin, "%d%d%d", &u, &v, &w);
			e[i].u = u;
			e[i].v = v;
			e[i].w = w;
		}
		
		qsort(e, m, sizeof(Edge), cmp);
		
		for(int i=0;i<m;i++){
			u = e[i].u;
			v = e[i].v;
			if(find(u) == find(v))
				ans[idx++] = e[i].w;
			else
				Union(u, v);
		}
		if(idx){
			for(int i=0;i<idx;i++){
				printf("%d ", ans[i]);
			}printf("\n");
		}
		else
			printf("forest\n");
		
	}
	return 0;
}
