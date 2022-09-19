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
Node* create_new_node(int val) {
	Node* tmp = (Node*)malloc(sizeof(Node));

	tmp->value = val;
	tmp->next = NULL;

	return tmp;
}

// Initialize a queue
Queue* queue_init() {
	Queue* q = (Queue*)malloc(sizeof(Queue));

	q->head = q->tail = NULL;

	return q;
}

void enqueue(Queue* q, int val) {
	Node* tmp = create_new_node(val);

	// Empty queue
	if (q->tail == NULL) {
		q->head = q->tail = tmp;
		return;
	}

	q->tail->next = tmp;
	q->tail = tmp;
}

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
  Node *tmp = q->head;

  if (tmp == NULL) {
    printf("\n>Empty queue\n");
  }

  while(tmp != NULL){
    printf("%d <~~~ ", tmp->value);
    tmp = tmp->next;
  }
}

int search(Queue* q, int val) {
  // -1 means no item in queue with such value
  int index = 0;

  Node *tmp = q->head;

  if (tmp == NULL) {
    printf("\n>Empty queue. Nothing to search\n");
    return QUEUE_EMPTY;
  }

  while(tmp != NULL){
    if(tmp->value == val) {
      printf("\nValue %d found at index: %d\n", tmp->value, index);
      return index;
    }

    index += 1;
    tmp = tmp->next;
  }

  // if no index is returned it means there is no such value in queue
  printf("\nNo element with value %d in queue\n", val);
  
  return index;
}

void sort(Queue* q, int n) {
  Node **ptr, *tmp;

  if (q->head == NULL){
    printf("\n>Empty queue. Nothing to sort\n");
    return;
  }

  int i;
  // n elements in queue
  for(i = 0; i < n; i++) {
    for(ptr = &q->head; tmp = *ptr; ptr = &(*ptr)->next) {
      Node *other = tmp->next;

      if (!tmp->next) break;
      if (tmp->value < other->value) continue;

      *ptr = other;              
      tmp->next = other->next; 
      other->next = tmp;       
    }
  }  

  return;
}

void reverse(Queue *q) {
  int tmp;

  // Recursion base case: empty queue
  if (q->head == NULL) {
      return;
  }
  
  // using stack we dequeue each element
  // then enque the value into the same queue
  tmp = dequeue(q);
  reverse(q);
  enqueue(q, tmp);
}

int main() {
	Queue* q = queue_init();

  int i, n, m, k, s;

  while (k != 9) {
    printf("\n======== MENU ======== \n");
    printf("| 1 - enqueue        |\n");
    printf("| 2 - dequeue        |\n");
    printf("| 3 - show queue     |\n");
    printf("| 4 - search         |\n");
    printf("| 5 - sort           |\n");
    printf("| 6 - reverse        |\n");
    printf("| 9 - exit terminal  |\n");
    printf("======== MENU ======== \n");
    
    scanf("%d", &k);

    switch (k) {
      case 1:
        printf("\n>How many elements to enqueue? \n");
        scanf("%d", &n);

        for(i = 0; i < n; i++) {
          scanf("%d", &m);
          enqueue(q, m);
        }
        break;
      case 2:
        printf("\n>How many elements to dequeue? \n");
        scanf("%d", &n);

        for(i = 0; i < n; i++) {
          dequeue(q);
        }
        break;
      case 3:
        printf("\n");
        display_queue(q);
        printf("\n");
        break;
      case 4:
        printf("\n>Element value? \n");
        scanf("%d", &s);
        search(q, s);
        break;
      case 5:
        sort(q, n);
        printf("\n>Queue was sorted \n");
        break;
      case 6:
        reverse(q);
        printf("\n>Queue was reversed \n");
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
