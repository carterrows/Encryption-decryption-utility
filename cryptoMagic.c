// Mini project #1
// Encrypter and decrypter
// Made by Carter Rows and Chigozie Eronini

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char import[125];
    char mode[5];
    char e[5] = "-E";
    char d[5] = "-D";

    FILE* file_handle;
    
    // user does not enter command
    // output is a ".crp" file
    if(argc == 2)
    {
        char encrypt[1000];
        
        file_handle = fopen(argv[1], "r+");

        // if program cannot find file
        if(file_handle == NULL)
        {
            perror("Error opening file\n\n");
            return 0;
        }
        
        while(fgets(import, sizeof(import), file_handle))
        {
            strncat(encrypt, import, sizeof(import));
        }

        int i = 0;
        while(encrypt[i] != '\0')
        {
            encrypt[i] -= 16;

            if(encrypt[i] < 32)
            {
                encrypt[i] += 112;
            }

            i++;
        }

        for(int j = 0; encrypt[j] != '\0'; j++)
        {
            printf("%X", encrypt[j]);
        }

        /*
        i = 0;
        while(encrypt[i] != '\0')
        {
             fprintf(file_handle, "%X", encrypt[i]);
        }
        */
        fclose(file_handle);
    }
    
    // user inputs -E
    // output is a ".crp" file
    else if(argc == 3 && !strcmp(argv[1], e))
    {
        char encrypt[1000];
        
        file_handle = fopen(argv[2], "r+");

        if(file_handle == NULL)
        {
            perror("Error opening file\n\n");
        }
        else
        {
            if(fgets(import, sizeof(import), file_handle) != NULL)
            {
                puts(import);
            }
        }

        fclose(file_handle);
    }

    // user inputs -D
    // output is a ".txt" file
    else if(argc == 3 && !strcmp(argv[1], d))
    {
        strcpy(mode, argv[1]);

        printf("%s\n\n", mode);
    }

    // incorrect command
    else
    {
        printf("\nPlease enter a valid command.\n\n");
    }

    return 0;
}