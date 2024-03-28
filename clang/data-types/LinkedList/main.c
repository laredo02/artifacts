
#include <stdio.h>
#include <stdlib.h>

struct node_t {
	int data;
	struct node_t *next;
};

struct node_t *addNode(struct node_t *head, int value) {
	struct node_t *temp, *p;
	temp = (struct node_t *) malloc(sizeof(struct node_t));
	temp->data = value;
	temp->next = NULL;
	if (head == NULL) {
		head = temp;
	} else {
		p = head;
		while (p->next != NULL) {
			p = p-> next;
		} 
		p->next = temp;
	}
	return head;
}

void printList(struct node_t *head)
{
	while (head->next != NULL) {
		printf("next = %p\tvalue = %d\n", head->next, head->data);
		head = head->next;
	}
}

int main()
{
	struct node_t *head = addNode(NULL, 0);
	for (int i=1; i<10; i++) {
		addNode(head, i);
	}
	
	printList(head);
	return 0;
}

