#include "project_header.h"
/* 
   Validate file existence and content.
   Displays success or error messages.
 */
void file_validate(char *argv[], flist **head)
{
    printf(ANSI_COLOR_CYAN "-------------------------------------------------\n");
    printf("\t        UPLOADING FILES\n");
    printf(ANSI_COLOR_CYAN "-------------------------------------------------\n");
    int i = 1, ret_value, ext_ret_value;

    while(argv[i] != NULL)
    {
	ret_value = checkFileEmpty(argv[i]);

	ext_ret_value = checkFileExtension(argv[i]);

	if(ext_ret_value == SUCCESS)
	{

	    if(ret_value == FILE_NOT_AVAIL)
	    {
		printf(ANSI_COLOR_RED "\nERROR: File %s is not available.\n",argv[i]);
		printf(ANSI_COLOR_RED "Unable to add to the list.\n");
		i++;
		continue;
	    }
	    else if(ret_value == FILE_EMPTY)
	    {
		printf(ANSI_COLOR_RED "\n[ERROR] File %s is empty.\n",argv[i]);
		printf(ANSI_COLOR_RED "Unable to add to the list.\n");
		i++;
		continue;
	    }
	    else
	    {
		ret_value = createFileList(head,argv[i]);
		if(ret_value == SUCCESS)
		{
		    printf(ANSI_COLOR_GREEN "[SUCCESS] Added file '%s' to the list\n", argv[i]);

		    //printFileList(*head);
		}
		else if(ret_value == REPITATION)
		{
		    printf(ANSI_COLOR_RED "\n[ERROR] File '%s' is already in the list\n", argv[i]);
		}
		else
		{
		    printf(ANSI_COLOR_RED "\n[ERROR] Unable to add file '%s' to the list\n", argv[i]);
		}
	    }
	    i++;
	    continue;
	}
	else
	{
	    printf(ANSI_COLOR_RED"[ERROR] Unable to add file '%s' to the list ('.txt' missing)\n",argv[i]);
	}
	i++;
    }
}

/* 
   Check if file exists and if it's empty.
   Returns FILE_NOT_AVAIL or FILE_EMPTY.
 */

int checkFileEmpty(char *fileName)
{
    //check existances
    FILE *fptr = fopen(fileName, "r");
    if(fptr == NULL)
    {
	return FILE_NOT_AVAIL;  
    }

    //check is empty
    else
    {
	fseek(fptr, 0, SEEK_END);
	if(ftell(fptr) == 0)
	{
	    return FILE_EMPTY;
	}
    }
}

/* 
   Create a file list and insert a file.
   Returns SUCCESS or REPITATION for duplicate.
 */

int createFileList(flist **f_head, char *fileName)
{
    /* Create the node */
    flist *newNode = malloc(sizeof(flist));

    /* Validate the nodr */
    if(newNode == NULL)
    {
	printf(ANSI_COLOR_RED "[ERROR] Failed to allocate the memory\n");
	return FAILURE;
    }

    /* Update the value */
    strncpy(newNode -> file_name, fileName, (FNAME_SIZE - 1));          // copy the file name to node
    newNode -> file_name[FNAME_SIZE - 1] = '\0';                        // Insert the null character
    newNode -> link = NULL;

    /* Insertion if list is empty */
    if(*f_head == NULL)                                               
    {
	*f_head = newNode;
	return SUCCESS;
    }

    /* Insertion if list is nonempty */
    flist *temp = *f_head;
    while(temp -> link != NULL)
    {
	if(strcmp(temp -> file_name, fileName) == 0)                       // Check duplicate files
	{
	    return REPITATION;
	}
	temp = temp -> link;
    }
    temp -> link = newNode;
    return SUCCESS;
}

/* Check .txt extension */
int checkFileExtension(char *fileName)
{
    if(strstr(fileName, ".txt") != NULL)
    {
	return SUCCESS;
    }
    else
    {
	return FAILURE;
    }
}
