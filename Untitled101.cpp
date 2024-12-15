// Complete and fixed version of the library management system.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Constants
#define MAX_TITLE_LENGTH 100  //  for the title of a book
#define MAX_AUTHOR_LENGTH 100 // for the author's name
#define MAX_NAME_LENGTH 50    // for a user's name
#define MAX_QUEUE_SIZE 50     //  of borrow requests in the queue
#define MAX_STACK_SIZE 50     // of returned books in the stack



// this is for the book in the library
typedef struct {
    int book_id;                       //  id for book
    char title[MAX_TITLE_LENGTH];      // Title 
    char author[MAX_AUTHOR_LENGTH];   
    bool is_available;                 // Availability 
} Book;

//  user making a borrow request ( the order of the user)
typedef struct {
    int user_id;                       //  id user
    char name[MAX_NAME_LENGTH];        // User's name
    int requested_book_id;             // ID of the book requested
} User;

// this is for the stack to hold returned books
typedef struct {
    Book items[MAX_STACK_SIZE];        // Array to store books
    int top;                           // Index of the top book in the stack it points exactly to the last book in the stack 
} ReturnedBooksStack;

// Represents a queue to handle borrow requests
typedef struct {
    User items[MAX_QUEUE_SIZE];        // Array to store user requests
    int front;                         // Index of the front of the queue
    int rear;                          // Index of the rear of the queue
    int size;                          // Current number of requests in the queue
} BorrowRequestQueue;

// Global Variables
Book* library = NULL;                  // Dynamic array of books
int total_books = 0;                   // Number of books in the library
ReturnedBooksStack returned_books_stack; // Stack to hold returned books
BorrowRequestQueue borrow_request_queue; // Queue to hold borrow requests

// Function Declarations
// Stack-related functions
void initStack(ReturnedBooksStack* stack); // Initialize the stack
bool isStackEmpty(ReturnedBooksStack* stack); // Check if the stack is empty
bool isStackFull(ReturnedBooksStack* stack); // Check if the stack is full
void pushToStack(ReturnedBooksStack* stack, Book book); // Push a book onto the stack

// Queue-related functions
void initQueue(BorrowRequestQueue* queue); // Initialize the queue
bool isQueueEmpty(BorrowRequestQueue* queue); // Check if the queue is empty
bool isQueueFull(BorrowRequestQueue* queue); // Check if the queue is full
void enqueue(BorrowRequestQueue* queue, User user); // Add a user request to the queue
User dequeue(BorrowRequestQueue* queue); // Remove a user request from the queue
User peekQueue(BorrowRequestQueue* queue); // Peek at the front user request

// library system functions that we need to serve the user  the option that the user have

void addBook(); // Add a new book to the library( the owner of the lib)

void borrowBook(); // Borrow a book from the library
void returnBook(); // Return a book to the library

void processRequests(); // Process pending borrow requests
// this function is part of the process of the borrow of the book

void searchBook(); 
void displayReturnedBooks(); // the recently books
void displayBorrowRequests(); //  pending requests ( all the books are pending  by dafault) 

void displayMenu(); // Display the main menu options


// Stack Functions Implementation

// Initialize the stack
void initStack(ReturnedBooksStack* stack) {
    stack->top = -1; // Set top to -1 to indicate an empty stack
}

// Check if the stack is empty
bool isStackEmpty(ReturnedBooksStack* stack) {
    return stack->top == -1;
}

// Check if the stack is full
bool isStackFull(ReturnedBooksStack* stack) {
    return stack->top == MAX_STACK_SIZE - 1;
}

// Push a book onto the stack
void pushToStack(ReturnedBooksStack* stack, Book book) {
    if (isStackFull(stack)) {
        printf("Error: Stack is full. Cannot add more books.\n");
        return;
    }
    stack->items[++stack->top] = book; // Increment top and add the book
}

// Queue Functions Implementation

// Initialize the queue
void initQueue(BorrowRequestQueue* queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
}

// Check if the queue is empty
bool isQueueEmpty(BorrowRequestQueue* queue) {
    return queue->size == 0;
}

