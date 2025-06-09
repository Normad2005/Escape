#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int digit;
	struct Node *next;
}Node;

FILE *fin, *fout;

Node *newNode(int digit){
	Node *n = (Node *)malloc(sizeof(Node));
	n->digit = digit;
	n->next = NULL;
	return n;
}

Node *rev(Node *head){
	Node *trail = NULL;
	Node *middle = NULL;
	Node *lead = head;
	
	while(lead){
		trail = middle;
		middle = lead;
		lead = lead->next;
		middle->next = trail;
	}
	
	return middle;
}

int main(){
	int n;
	fin = fopen("testcase2_1.txt", "r");
	fout = fopen("output2_1.txt", "w");

	while(fscanf(fin, "%d", &n) != EOF){
		Node *head = newNode(1);
		
		for(int i=1;i<=n;i++){
			Node *cur = head;
			int carry = 0;
			while(cur){
				int total = i*(cur->digit) + carry;
				int digit = total % 10;
				carry = total / 10;
				cur->digit = digit;
				cur = cur->next;
			}
			
			cur = head;
			while(cur->next) cur = cur->next;
			
			while(carry){
				int a = carry%10;
				Node *tmp = newNode(a);
				cur->next = tmp;
				cur = cur->next;
				carry /= 10;
			}
		}
		head = rev(head);
		Node *cur = head;
		fprintf(fout ,"%d! = ", n);
		while(cur){
			fprintf(fout, "%d", cur->digit);
			cur = cur->next;
		}fprintf(fout, "\n");
	}
	return 0;
}
