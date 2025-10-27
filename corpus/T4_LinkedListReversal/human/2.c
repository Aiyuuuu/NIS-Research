/* Emircan Kirez - Ch3rry */
/* Last Update: 20/07/2022 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int value;
	struct node *next;
}NODE;

void insert(NODE **head, int value);
NODE *createNode(int value);
void printList(NODE *head);
void reverse(NODE **head);

int main(){
	NODE *head = NULL;
	int value;

	printf("Enter integers (Ctrl+D to end):\n");
	while (scanf("%d", &value) == 1) {
		insert(&head, value);
	}

	printf("Original list:\n");
	printList(head);

	reverse(&head);
	printf("Reversed list:\n");
	printList(head);

	reverse(&head);
	printf("Restored list:\n");
	printList(head);

	return 0;
}

void insert(NODE **head, int value){
	NODE *newNode = createNode(value);
	newNode->next = *head;
	*head = newNode;
}

NODE *createNode(int value){
	NODE *tmp = (NODE *)malloc(sizeof(NODE));
	tmp->value = value;
	tmp->next = NULL;
	return tmp;
}

void printList(NODE *head){
	while(head != NULL){
		printf("%d ", head->value);
		head = head->next;
	}
	printf("\n");
}

void reverse(NODE **head){
	NODE *prev = NULL, *current = *head, *next;
	while(current != NULL){
		next = current->next; //save next node
		current->next = prev; //current node shows previous node
		prev = current; //update prev node
		current = next; //update current node
	}
	*head = prev;
}

