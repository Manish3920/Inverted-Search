#include "project_header.h"

void display_database(mainNode *head[])
{
    system("clear");
    printf("--------------------------------------------------------------------------\n");
    printf(" INDEX    WORD         FILE COUNT           FILE NAME         WORD COUNT\n");
    printf("--------------------------------------------------------------------------\n");

    for(int i = 0; i < 27; i++)
    {
	mainNode *mTemp = head[i];

	while(mTemp != NULL)
	{
	    printf("%-7d   %-10s      %-14d    ", i, mTemp->word, mTemp->fcount);

	    subNode *sTemp = mTemp->slink;

	    if (sTemp != NULL)
	    {
		printf("%-20s %d", sTemp->file_name, sTemp->wcount);
		sTemp = sTemp->slink;
	    }

	    while(sTemp != NULL)
	    {
		printf("\n                                            %-20s %d", sTemp->file_name, sTemp->wcount);
		sTemp = sTemp->slink;
	    }

	    printf("\n");
	    mTemp = mTemp->mlink;
	}
    }

    printf("--------------------------------------------------------------------------\n");
}
