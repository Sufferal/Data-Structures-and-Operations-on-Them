#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define QUEUE_EMPTY INT_MIN

// Linked list
typedef struct Node {
	int value;
	struct Node* next;
} Node;

// Queue 
typedef struct Queue {
	Node *head;
	Node *tail;
} Queue;

// Create new node
Node* create_new_node(int value) {
	Node* tmp = (Node*)malloc(sizeof(Node));

	tmp->value = value;
	tmp->next = NULL;

	return tmp;
}

// Initialize a queue
Queue* queue_init() {
	Queue* q = (Queue*)malloc(sizeof(Queue));

	q->head = q->tail = NULL;

	return q;
}

// The function to add a value to a queue
void enqueue(Queue* q, int value) {
	Node* tmp = create_new_node(value);

	// Empty queue
	if (q->tail == NULL) {
		q->head = q->tail = tmp;
		return;
	}

	q->tail->next = tmp;
	q->tail = tmp;
}

// Function to remove a value from given queue 
int dequeue(Queue* q) {
	// Empty queue
	if (q->head == NULL)
		return QUEUE_EMPTY;

	// Store head 
	Node* tmp = q->head;
	q->head = q->head->next;
  int res = tmp->value;

	// Queue with one value
	if (q->head == NULL)
		q->tail = NULL;

  // Deallocate the memory
	free(tmp);

  return res;
}

void display_queue(Queue* q) {
  int i = 0;
  Node *tmp = q->head;

  if (tmp == NULL) {
    printf("\n>Empty queue\n");
  }

  while(tmp != NULL){
    i += 1;
    printf("%d <~~~ ", tmp->value);
    tmp = tmp->next;
  }
}

int main() {
	Queue* q = queue_init();

  int i, n, m, k;

  while (k != 9) {
    printf("\n======== MENU ======== \n");
    printf("| 1 - enqueue        |\n");
    printf("| 2 - dequeue        |\n");
    printf("| 3 - show queue     |\n");
    printf("| 9 - exit terminal  |\n");
    printf("======== MENU ======== \n");
    
    scanf("%d", &k);

    switch (k) {
      case 1:
        printf("\n>How many items to enqueue? \n");
        scanf("%d", &n);

        for(i = 0; i < n; i++) {
          scanf("%d", &m);
          enqueue(q, m);
        }
        break;
      case 2:
        printf("\n>How many items to dequeue? \n");
        scanf("%d", &n);

        for(i = 0; i < n; i++) {
          dequeue(q);
        }
        break;
      case 3:
        display_queue(q);
        break;
      case 9:
        printf(">Exit complete \n");
        break;
      default:
        printf("\n>Enter a valid value \n");
        break;
    }
  }

	return 0;
}
