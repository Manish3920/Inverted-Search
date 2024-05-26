#include "project_header.h"

int search_word(mainNode *head, char *word)
{
    /* Check if the main list is empty */
    if(head == NULL)
    {
	printf(ANSI_COLOR_RED"[ERROR] Search not possible, list is empty.\n");
	return FAILURE;
    }

    /* Traverse the main list */
    while(head)
    {
	if(!strcmp(head->word, word))
	{
	    system("clear");
	    printf(ANSI_COLOR_GREEN"----------------------------------------------\n"ANSI_COLOR_RESET);
	    printf(ANSI_COLOR_GREEN"               RESULT TERMINAL\n");
	    printf(ANSI_COLOR_GREEN"----------------------------------------------\n"ANSI_COLOR_RESET);
	    printf("SEARCH TERM:         '%s'\n", head->word);
	    printf("FILE COUNT:           %d\n", head->fcount);

	    /* Traverse the subnode */
	    subNode *sTemp = head->slink;

	    while(sTemp)
	    {
		printf("FILE NAME:            %s\n", sTemp->file_name);
		printf("WORD COUNT:           %d\n", sTemp->wcount);
		sTemp = sTemp->slink;
	    }

	    printf(ANSI_COLOR_GREEN"----------------------------------------------\n"ANSI_COLOR_RESET);
	    printf(ANSI_COLOR_GREEN"Search successful...\n");
	    return SUCCESS;
	}
	head = head->mlink;
    }
    printf(ANSI_COLOR_RED"\n[ERROR] Search failed. The word '%s' was not found.\n", word);
    return FAILURE;
}
