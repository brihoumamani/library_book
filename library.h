
#ifndef library_h
#define library_h

#include <stdio.h>

#include <stdbool.h>

#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 50
#define MAX_NAME_LENGTH 50
#define MAX_STACK_SIZE 100
#define MAX_QUEUE_SIZE 100

// Book Structure
typedef struct {
    int book_id;
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    bool is_available;
} Book;

// User Structure
typedef struct {
    int user_id;
    char name[MAX_NAME_LENGTH];
    int requested_book_id;
} User;

// Stack Structure for Recently Returned Books
typedef struct {
    Book items[MAX_STACK_SIZE];
    int top;
} ReturnedBooksStack;

// Queue Structure for Borrow Requests
typedef struct {
    User items[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int size;
} BorrowRequestQueue;

// Stack Operation Prototypes
void initStack();
void pushToStack();
Book popFromStack();
bool isStackEmpty();
bool isStackFull();

// Queue Operation Prototypes
void initQueue();
void enqueue();
User dequeue();
bool isQueueEmpty();
bool isQueueFull();

// Library Management Function Prototypes
void addBook();
void borrowBook();
void returnBook();
void processRequests();
void displayStack();
void displayQueue();
void searchBook();

#endif // LIBRARY_H
