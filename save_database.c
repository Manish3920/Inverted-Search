#include "project_header.h"

void save_database(mainNode **head)
{
    /* Take input from the user */
    char fileName[FNAME_SIZE];
    printf(ANSI_COLOR_MAGENTA "Please enter the file name to save the database: ");
    scanf("%s", fileName);

    /* File extension validation */
    if (strcmp(strrchr(fileName, '.'), ".txt") == 0)
    {
        /* Open the required file in write mode */
        FILE *fptr = fopen(fileName, "w");

        /* Error handling */
        if (fptr == NULL)
        {
            printf(ANSI_COLOR_RED "[ERROR] Failed to open the file\n");
            return; // Exit the function if file opening fails
        }

        /* Iterate through all head pointers */
        for (int i = 0; i < 27; i++)
        {
            /* Check if head is empty or not */
            if (head[i] != NULL)
            {
                write_database(head[i], fptr);
            }
        }

        printf(ANSI_COLOR_GREEN "[SUCCESS] Database saved...\n");
        fclose(fptr); // close the file after writing
    }
    else
    {
        printf(ANSI_COLOR_RED "\n[ERROR] Please provide '.txt' extension file\n");
    }
}

/* Function to write the data */
void write_database(mainNode *head, FILE *databaseFile)
{
    mainNode *mTemp = head;
    while (mTemp != NULL)
    {
        fprintf(databaseFile, "#%d;%d;%s;", mTemp->word[0] % 97,mTemp->fcount, mTemp->word);

        subNode *sTemp = mTemp->slink;
        while (sTemp != NULL)
        {
            fprintf(databaseFile, "%s;%d", sTemp -> file_name, sTemp -> wcount);
            sTemp = sTemp -> slink;
			if(sTemp != NULL)
			fprintf(databaseFile,"%c",';');
        }
		fprintf(databaseFile,"%c\n",'#');
        mTemp = mTemp -> mlink;
    }
}
