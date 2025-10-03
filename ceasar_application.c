#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 500

// Function to encrypt/decrypt a single character
char cipher_char(char c, int key, int decrypt) {
    int shift = key;
    if (decrypt) {
        // For decryption, the effective key is 26 - key
        shift = (26 - key) % 26; 
    }

    if (islower(c)) {
        // Formula: (c - 'a' + shift) % 26 + 'a'
        return (char)(((c - 'a' + shift) % 26) + 'a');
    } else if (isupper(c)) {
        // Formula: (c - 'A' + shift) % 26 + 'A'
        return (char)(((c - 'A' + shift) % 26) + 'A');
    } else {
        // Return other characters (spaces, punctuation) unchanged
        return c;
    }
}

// Function to process and print the entire string for a given key
void process_line(const char *input_arr, int key) {
    char output_arr[MAX_LENGTH];
    int len = strlen(input_arr);
    
    // Copy the input to the output buffer
    strncpy(output_arr, input_arr, MAX_LENGTH);
    output_arr[MAX_LENGTH - 1] = '\0'; // Ensure null termination

    // Remove the newline character if it exists
    if (len > 0 && output_arr[len - 1] == '\n') {
        output_arr[len - 1] = '\0';
        len--;
    }
    
    // Apply the decryption to each character
    for (int i = 0; i < len; i++) {
        // Use 'decrypt=1' to treat the key as a shift *backwards*
        output_arr[i] = cipher_char(output_arr[i], key, 1); 
    }

    // Print the result
    printf("Key %2d: %s\n", key, output_arr);
}

int main() {
    char arr[MAX_LENGTH];

    printf("Enter text to decrypt (Ctrl+D to end input):\n");
    // Read the input line by line until EOF
    while (fgets(arr, MAX_LENGTH, stdin) != NULL) {
        printf("\n--- Decrypting with all 26 keys ---\n");
        // Iterate through all 26 possible keys (0 to 25)
        for (int i = 0; i <= 25; i++) {
            process_line(arr, i);
        }
    }
    
    return 0;
}