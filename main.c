#include "project_header.h"
int main(int argc, char *argv[])
{
    /* Clear the screen on execution */
    system("clear"); 

    int create_databae_flag = 0;

    mainNode *head[27] = {NULL}; //Database head array of pointers

    /* Validate the number of command-line arguments */
    if(argc < 2)
    {
	printf("\n" ANSI_COLOR_RED "[ERROR] Please enter the valid number of arguments.\n[USAGE] ./a.out FILE1.txt FILE2.txt..\n\n" ANSI_COLOR_RESET);
	printf("Process Terminated......\n");
	return 0;
    }

    /* Head pointer for the file list */
    flist *f_head = NULL;

    /* Validate the files and populate the file list */
    file_validate(argv, &f_head);

    /* Check if the file list is empty */
    if(f_head == NULL)
    {
	printf(ANSI_COLOR_YELLOW "[WARNING] No valid files were added to the list.\n" ANSI_COLOR_RESET);
    }
    else
    {
	printf(ANSI_COLOR_GREEN "[SUCCESS] Files have been validated and added to the list.\n" ANSI_COLOR_RESET);
    }

    /* Display the operation menu */
    int option ;
    char choice;
    do {
	displayMenu(); // Assuming displayMenu function displays the menu

	printf(ANSI_COLOR_MAGENTA"\nEnter your choice (1-5) -> " ANSI_COLOR_RESET);
	scanf("%d", &option);

	switch (option) {
	    case 1:
		if(create_databae_flag == 0)
		{
		    create_database(f_head,head);
		    create_databae_flag = 1;
		}
		else
		{
		    printf(ANSI_COLOR_RED"\n[ERROR] Database already created...\n");
		}
		break;
	    case 2:
		display_database(head);
		printf(ANSI_COLOR_GREEN "Database loaded succcessfully...\n");
		break;
	    case 3:
		if(update_database(head, &f_head) == SUCCESS)
		{
			printf(ANSI_COLOR_GREEN"[SUCCESS] Data updated successfully\n");
		}
		else
		{
			printf("FAILURE\n");
		}
		break;
	    case 4:
		char sWord[WORD_SIZE];
		printf(ANSI_COLOR_MAGENTA"\nEnter word to search: ");
		scanf("%s",sWord);
		search_word(head[tolower(sWord[0] % 97)],sWord);
		break;
	    case 5:
		save_database(head);
		break;
	    case 6:
		system("clear");
		printf("Exiting...\n");
		return 0;  // Exit the program
	    default:
		printf(ANSI_COLOR_RED"[ERROR] Invalid option\n");
		break;
	}

	printf(ANSI_COLOR_RESET); // Reset color after printing the message

	// Ask the user if they want to continue
	printf("\nDo you want to continue? (y/n): ");
	scanf(" %c", &choice);
	system("clear");

    } while (choice == 'y' || choice == 'Y');

    printf("Exiting...\n");
    return 0;
}
