#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a stack structure
struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

// Function to initialize a stack
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(struct Stack* stack, int item) {
    stack->array[++stack->top] = item;
}

// Function to pop an element from the stack
int pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '$'; // Placeholder for empty stack
}

// Function to return the top element of the stack without popping
int peek(struct Stack* stack) {
    return stack->array[stack->top];
}

// Function to check if a character is an operand
int isOperand(char ch) {
    return (ch >= '0' && ch <= '9');
}

// Function to get the precedence of an operator
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
    }
    return -1;
}

// Function to convert infix expression to postfix and evaluate
int infixToPostfixAndEvaluate(char* infix) {
    struct Stack* stack = createStack(strlen(infix));
    int i, j;
    for (i = 0, j = -1; infix[i]; ++i) {
        if (isOperand(infix[i]))
            infix[++j] = infix[i];
        else if (infix[i] == '(')
            push(stack, infix[i]);
        else if (infix[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(')
                infix[++j] = pop(stack);
            pop(stack); // Remove '(' from the stack
        } else {
            while (!isEmpty(stack) && precedence(infix[i]) <= precedence(peek(stack)))
                infix[++j] = pop(stack);
            push(stack, infix[i]);
        }
    }

    while (!isEmpty(stack))
        infix[++j] = pop(stack);

    infix[++j] = '\0';

    // Evaluate the postfix expression
    struct Stack* evalStack = createStack(strlen(infix));
    for (i = 0; infix[i]; ++i) {
        if (isOperand(infix[i]))
            push(evalStack, infix[i] - '0');
        else {
            int operand2 = pop(evalStack);
            int operand1 = pop(evalStack);
            switch (infix[i]) {
                case '+':
                    push(evalStack, operand1 + operand2);
                    break;
                case '-':
                    push(evalStack, operand1 - operand2);
                    break;
                case '*':
                    push(evalStack, operand1 * operand2);
                    break;
                case '/':
                    push(evalStack, operand1 / operand2);
                    break;
            }
        }
    }

    return pop(evalStack);
}

// Driver program
int main() {
    char infix[100];
    printf("Enter infix expression: ");
    scanf("%s", infix);

    int result = infixToPostfixAndEvaluate(infix);
    printf("Postfix expression: %s\n", infix);
    printf("Result after evaluation: %d\n", result);

    return 0;
}
