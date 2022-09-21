#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_EMPTY INT_MIN
#define MIN_PRIORITY 999

// Linked list
typedef struct Node {
	int value;
  int priority;
	struct Node* next;
} Node;

// Queue 
typedef struct Queue {
	Node *head;
	Node *tail;
} Queue;

// Initialize a queue
Queue* queue_init() {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->head = q->tail = NULL;
	return q;
}

// check if queue is empty
int isEmpty(Queue* q) {
  return q->head == NULL;
}

// Get the value of first element
int peek(Queue* q) {
  return q->head->value;
}

void enqueue(Queue* q, int val) {
  Node* tmp = (Node*)malloc(sizeof(Node));

	tmp->value = val;
  tmp->priority = MIN_PRIORITY;
	tmp->next = NULL;

	// Empty queue
	if (q->tail == NULL) {
		q->head = q->tail = tmp;
		return;
	}

	q->tail->next = tmp;
	q->tail = tmp;
}

void p_enqueue(Queue* q, int val, int priority) {
  Node* new_node = malloc(sizeof(Node));

  new_node->value = val;
  new_node->next = NULL;
  new_node->priority = priority;

  if(!isEmpty(q)) {
    if(new_node->priority < q->head->priority) {
      new_node->next = q->head;
      q->head = new_node;
    }
    else {
      Node* prev = q->head;
      Node* tmp = q->head->next;

      while(tmp != NULL && tmp->priority < new_node->priority) {
        prev = tmp;
        tmp = tmp->next;
      }

      if(tmp == NULL) {
        prev->next = new_node;
        q->tail = new_node;
      } else {
        new_node->next = tmp;
        prev->next = new_node;
      }
    }
  } else {
    q->head = new_node;
    q->tail = new_node;
  }
}

void c_enqueue(Queue* q, int val) {
  Node* tmp = (Node*)malloc(sizeof(Node));

	tmp->value = val;
  tmp->priority = MIN_PRIORITY;
	tmp->next = NULL;

	// Empty queue
	if (q->tail == NULL) {
		q->head = q->tail = tmp;
    q->tail->next = q->head;
		return;
	}

	q->tail->next = tmp;
	q->tail = tmp;
  q->tail->next = q->head;
}

// returns an array with value and priority
int* dequeue(Queue* q) {
  static int res[2];

	// Empty queue
	if (isEmpty(q))
		return res;

	// Store head 
	Node* tmp = q->head;
  res[0] = tmp->value;
  res[1] = tmp->priority;

	q->head = q->head->next;

	// if head becomes NULL
	if (q->head == NULL)
		q->tail = NULL;

  // Deallocate the memory
	free(tmp);

  return res;
}

void display_queue(Queue* q, int queue_type) {
  Node* tmp = q->head;

  if (tmp == NULL) {
    printf("\n>Empty queue\n");
    return;
  }

  if(queue_type == 2) {
    printf("value(priority): \n");
  } else if(queue_type == 3) {
    printf("Address of q->head: %p\n", q->head);
    printf("Address of q->tail->next: %p\n", q->tail->next);
    while(tmp->next != q->head) {
      printf("%d <~~~ ", tmp->value);
      tmp = tmp->next;
    }
    printf("%d", tmp->value);
    return;
  }

  while(tmp != NULL){
    switch (queue_type) {
    // normal queue
    case 1:
      printf("%d <~~~ ", tmp->value);
      break;

    // priority queue
    case 2:
      printf("%d(%d) <~~~ ", tmp->value, tmp->priority);
      break;

    default:
      printf("\n>Invalid queue type \n");
      break;
    }

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

void reverse(Queue *q, int queue_type) {
  int tmp[2];

  // Recursion base case: empty queue
  if (q->head == NULL) {
      return;
  }
  
  // using stack we dequeue each element
  // then enque the value into the same queue
  // tmp = dequeue(q);
  memcpy(tmp, dequeue(q), sizeof dequeue(q));
  reverse(q, queue_type);

  if(queue_type == 1) {
    enqueue(q, tmp[0]);
  } else if(queue_type == 2) {
    printf("%d(%d) <~~~ ", tmp[0], tmp[1]);
    p_enqueue(q, tmp[0], tmp[1]);
  }
}

int main() {
	Queue* q = queue_init();

  int i, n, m, p, k, s;
  /*
    i - loop variable
    n - number of elements to enqueue/dequeue
    m - value of element to enqueue/dequeue
    p - priority
    k - interactive menu keyboard variable
    s - search value variable
  */

  int queue_type;

  printf("\n>Type of queue? \n");
  printf("| 1 - normal      |\n");
  printf("| 2 - priority    |\n");
  printf("| 3 - circular    |\n");

  scanf("%d", &queue_type);
  switch (queue_type) {
    case 1:
      printf("Normal queue:      \n");
      break;
    case 2: 
      printf("Priority queue:    \n");
      break;
    case 3: 
      printf("Circular queue:    \n");
      break;
  default:
    printf("\n>Invalid queue type \n");
    break;
  }

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
          printf("\n>Value? \n");
          scanf("%d", &m);

          // Priority queue
          if(queue_type == 2) {
            printf("\n>Priority? \n");
            scanf("%d", &p);
            p_enqueue(q, m, p);
            continue;
          }

          // Circular queue
          if(queue_type == 3) {
            c_enqueue(q, m);
            continue;
          }

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
        display_queue(q, queue_type);
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
        reverse(q, queue_type);
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
