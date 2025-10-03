#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 500

/**
 * @brief Encrypts or decrypts a single alphabetic character.
 * * @param c The character to process.
 * @param key The shift value (0-25).
 * @param encrypt Flag: 1 for encryption (forward shift), 0 for decryption (backward shift).
 * @return The shifted character, or the original character if non-alphabetic.
 */
char cipher_char(char c, int key, int encrypt) {
    int shift = key % 26; // Ensure key is within 0-25
    
    // For encryption, the shift is just the key.
    // For decryption, the effective shift is 26 - key.
    if (!encrypt) {
        shift = (26 - shift) % 26; 
    }

    if (islower(c)) {
        // (c - 'a' + shift) % 26 + 'a'
        return (char)(((c - 'a' + shift) % 26) + 'a');
    } else if (isupper(c)) {
        // (c - 'A' + shift) % 26 + 'A'
        return (char)(((c - 'A' + shift) % 26) + 'A');
    } else {
        // Return other characters (spaces, punctuation, digits) unchanged
        return c;
    }
}

/**
 * @brief Encrypts an entire string and prints the result.
 * * @param input_arr The string to be encrypted.
 * @param key The encryption key (0-25).
 */
void encrypt_line(const char *input_arr, int key) {
    char output_arr[MAX_LENGTH];
    int len = strlen(input_arr);
    
    // Copy the input to the output buffer
    strncpy(output_arr, input_arr, MAX_LENGTH);
    output_arr[MAX_LENGTH - 1] = '\0';

    // Remove the newline character if it exists
    if (len > 0 && output_arr[len - 1] == '\n') {
        output_arr[len - 1] = '\0';
        len--;
    }
    
    // Apply the encryption to each character
    for (int i = 0; i < len; i++) {
        // Use 'encrypt=1' to perform a forward shift
        output_arr[i] = cipher_char(output_arr[i], key, 1); 
    }

    // Print the result
    printf("Encrypted Message: %s\n", output_arr);
}

// ----------------------------------------------------------------------

int main() {
    char arr[MAX_LENGTH];
    int key;

    // 1. Get the encryption key from the user
    printf("Enter the encryption key (an integer, e.g., 3 for C): ");
    if (scanf("%d", &key) != 1) {
        fprintf(stderr, "Invalid key entered. Exiting.\n");
        return 1;
    }
    // Consume the rest of the line, including the newline after the integer input
    while (getchar() != '\n'); 

    // 2. Get the plaintext from the user
    printf("Enter the message (plaintext) to encrypt (Ctrl+D to end input):\n");
    
    // 3. Read the input line by line and encrypt
    while (fgets(arr, MAX_LENGTH, stdin) != NULL) {
        encrypt_line(arr, key);
    }
    
    return 0;
}