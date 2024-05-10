#include<stdio.h>
#include<stdlib.h>

struct data{
	int queue;
	data*next=NULL;
}*head=NULL,*tail=NULL;


data*createNode(int queue){
	data*toInsert=(data*)malloc(sizeof(queue));
	toInsert->queue=queue;
	toInsert->next=NULL;
	return toInsert;
}

void pushHead(int queue){
	data*toInsert=createNode(queue);
	if(head==NULL){
		head=toInsert;
		tail=toInsert;
	}
	else{
		toInsert->next=head;
		head=toInsert;
	}
}
void pushMid(int queue){
	data*toInsert=createNode(queue);
	if(head==NULL){
		head=toInsert;
		tail=toInsert;
	}
	else{
		data*curr=head;
		if(queue<curr->queue){
			pushHead(queue);
			return;
		}
		while(curr->next!=NULL&&curr->next->queue<queue){
			curr=curr->next;
		}
		toInsert->next=curr->next;
		curr->next=toInsert;
		
		if(tail==curr){
			tail=toInsert;
		}
	}
}

void popHead(){
	data*temp=head->next;
	free(head);
	head=temp;
}

void popTail(){
	data*curr=head;
	while(curr->next->next!=NULL){
		curr=curr->next;
	}
	free(curr->next);
	curr->next=NULL;
}

void popMid(int key){
	if(head==NULL){
		return;
	}
	data*curr=head;
	
	if(head->queue==key){
		popHead();
		return;
	}
	
	if(tail->queue==key){
		popTail();
		return;
	}
	
	while(curr->next!=NULL&&curr->next->queue!=key){
		curr=curr->next;
	}
	
	data*del=curr->next;
	curr->next=del->next;
	free(del);
}
	
void print(){
	
	data*curr=head;
	
	while(curr!=NULL){
		printf("%d\n",curr->queue);
		curr=curr->next;
	}
}

int main(){
	
	
	pushMid(5);
	pushMid(50);
	pushMid(3);
	pushMid(30);
	pushMid(12);
	pushMid(4);

	print();

	
	puts("___________\n");
	
	popMid(3);
	print();
	
	
	return 0;
}
