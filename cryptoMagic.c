// Mini project #1 - ENGG*1410
// Encrypt and decrypt tool

#include <stdio.h>
#include <string.h>

// 3 functions declared for the program
void stripExtension(char *fname);
int encryptionScheme(char a);
int decryptionScheme(char x, char y);

// argc is # of arguments in command line
// argv is the specific string
int main(int argc, char *argv[])
{
    // for reading the file
    char ch, ch2;

    // declare two file pointers for handling input and output files
    FILE *fp1, *fp2;

    // user does not input a command
    // assume encryption
    // output is a .crp file
    if(argc == 2)
    {
        // open file in read mode
        // check if the file actually exists in directory
        fp1 = fopen(argv[1], "r");
        if(fp1 == NULL)
        {
            perror("Please enter a valid file name.\n\n");
            return 0;
        }

        // print contents of input file
        printf("\nThe content of '%s' is:\n\n", argv[1]);
        while(ch != EOF)
        {
            ch = fgetc(fp1);
            printf("%c", ch);
        }
        fclose(fp1);

        printf("\n\n");

        // declare string "newFile" with .crp extension
        char newFile[50];
        strcpy(newFile, argv[1]);
        stripExtension(newFile);
        strncat(newFile, ".crp", 4);

        // print new file name
        printf("New encrypted file is: '%s'\n\n", newFile);

        // create the new file in write mode
        fp2 = fopen(newFile, "w");
        if(fp2 == NULL)
        {
            perror("Error creating encrypted file.\n\n");
            fclose(fp1);
            fclose(fp2);
            return 0;
        }

        fp1 = fopen(argv[1], "r");

        while(1)
        {
            // get character from input file
            ch = fgetc(fp1);
            
            // check for end of file
            if(ch == EOF)
            {
                break;
            }
            
            // declare ascii for printing onto new file
            // encrypting the char value after
            int ascii = encryptionScheme(ch);
            
            // if ch = 10, print new line in the file
            if(ascii == 10)
            {
                fprintf(fp2, "\n");
            }
            
            // if ch = 9 print "TT" sequence
            else if(ascii == 9)
            {
                fprintf(fp2, "TT");
            }
            
            // else just print the encrypted encrypted character in Hexadecimal form
            else
            {
                fprintf(fp2, "%X", ascii);
            }
        }
    }

    // user inputs -E, encrypt file
    // output is a .crp file
    else if(argc == 3 && strcmp(argv[1], "-E") == 0)
    {
        // open file in read mode
        // check if the file actually exists in directory
        fp1 = fopen(argv[2], "r");
        if(fp1 == NULL)
        {
            perror("Please enter a valid file name.\n\n");
            return 0;
        }

        // print contents of input file
        printf("\nThe content of '%s' is:\n\n", argv[2]);
        while(ch != EOF)
        {
            ch = fgetc(fp1);
            printf("%c", ch);
        }
        fclose(fp1);
        
        printf("\n\n");
        
        // declare string "newFile" with .crp extension
        char newFile[50];
        strcpy(newFile, argv[2]);
        stripExtension(newFile);
        strncat(newFile, ".crp", 4);

        // print new file name
        printf("New encrypted file is: '%s'\n\n", newFile);

        // create the new file in write mode
        fp2 = fopen(newFile, "w");
        if(fp2 == NULL)
        {
            perror("Error creating encrypted file.\n\n");
            fclose(fp1);
            fclose(fp2);
            return 0;
        }

        fp1 = fopen(argv[2], "r");
        
        // same process as above
        while(1)
        {
            ch = fgetc(fp1);
            if(ch == EOF)
            {
                break;
            }
            
            int ascii = encryptionScheme(ch);
            
            if(ascii == 10)
            {
                fprintf(fp2, "\n");
            }
            else if(ascii == 9)
            {
                fprintf(fp2, "TT");
            }
            else
            {
                fprintf(fp2, "%X", ascii);
            }
        }
    }

    // user inputs -D, decrypt file
    // output is a .txt file
    else if(argc == 3 && strcmp(argv[1], "-D") == 0)
    {
        // open file in read mode
        // check if the file actually exists in directory
        fp1 = fopen(argv[2], "r");
        if(fp1 == NULL)
        {
            perror("Please enter a valid file name.\n\n");
            return 0;
        }

        // print contents of input file
        printf("\nThe content of '%s' is:\n\n", argv[2]);
        while(ch != EOF)
        {
            ch = fgetc(fp1);
            printf("%c", ch);
        }
        fclose(fp1);
        
        printf("\n\n");
        
        // declare string "newFile" with .crp extension
        char newFile[50];
        strcpy(newFile, argv[2]);
        stripExtension(newFile);
        strncat(newFile, ".txt", 4);

        // print new file name
        printf("New decrypted file is: '%s'\n\n", newFile);

        // create the new file in write mode
        fp2 = fopen(newFile, "w");
        if(fp2 == NULL)
        {
            perror("Error creating encrypted file.\n\n");
            fclose(fp1);
            fclose(fp2);
            return 0;
        }

        fp1 = fopen(argv[2], "r");
        
        while(1)
        {
            // get first character from encrypted file
            ch = fgetc(fp1);
            
            // if character 1 is not a new line
            if(ch != '\n')
            {
                // get the second character of the 2 digit hex sequence
                ch2 = fgetc(fp1);

                if(ch == EOF)
                {
                    break;
                }

                // if the sequence is "TT" print a tab in the new file
                if(ch == 'T' && ch2 == 'T')
                {
                    fprintf(fp2, "%c", 9);
                }
                
                // otherwise perform decryption scheme on the 2 character sequence
                else
                {
                    int ascii = decryptionScheme(ch, ch2);
                    
                    // print to new file the decrypted character
                    fprintf(fp2, "%c", ascii);
                }
            }
            
            // print a new line if character 1 is \n
            else if(ch == '\n')
            {
                fprintf(fp2, "\n");
            }
        }
    }

    // if user does not input the correct command line arguments
    else
    {
        printf("Please enter a valid command.\n\n");
    }

    // close both file pointers
    fclose(fp1);
    fclose(fp2);
    
    // we are done!
    return 0;
}

