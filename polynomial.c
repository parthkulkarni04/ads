#include <stdio.h>
#include <stdlib.h>

// Define the structure for a term in a polynomial
struct Term {
    int coefficient;
    int exponent;
    struct Term* next;
};

// Function to create a new term for a polynomial
struct Term* createTerm(int coefficient, int exponent) {
    struct Term* newTerm = (struct Term*)malloc(sizeof(struct Term));
    newTerm->coefficient = coefficient;
    newTerm->exponent = exponent;
    newTerm->next = NULL;
    return newTerm;
}

// Function to add a term to a polynomial
void addTerm(struct Term** poly, int coefficient, int exponent) {
    struct Term* newTerm = createTerm(coefficient, exponent);

    if (*poly == NULL) {
        *poly = newTerm;
    } else {
        struct Term* temp = *poly;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newTerm;
    }
}

// Function to add two polynomials
struct Term* addPolynomials(struct Term* poly1, struct Term* poly2) {
    struct Term* result = NULL;
    while (poly1 != NULL || poly2 != NULL) {
        if (poly1 == NULL) {
            addTerm(&result, poly2->coefficient, poly2->exponent);
            poly2 = poly2->next;
        } else if (poly2 == NULL) {
            addTerm(&result, poly1->coefficient, poly1->exponent);
            poly1 = poly1->next;
        } else {
            if (poly1->exponent > poly2->exponent) {
                addTerm(&result, poly1->coefficient, poly1->exponent);
                poly1 = poly1->next;
            } else if (poly1->exponent < poly2->exponent) {
                addTerm(&result, poly2->coefficient, poly2->exponent);
                poly2 = poly2->next;
            } else {
                addTerm(&result, poly1->coefficient + poly2->coefficient, poly1->exponent);
                poly1 = poly1->next;
                poly2 = poly2->next;
            }
        }
    }
    return result;
}

// Function to display a polynomial
void displayPolynomial(struct Term* poly) {
    while (poly != NULL) {
        printf("%dx^%d ", poly->coefficient, poly->exponent);
        if (poly->next != NULL) {
            printf("+ ");
        }
        poly = poly->next;
    }
    printf("\n");
}

// Main function
int main() {
    struct Term* poly1 = NULL;
    struct Term* poly2 = NULL;
    struct Term* result = NULL;

    // Add terms to the first polynomial
    addTerm(&poly1, 3, 2);
    addTerm(&poly1, 5, 1);
    addTerm(&poly1, 7, 0);

    // Add terms to the second polynomial
    addTerm(&poly2, 2, 3);
    addTerm(&poly2, 4, 1);
    addTerm(&poly2, 1, 0);

    // Display the polynomials
    printf("Polynomial 1: ");
    displayPolynomial(poly1);

    printf("Polynomial 2: ");
    displayPolynomial(poly2);

    // Add the polynomials and display the result
    result = addPolynomials(poly1, poly2);
    printf("Sum of Polynomials: ");
    displayPolynomial(result);

    // Free the memory allocated for the linked lists
    free(poly1);
    free(poly2);
    free(result);

    return 0;
}