// Check if the queue is full
bool isQueueFull(BorrowRequestQueue* queue) {
    return queue->size == MAX_QUEUE_SIZE;
}

// Add a user request to the queue
void enqueue(BorrowRequestQueue* queue, User user) {
    if (isQueueFull(queue)) {
        printf("Error: Queue is full. Cannot add more requests.\n");
        return;
    }
    queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE; // Circular increment
    queue->items[queue->rear] = user;
    queue->size++;
}

// Remove a user request from the queue
User dequeue(BorrowRequestQueue* queue) {
    User empty_user = {-1, "", -1}; // Default empty user
    if (isQueueEmpty(queue)) {
        printf("Error: Queue is empty. Cannot remove a user.\n");
        return empty_user;
    }
    User dequeued_user = queue->items[queue->front];
    queue->front = (queue->front + 1) % MAX_QUEUE_SIZE; // Circular increment
    queue->size--;
    return dequeued_user;
}

// Peek at the front user request
User peekQueue(BorrowRequestQueue* queue) {
    User empty_user = {-1, "", -1}; // Default empty user
    if (isQueueEmpty(queue)) {
        printf("Error: Queue is empty. Cannot peek.\n");
        return empty_user;
    }
    return queue->items[queue->front];
}

// Core Library Functions Implementation

// Add a new book to the library
void addBook() {
    Book* new_library = (Book*)realloc(library, (total_books + 1) * sizeof(Book)); // Resize library array
    if (!new_library) {
        printf("\n? Error: Unable to allocate memory for new book.\n");
        return;
    }
    library = new_library; // Update the library pointer

    Book new_book;

    printf("\n=============================================\n");
    printf("                ?? Add a New Book             \n");
    printf("=============================================\n");

    printf("?? Enter Book ID: ");
    scanf("%d", &new_book.book_id); // Read book ID

    getchar(); // Clear input buffer

    printf("?? Enter Book Title: ");
    fgets(new_book.title, MAX_TITLE_LENGTH, stdin); // Read book title
    new_book.title[strcspn(new_book.title, "\n")] = 0; // Remove newline character

    printf("??  Enter Author Name: ");
    fgets(new_book.author, MAX_AUTHOR_LENGTH, stdin); // Read author name
    new_book.author[strcspn(new_book.author, "\n")] = 0; // Remove newline character

    new_book.is_available = true; // Set availability to true by default

    library[total_books++] = new_book; // Add the book to the library and increment count

    printf("\n? Book \"%s\" by %s added successfully!\n", new_book.title, new_book.author);
    printf("=============================================\n");
}

// Borrow a book from the library
void borrowBook() {
    int book_id;
    printf("Enter Book ID to borrow: ");
    scanf("%d", &book_id); // Read the book ID to borrow

    for (int i = 0; i < total_books; i++) {
        if (library[i].book_id == book_id) {
            if (library[i].is_available) {
                library[i].is_available = false; // Mark the book as borrowed
                printf("Book \"%s\" borrowed successfully!\n", library[i].title);
                return;
            } else {
                User new_user;
                printf("Book is currently unavailable. Adding to borrow request queue.\n");

                printf("Enter User ID: ");
                scanf("%d", &new_user.user_id); // Read user ID

                getchar(); // Clear input buffer

                printf("Enter User Name: ");
                fgets(new_user.name, MAX_NAME_LENGTH, stdin); // Read user name
                new_user.name[strcspn(new_user.name, "\n")] = 0; // Remove newline character

                new_user.requested_book_id = book_id; // Set the requested book ID

                enqueue(&borrow_request_queue, new_user); // Add request to queue
                printf("You've been added to the borrow request queue.\n");
                return;
            }
        }
    }
    printf("Book not found in the library.\n");
}

