//read testcase74.txt
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 200005
int tree[(1<<19)];
int pos[MAXN];
int timestamp;

void update(int node, int l, int r, int x, int v){
	if(x < l || x > r) return;
	if(l == r){
		tree[node] += v;
		return;
	}
	int mid = (l+r)/2;
	update(2*node, l, mid, x, v);
	update(2*node + 1, mid+1, r, x, v);
	tree[node] = tree[node*2] + tree[node*2 + 1];
}

int query(int node, int l, int r, int ql, int qr){
	if(qr<l || ql>r) return 0;
	if(ql <= l && r <= qr) return tree[node];
	int mid = (l+r)/2;
	return query(node*2, l, mid, ql, qr) + query(node*2 + 1, mid+1, r, ql, qr); 
}
FILE *fin;
int main(){
	
	fin = fopen("testcase74.txt", "r");
	int t, n, m;
	fscanf(fin, "%d", &t);
	while(t--){
		memset(tree, 0, sizeof(tree));
		fscanf(fin, "%d%d", &n, &m);
		timestamp = n;
		for(int i=1;i<=n;i++){
			pos[i] = n - i + 1;
			update(1, 1, MAXN, pos[i], 1);
		}
		
		for(int i=0;i<m;i++){
			int a, res;
			fscanf(fin, "%d", &a);
			res = query(1, 1, MAXN, pos[a] + 1, MAXN);
			printf("%d ", res);
			
			update(1, 1, MAXN, pos[a], -1);
			pos[a] = ++timestamp;
			update(1, 1, MAXN, pos[a], 1);
		}printf("\n");
	}
	return 0;
}
