#include <stdio.h>

// Function to perform bit stuffing on a data stream
void bitStuffing(unsigned char* data, int* length) {
    int i, count = 0;

    for (i = 0; i < *length; i++) {
        if (data[i] == 1) {
            count++;
        } else {
            count = 0;
        }

        // If five consecutive 1s are encountered, insert an extra 0
        if (count == 5) {
            // Shift the remaining bits to the right
            int j;
            for (j = *length - 1; j > i; j--) {
                data[j + 1] = data[j];
            }

            // Insert the extra 0
            data[i + 1] = 0;
            count = 0;  // Reset the count
            (*length)++;  // Increase the length of the data stream
        }
    }
}

// Function to perform bit unstuffing on a received data stream
void bitUnstuffing(unsigned char* data, int* length) {
    int i, count = 0;

    for (i = 0; i < *length; i++) {
        if (data[i] == 1) {
            count++;
        } else {
            count = 0;
        }

        // If five consecutive 1s followed by a 0 are encountered, remove the extra 0
        if (count == 5 && i < (*length - 1) && data[i + 1] == 0) {
            // Shift the remaining bits to the left
            int j;
            for (j = i + 1; j < *length - 1; j++) {
                data[j] = data[j + 1];
            }

            // Decrease the length of the data stream
            (*length)--;
        }
    }
}

int main() {
    int numBits;

    printf("Enter the number of bits in the data stream: ");
    scanf("%d", &numBits);

    unsigned char data[numBits];
    printf("Enter the data stream (0s and 1s): ");
    for (int i = 0; i < numBits; i++) {
        scanf("%hhu", &data[i]);
    }

    printf("Original data: ");
    for (int i = 0; i < numBits; i++) {
        printf("%d ", data[i]);
    }

    bitStuffing(data, &numBits);

    printf("\nStuffed data: ");
    for (int i = 0; i < numBits; i++) {
        printf("%d ", data[i]);
    }

    bitUnstuffing(data, &numBits);

    printf("\nUnstuffed data: ");
    for (int i = 0; i < numBits; i++) {
        printf("%d ", data[i]);
    }

    return 0;
}