#include "project_header.h"
extern char *fname;

int insert_at_last(mainNode **head, char *word)
{
    /* Create a newNode type */
    mainNode *newNode = malloc(sizeof(mainNode));
    if(newNode == NULL)
    {
	printf("[ERROR] Failed to allocate the memory.");
	return FAILURE;
    }

    /* Update the values */
    newNode -> fcount = 1;
    strcpy(newNode->word, word);
    newNode -> slink = NULL;
    newNode -> mlink = NULL;

    update_subNode(&newNode);

    if(*head == NULL)
    {
	*head = newNode;
	return SUCCESS;
    }
    mainNode *temp = *head;
    while(temp -> mlink)
    {
	temp = temp -> mlink;
    }
    temp -> mlink = newNode;
    return SUCCESS;
}

int update_subNode(mainNode **head)
{
    /* Create the node */
    subNode *subNewNode = malloc(sizeof(subNode));

    if(subNewNode == NULL)
    {
	return FAILURE;
    }
    subNewNode -> wcount = 1;
    strcpy(subNewNode -> file_name, fname);
    subNewNode -> slink = NULL;

    (*head) -> slink = subNewNode;

    return SUCCESS;
}
