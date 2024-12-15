
#include <stdio.h>
#include "library.h"

// Initialize the queue
void initQueue(BorrowRequestQueue* queue) {
    // Set front and rear to initial positions
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
}

// Check if queue is empty
bool isQueueEmpty(BorrowRequestQueue* queue) {
    return queue->size == 0;
}

// Check if queue is full
bool isQueueFull(BorrowRequestQueue* queue) {
    return queue->size == MAX_QUEUE_SIZE;
}

// Add a user to the queue (enqueue)
void enqueue(BorrowRequestQueue* queue, User user) {
    // Check if queue is full
    if (isQueueFull(queue)) {
        printf("Error: Queue is full. Cannot add more requests.\n");
        return;
    }
    
    // Move rear and add the user
    queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
    queue->items[queue->rear] = user;
    queue->size++;
}

// Remove and return the first user from the queue (dequeue)
User dequeue(BorrowRequestQueue* queue) {
    // Create a dummy user to return if queue is empty
    User empty_user = {-1, "", -1};
    
    // Check if queue is empty
    if (isQueueEmpty(queue)) {
        printf("Error: Queue is empty. Cannot remove a user.\n");
        return empty_user;
    }
    
    // Get the user at the front and move front
    User dequeued_user = queue->items[queue->front];
    queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
    queue->size--;
    
    return dequeued_user;
}

// Optional: Peek at the first user without removing
User peekQueue(BorrowRequestQueue* queue) {
    // Create a dummy user to return if queue is empty
    User empty_user = {-1, "", -1};
    
    // Check if queue is empty
    if (isQueueEmpty(queue)) {
        printf("Error: Queue is empty. Cannot peek.\n");
        return empty_user;
    }
    
    // Return the front user without removing
    return queue->items[queue->front];
}
