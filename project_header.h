/**
 * project_headers.h
 * Contains all necessary header files, macros, function prototypes,
 * structures, and enums for the project.
 */

#ifndef PROJECT_HEADER_H
#define PROJECT_HEADERS_H

/* Header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <time.h>

/* Macros for colors */
#define ANSI_COLOR_RESET "\033[0m"
#define ANSI_COLOR_RED "\033[1;31m"
#define ANSI_COLOR_GREEN "\033[1;32m"
#define ANSI_COLOR_CYAN "\033[1;36m"
#define ANSI_COLOR_YELLOW "\033[1;33m"
#define ANSI_COLOR_WHITE "\033[1;37m"
#define ANSI_COLOR_MAGENTA "\033[1;35m"

/* Macros return values */
#define FAILURE        -1
#define SUCCESS         0
#define FNAME_SIZE      256
#define WORD_SIZE       256
#define CHAR_NUM        28
#define FILE_EMPTY     -2
#define FILE_NOT_AVAIL -3
#define REPITATION     -4

extern char global_fileName[FILENAME_MAX];

/* Structure for file list */

typedef struct node
{
    char file_name[FNAME_SIZE];
    struct node *link;

}flist;

/* Structure for main node */
typedef struct _mainNode
{
    int fcount;
    char word[WORD_SIZE];
    struct _subNode *slink;
    struct _mainNode *mlink;
    
}mainNode;

/* Structure for sub node */
typedef struct _subNode
{
    int wcount;
    char file_name[FNAME_SIZE];
    struct _subNode *slink;
}subNode;


/* Function prototypes */

/* Function to validate the existance/content/duplicacy */
void file_validate(char *argv[], flist **head);

/* Function to check file empty */
int checkFileEmpty(char *fileName);

int checkFileExtension(char *fileName);

/* Function to create list of files */
int createFileList(flist **f_head, char *fileName);

/* Function to create the database */
void create_database(flist *fhead, mainNode *head[]);

/* Read the data from file */
mainNode * read_data_of_file(flist *fhead, mainNode *head[], char *fileName);

/* Insert the word */
int insert_at_last(mainNode **head, char *word);

/* Update the sub node */
int update_subNode(mainNode **head);

/* Update the word count */
int update_word_count(mainNode **head, char *fileName);

/* Display the database */
void display_database(mainNode *head[]);

/*Update the database */
int update_database(mainNode **head, flist **f_head);


/* Search the word in database */
int search_word(mainNode *head, char *word);

/* Save the database */
void save_database(mainNode **head);

/* Write the data in file */
void write_database(mainNode *head, FILE *databaseFile);

/* Operation menu */
void displayMenu(void);

#endif
