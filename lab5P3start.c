/* Lab 5 P3: starter code to complete*/
#include <stdio.h>
#include <string.h>

int main()
{
    char input[256] = "";
    int letterCount[26] = {0}; // Array to store the count of each letter initialized to zeros

    printf("Enter text strings (press Enter on an empty line to exit):\n");

    while (1)
    {
        fgets(input, sizeof(input), stdin); // get the input from the user via keyboard

        // Check for an empty line to exit the loop
        if (strlen(input) == 1 && input[0] == '\n')
        {
            break;
        }
        // Your Code should be implemented here
        // Iterate through the characters in the input
        // Check if the character is a letter (A-Z or a-z)
        // Increment the corresponding count in the array

        for(int i=0; i<256; i++)
        {
            if ((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z')) 
            {
                for(int j=65; j<=90; j++)
                {
                    if(input[i] == j || input[i]== (j+32))
                    {
                        //printf("\nThis would incriment %c, when j is %d", input[i], j);
                        letterCount[j-65] += 1;
                    }
                }
            
            }

            //printf("\n\n");

        }       
    }

    printf("\n\n");

    for(int i=0; i<26;i++)
    {
        printf("%c: %--3d ", (65+i), letterCount[i]);
    }
    // More of your code here to
    // Display the letter counts

    return 0;
}