#include "project_header.h"

/* Global variable to store the current file name  */
char *fname;

/*
 * Function to create the database by reading data from files in the list.
 * It iterates over each file in the list and reads its data.
 */
void create_database(flist *f_head, mainNode *head[])
{
    /* Traverse through the file list */
    while(f_head)
    {   
	read_data_of_file(f_head, head, f_head->file_name);
	f_head = f_head -> link;
    }
}

/*
 * Function to read data from a given file and populate the database.
 * It reads each word from the file, checks for its presence in the database,
 * and updates the database accordingly.
 */
mainNode *read_data_of_file(flist *f_head, mainNode *head[], char *fileName)
{
    fname = fileName;

    FILE *fptr = fopen(fileName, "r");
    char wordBuffer[WORD_SIZE];
    int flag = 1;

    if(fptr == NULL)
    {
	printf("[ERROR] Failed to open %s file.\n", fileName);
	return NULL;
    }

    while(fscanf(fptr, "%s", wordBuffer) != EOF)
    {
	int flag = 1;  // Reset flag for each new word
	/* Calculate the index for the word */
	int index = tolower(wordBuffer[0]) % 97;

	/* If the index is out of range, use a default index */
	if(!(index >= 0 && index <= 25))
	{
	    index = 26;
	}

	/* Check if the word already exists in the database */
	if(head[index] != NULL)
	{
	    mainNode *temp = head[index];

	    while(temp)
	    {
		if(!strcmp(temp -> word, wordBuffer))
		{
		    update_word_count(&temp, fileName);
		    flag = 0;
		    break;
		}
		temp = temp -> mlink;
	    }
	}

	/* If the word is new, insert it into the database */
	if(flag == 1) 
	{
	    insert_at_last(&head[index], wordBuffer);
	}
    }

    printf(ANSI_COLOR_GREEN "[SUCCESS] Database created successfully for file: %s\n", fileName);

    return NULL;
}

/*
 * Function to update the word count for a given word and file.
 * It checks if the file name matches with any existing subnode.
 * If yes, it increments the word count; otherwise, it adds a new subnode.
 */
int update_word_count(mainNode **head, char *fileName)
{
    /* Traverse the subnodes to find a matching file name */
    subNode *temp = (*head)->slink, *prev = NULL;

    while(temp)
    {
	if(!strcmp(temp->file_name, fileName))
	{
	    /* Increment the word count for the file */
	    temp->wcount++;
	    return SUCCESS;
	}
	prev = temp;
	temp = temp->slink;
    }

    /* If the file name is not found, increment the file count and add a new subnode */
    (*head)->fcount++;

    /* Allocate memory for the new subnode */
    subNode *subNewNode = malloc(sizeof(subNode));

    /* Validate the memory allocation */
    if(subNewNode == NULL)
    {
	return FAILURE;
    }

    /* Initialize the new subnode with the file name and word count */
    strcpy(subNewNode->file_name, fileName);
    subNewNode->wcount = 1;
    subNewNode->slink = NULL;

    /* Establish link between the previous subnode and the new subnode */
    if(prev == NULL)
    {
	(*head)->slink = subNewNode;
    }
    else
    {
	prev->slink = subNewNode;
    }

    return SUCCESS;
}
