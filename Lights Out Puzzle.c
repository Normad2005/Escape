#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int flipmsk[25];
int r, c, minCnt, bestP;

void dfs(int btn, int cnt, int pressed, int panel){
	if(cnt > minCnt) return;
	if(btn == r*c){
		if(!panel){
			bestP = pressed;
			minCnt = cnt;
		}
		return;
	}
	dfs(btn+1, cnt, pressed, panel);
	dfs(btn+1, cnt+1, pressed | (1<<btn), panel ^ flipmsk[btn]);
}

int main(){
	FILE *fin = fopen("testcase75.txt", "r");
	
	int tc=1, panel;
	char ch;
	while(fscanf(fin, "%d %d", &r, &c) &&(r || c)){
		memset(flipmsk, 0, sizeof(flipmsk));
		for(int i=-1;i<=1;i++)
		for(int j=-1;j<=1;j++){
			do {
			    ch = fgetc(fin);
			} while (ch != '*' && ch != '.');
			
			if(ch == '*')
				for(int k=0;k<r*c;k++){
					if(k+i*c<0 || k+i*c >= r*c) continue;
					if(k+j < 0 || (k+j)/c != k/c) continue;
					flipmsk[k] |= 1 << (k + i*c + j);
				}
		}
		minCnt = 26;
		panel = (1 << (r*c))-1;
		
		dfs(0, 0, 0, panel);
		
		
		printf("Case #%d\n", tc++);
		if(minCnt == 26)
			printf("Impossible");
		else{
			for(int i=1;bestP; bestP >>= 1, i++){
				if(bestP & 1)
					printf("%d ", i);
			}
		}printf("\n");
	}
	return 0; 
}
