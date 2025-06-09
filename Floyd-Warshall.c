#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int dist1[105][105];
int dist2[105][105];

int n;
FILE *fin, *fout;

void init(){
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			dist1[i][j] = (i == j) ? 0 : INT_MAX;
			dist2[i][j] = (i == j) ? 0 : INT_MAX;
		}
}

void floyd1(){
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			if(dist1[i][k] == INT_MAX) continue;
			for(int j=0;j<n;j++){
				if(dist1[k][j] == INT_MAX) continue;
				if(dist1[i][k] + dist1[k][j] < dist1[i][j]){
					dist1[i][j] = dist1[i][k] + dist1[k][j];
				}
			}
		}
	}
}

void floyd2(){
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			if(dist2[i][k] == INT_MAX) continue;
			for(int j=0;j<n;j++){
				if(dist2[k][j] == INT_MAX) continue;
				if(dist2[i][k] + dist2[k][j] < dist2[i][j]){
					dist2[i][j] = dist2[i][k] + dist2[k][j];
				}
			}
		}
	}
}

void read(int tell){
	int u, v;
	char ch;
	fscanf(fin, "%d", &u);
	while(1){
		fscanf(fin, "%d", &v);
		if(tell == 1) dist1[u-1][v-1] = 1;
		else dist2[u-1][v-1] = 1;
		do ch = fgetc(fin);
		while(ch != ' ' && ch != '\n');
		if(ch == '\n') break;
	}
}

int ok(int A, int B){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(dist1[i][j] != INT_MAX && dist2[i][j] == INT_MAX){
				return 0;
			}
			if(dist1[i][j] == INT_MAX || dist2[i][j] == INT_MAX) continue;
			int t = dist1[i][j]*A + B;
			if(dist2[i][j] > t)
				return 0;
		}
	}
	return 1;
}

int max(){
	int max = -1;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(dist1[i][j] > max)
				max = dist1[i][j];
		}
	}
	return max;
}

int main(){
	fin = fopen("testcase71.txt", "r");
	//fout = fopen("eeoo4_1.txt", "w");
	
	while(fscanf(fin, "%d", &n) && n){
		
		init();
		int A, B, maxium, okay;
		for(int i=0;i<n;i++) read(1);
		for(int i=0;i<n;i++) read(2);
		fscanf(fin, "%d%d", &A, &B);
		floyd1();
		floyd2();
		okay = ok(A, B);
		maxium = max();
		if(okay) printf("Yes ");
		else printf("No ");
		printf("%d\n", maxium);
	}	
	return 0;
}
