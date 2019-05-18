#include "../include/queue.h"
#include <stddef.h>  // macro : NULL(0)
#include <stdint.h>  // type  : int8_t
#include <stdbool.h> // type  : bool
#include <assert.h>  // macro : assert()
#define swap(X,Y) { __typeof__(X) _T = X; X = Y; Y = _T; }

// Utility function
int8_t parent(int8_t i) {return (i&1)?(i-1)>>1:(i-2)>>1;}
int8_t left  (int8_t i) {return (i<<1) + 1;}
int8_t right (int8_t i) {return (i<<1) + 2;}

static void heapifyUp  (struct queue_t * q, int8_t i);
static void heapifyDown(struct queue_t * q, int8_t i);

bool empty(struct queue_t * q) {
	assert(q != NULL);
	return q->size == 0;
}

bool full(struct queue_t * q) {
	assert(q != NULL);
	return q->size == MAX_QUEUE_SIZE;
}

void enqueue(struct queue_t * q, struct pcb_t * proc) {
	assert(q != NULL && proc != NULL);
	// If queue is full, stop program
	if(full(q)) return;
	// 1. Insert new process at end of queue
	q->proc[q->size] = proc;
	q->size = q->size + 1;
	// 2. Heapify up new process in queue
	heapifyUp(q, q->size - 1);
}

struct pcb_t * dequeue(struct queue_t * q) {
	assert(q != NULL);
	// If queue is empty, stop program
	if(empty(q)) return NULL;
	// 1 Save process with highest priority(HP)
	struct pcb_t * proc = q->proc[0];
	// 2 Remove HP process from queue
	q->proc[0] = q->proc[q->size - 1];
	q->size = q->size - 1;
	// 3 Heapify down first process in queue
	heapifyDown(q, 0);

	return proc;
}

static void heapifyUp  (struct queue_t * q, int8_t i) {
	assert(q != NULL && i >= 0);

	int8_t p = parent(i);

	if(p >= 0 && q->proc[i]->priority > q->proc[p]->priority) {
		swap(q->proc[i], q->proc[p]); // parent is smaller
		heapifyUp(q, p); 			  // continue
	}
}
static void heapifyDown(struct queue_t * q, int8_t i) {
	int8_t l = left(i), r = right(i), biggest = i;

	if(l < q->size && q->proc[l]->priority > q->proc[biggest]->priority)
		biggest = l;	// left child priority is bigger
	if(r < q->size && q->proc[r]->priority > q->proc[biggest]->priority)
		biggest = r;	// right child priority is bigger

	if(biggest != i) {
		swap(q->proc[i], q->proc[biggest]); 
		heapifyDown(q, biggest); // continue
	}
}
