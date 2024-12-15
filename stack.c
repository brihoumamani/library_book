#include <stdio.h>
#include "library.h"

// Initialize the stack
void initStack(ReturnedBooksStack* stack) {
    // Set top to -1 to indicate an empty stack
    stack->top = -1;
}

// Check if stack is empty
bool isStackEmpty(ReturnedBooksStack* stack) {
    // Stack is empty when top is -1
    return stack->top == -1;
}

// Check if stack is full
bool isStackFull(ReturnedBooksStack* stack) {
    // Stack is full when top is at the last index
    return stack->top == MAX_STACK_SIZE - 1;
}

// Push a book to the stack
void pushToStack(ReturnedBooksStack* stack, Book book) {
    // Check if stack is full before pushing
    if (isStackFull(stack)) {
        printf("Error: Stack is full. Cannot add more books.\n");
        return;
    }
    
    // Increment top and add the book
    stack->top++;
    stack->items[stack->top] = book;
}

// Pop a book from the stack
Book popFromStack(ReturnedBooksStack* stack) {
    // Create a dummy book to return if stack is empty
    Book empty_book = {-1, "", "", false};
    
    // Check if stack is empty
    if (isStackEmpty(stack)) {
        printf("Error: Stack is empty. Cannot pop a book.\n");
        return empty_book;
    }
    
    // Return the top book and decrement top
    Book popped_book = stack->items[stack->top];
    stack->top--;
    return popped_book;
}

// Optional: Peek at the top book without removing it
Book peekStack(ReturnedBooksStack* stack) {
    // Create a dummy book to return if stack is empty
    Book empty_book = {-1, "", "", false};
    
    // Check if stack is empty
    if (isStackEmpty(stack)) {
        printf("Error: Stack is empty. Cannot peek.\n");
        return empty_book;
    }
    
    // Return the top book without removing it
    return stack->items[stack->top];
}
