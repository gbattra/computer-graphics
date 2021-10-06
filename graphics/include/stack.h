/**
 * Greg Attra
 * 10/04/2021
 * 
 * Definition of a stack and stack API.
 * Inspired by http://jiten-thakkar.com/posts/writing-generic-stack-in-c
 */

typedef struct
{
    int capacity;
    int item_size;
    int top;
    void *items;
} Stack;

/**
 * Create a new stack.
 * 
 * @param capacity the max number of items in the stack
 * @param item_size the size of each item in the stack
 * 
 * @return newly initialized stack pointer
 */
Stack *stack_create(int capacity, int item_size);

/**
 * Push an item onto the stack.
 * 
 * @param stack the stack to push to
 * @param item the item to push
 * 
 * @return void
 */
void stack_push(Stack *stack, void *item);

/**
 * Pop an item off the stack.
 * 
 * @param stack the stack to pop
 * @param target the memory to pop to
 * 
 * @return void
 */
void stack_pop(Stack *stack, void *target);

/**
 * Utility function to return size of the stack.
 * 
 * @param stack the stack to size
 * 
 * @return the size of the stack
 */
int stack_size(Stack *stack);

/**
 * Free all internal data and the stack itself.
 * 
 * @param stack the stack to free
 * 
 * @return void
 */
void stack_free(Stack *stack);
