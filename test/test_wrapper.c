/**
 * test_wrapper.c
 * Test wrapper for the add_one function
 */

#include <stdio.h>
#include <stdlib.h>

/* Function declaration - this will be implemented in our object file */
extern int add_one(int x);

int main(int argc, char *argv[]) {
    int input = 41;
    int expected = 42;
    int result;
    
    /* Get input value from command line if provided */
    if (argc > 1) {
        input = atoi(argv[1]);
        expected = input + 1;
    }
    
    printf("Testing add_one function...\n");
    printf("Input: %d\n", input);
    printf("Expected: %d\n", expected);
    
    /* Call the function from our object file */
    result = add_one(input);
    
    printf("Result: %d\n", result);
    
    /* Check if the result is correct */
    if (result == expected) {
        printf("Test PASSED! ✓\n");
        return 0;
    } else {
        printf("Test FAILED! ✗\n");
        return 1;
    }
}