// function for encrypting each character
int encryptionScheme(char a)
{
    // declare a temp int to hold the ascii value of the input character
    int temp = a;
    
    // do not encrypt if the character's ascii value is 10 or 13
    if(temp != 10 && temp != 13)
    {
        // perform the encryption scheme
        temp -= 16;

        if(temp < 32)
        {
            temp = (temp - 32) + 144;
        }
    }
    
    return temp;
}

// function to remove extension from file
void stripExtension(char *fname)
{
    char *end = fname + strlen(fname);

    while (end > fname && *end != '.')
    {
        --end;
    }

    if (end > fname)
    {
        *end = '\0';
    }
}

// function to decrypt a 2 character sequence
int decryptionScheme(char x, char y)
{
    // declare the int that will be returned
    int finalVal = 0;
    
    // declare 2 temp ints
    int temp1, temp2;
    temp1 = x;
    temp2 = y;

    // first add the face value of the first character
    // first character in the hex sequence will ALWAYS be a number
    finalVal += (temp1 - 48)*16;
    
    // now depending on second character value:
    switch(temp2)
    {
        // 16 different cases for each possible second character (0, 1, 2, 3, ... F)
        // add the associated face value to "finalVal"
        case 48:
            break;

        case 49:
            finalVal += 1;
            break;

        case 50:
            finalVal += 2;
            break;

        case 51:
            finalVal += 3;
            break;

        case 52:
            finalVal += 4;
            break;

        case 53:
            finalVal += 5;
            break;

        case 54:
            finalVal += 6;
            break;

        case 55:
            finalVal += 7;
            break;

        case 56:
            finalVal += 8;
            break;

        case 57:
            finalVal += 9;
            break;

        case 65:
            finalVal += 10;
            break;

        case 66:
            finalVal += 11;
            break;

        case 67:
            finalVal += 12;
            break;

        case 68:
            finalVal += 13;
            break;

        case 69:
            finalVal += 14;
            break;

        case 70:
            finalVal += 15;
            break;
    }

    // reverse order of the encryption scheme
    finalVal += 16;

    if(finalVal > 127)
    {
        finalVal = (finalVal - 144) + 32;
    }

    // return the finalVal as an int, with proper ascii value
    return finalVal;
}