// Return a book to the library
void returnBook() {
    int book_id;
    printf("\n=============================================\n");
    printf("             ?? Return a Book               \n");
    printf("=============================================\n");

    printf("?? Enter Book ID to return: ");
    scanf("%d", &book_id); // Read the book ID to return

    for (int i = 0; i < total_books; i++) {
        if (library[i].book_id == book_id) {
            if (!library[i].is_available) {
                library[i].is_available = true; // Mark the book as available

                pushToStack(&returned_books_stack, library[i]); // Add to returned books stack

                printf("\n? Book \"%s\" returned successfully!\n", library[i].title);

                processRequests(); // Process pending requests
                printf("=============================================\n");
                return;
            } else {
                printf("\n??  This book was already available in the library.\n");
                printf("=============================================\n");
                return;
            }
        }
    }
    printf("\n? Book not found in the library.\n");
    printf("=============================================\n");
}

// Process pending borrow requests
void processRequests() {
    while (!isQueueEmpty(&borrow_request_queue)) {
        User next_user = peekQueue(&borrow_request_queue); // Get the next user request

        for (int i = 0; i < total_books; i++) {
            if (library[i].book_id == next_user.requested_book_id && library[i].is_available) {
                dequeue(&borrow_request_queue); // Remove the request from the queue
                library[i].is_available = false; // Mark the book as borrowed
                printf("Book \"%s\" borrowed by %s (User ID: %d)\n",
                       library[i].title, next_user.name, next_user.user_id);
                break;
            }
        }
    }
}

// Search for a book by its ID
void searchBook() {
    int book_id;
    printf("Enter Book ID to search: ");
    scanf("%d", &book_id); // Read the book ID to search for

    for (int i = 0; i < total_books; i++) {
        if (library[i].book_id == book_id) {
            printf("Book Found:\n");
            printf("Title: %s\n", library[i].title);
            printf("Author: %s\n", library[i].author);
            printf("Available: %s\n", library[i].is_available ? "Yes" : "No");
            return;
        }
    }
    printf("Book not found in the library.\n");
}

// Display the recently returned books
void displayReturnedBooks() {
    if (isStackEmpty(&returned_books_stack)) {
        printf("No recently returned books.\n");
        return;
    }

    printf("Recently Returned Books:\n");
    for (int i = returned_books_stack.top; i >= 0; i--) {
        Book book = returned_books_stack.items[i];
        printf("Book ID: %d, Title: %s, Author: %s\n",
               book.book_id, book.title, book.author);
    }
}

// Display the pending borrow requests
void displayBorrowRequests() {
    if (isQueueEmpty(&borrow_request_queue)) {
        printf("No pending borrow requests.\n");
        return;
    }

    printf("Borrow Request Queue:\n");
    int count = borrow_request_queue.size;
    int index = borrow_request_queue.front;

    for (int i = 0; i < count; i++) {
        User user = borrow_request_queue.items[index];
        printf("User ID: %d, Name: %s, Requested Book ID: %d\n",
               user.user_id, user.name, user.requested_book_id);
        index = (index + 1) % MAX_QUEUE_SIZE; // Circular increment
    }
}

// Display the main menu options
void displayMenu() {
    printf("\n===========================================================\n");
    printf("        ?? Library Management System                       \n");
    printf("===========================================================\n");
    printf("1??  Add New Book\n");
    printf("2??  Borrow Book\n");
    printf("3??  Return Book\n");
    printf("4??  Search Book\n");
    printf("5??  Display Recently Returned Books\n");
    printf("6??  Display Borrow Requests\n");
    printf("7??  Exit\n");
    printf("=============================================\n");
    printf("?? Enter your choice: ");
}

// Main function
int main() {
    initStack(&returned_books_stack); // Initialize the stack for returned books
    initQueue(&borrow_request_queue); // Initialize the queue for borrow requests

    int choice;
    do {
        displayMenu(); // Show menu options
        scanf("%d", &choice); // Get the user's choice

        switch (choice) {
            case 1:
                addBook(); // Add a new book
                break;
            case 2:
                borrowBook(); // Borrow a book
                break;
            case 3:
                returnBook(); // Return a book
                break;
            case 4:
                searchBook(); // Search for a book
                break;
            case 5:
                displayReturnedBooks(); // Show recently returned books
                break;
            case 6:
                displayBorrowRequests(); // Show pending borrow requests
                break;
            case 7:
                printf("Exiting the program. Goodbye!\n");
                free(library); // Free dynamically allocated memory
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}
