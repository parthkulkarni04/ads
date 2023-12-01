#include <stdio.h>
#include <stdlib.h>

// Structure for the stack
struct Stack {
    int capacity;
    int top;
    int *array;
};

// Function to create a stack with a given capacity
struct Stack *createStack(int capacity) {
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Function to check if the stack is full
int isFull(struct Stack *stack) {
    return stack->top == stack->capacity - 1;
}

// Function to check if the stack is empty
int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(struct Stack *stack, int item) {
    if (isFull(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->array[++stack->top] = item;
}

// Function to pop an element from the stack
int pop(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack->array[stack->top--];
}

// Function to calculate the factorial using a stack
int factorial(int n) {
    struct Stack *stack = createStack(n);
    push(stack, 1);

    int result = 1;
    while (!isEmpty(stack)) {
        int top = pop(stack);
        result *= top;
        if (top > 1) {
            push(stack, top - 1);
        }
    }

    free(stack->array);
    free(stack);

    return result;
}
// #include<stdio.h>  
// int main()    
// {    
//  int i,fact=1,number;    
//  printf("Enter a number: ");    
//   scanf("%d",&number);    
//     for(i=1;i<=number;i++){    
//       fact=fact*i;    
//   }    
//   printf("Factorial of %d is: %d",number,fact);    
// return 0;  
// } 

// Function to generate Fibonacci series using a stack
void fibonacci(int n) {
    struct Stack *stack = createStack(n);

    int a = 0, b = 1;
    push(stack, a);
    push(stack, b);

    printf("Fibonacci Series:\n%d\n%d\n", a, b);

    for (int i = 2; i < n; ++i) {
        int sum = a + b;
        push(stack, sum);
        printf("%d\n", sum);

        a = b;
        b = sum;
    }

    free(stack->array);
    free(stack);
}

int main() {
    int num;

    // Factorial
    printf("Enter a number to calculate factorial: ");
    scanf("%d", &num);
    printf("Factorial of %d is %d\n", num, factorial(num));

    // Fibonacci Series
    printf("\nEnter the number of terms for Fibonacci series: ");
    scanf("%d", &num);
    fibonacci(num);

    return 0;
}
