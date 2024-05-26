#include "project_header.h"

void check(mainNode **head, char *str, int index) {
    mainNode *temp = head[index], *prev = NULL;

    while (temp) {
        if (strcmp(str, temp -> word) == SUCCESS) {
            if (prev == NULL) {
                head[index] = temp -> mlink;
            } else {
                prev->mlink = temp -> mlink;
            }
            free(temp);
            temp = NULL;
            return; // Exit the function once the node is found and deleted
        }
        prev = temp;
        temp = temp -> mlink;
    }
}


int creat_update(mainNode **head, char *str) {
    int index = atoi(strtok((str + 1), ";"));
    int count, i, flag = 0;

    mainNode *Mnew = malloc(sizeof(mainNode));

    if (Mnew == NULL)
        return FAILURE;

    if (head[index] == NULL) {
        Mnew -> fcount = atoi(strtok(NULL, ";"));
        count = Mnew -> fcount;
        strcpy(Mnew -> word, strtok(NULL, ";"));
        Mnew -> mlink = NULL;

        for (i = 1; i <= count; i++) {
            subNode *Snew = malloc(sizeof(subNode));
            strcpy(Snew -> file_name, strtok(NULL, ";"));
            Snew -> wcount = atoi(strtok(NULL, ";"));
            Snew -> slink = NULL;

            if (i == 1) {
                Mnew->slink = Snew;
            } else {
                subNode *temp = Mnew->slink;
                while (temp->slink != NULL) {
                    temp = temp->slink;
                }
                temp->slink = Snew;
            }
            check(head, Snew -> file_name, index);
        }
        head[index] = Mnew;
    } else {
        // Handle insertion into existing main node
        // Similar logic as above, adapt it accordingly
    }

    return SUCCESS;
}

int update_database(mainNode **head, flist **f_head) {
    if (*f_head == NULL) {
        printf(ANSI_COLOR_RED"File list is empty\n");
        return FAILURE;
    }

    int i;
    char str[FNAME_SIZE];
    FILE *fptr;

    printf(ANSI_COLOR_MAGENTA"Enter the file name you stored data : ");
    scanf("%s", str);

    if (strcmp(strstr(str, "."), ".txt") == SUCCESS) {
        fptr = fopen(str, "r");
        if (fptr == NULL) {
            printf(ANSI_COLOR_RED"[ERROR] Unable to open file\n");
            return FAILURE;
        }

        while (fscanf(fptr, "%s", str) != EOF) {
            for (i = 0; str[i]; i++);
            i = i - 1;

            if (str[0] == '#' && str[i] == '#') {
                if (creat_update(head, str) != SUCCESS)
                    return FAILURE;
            } else {
                printf(ANSI_COLOR_RED"[ERROR] Pass correct file\n");
                return FAILURE;
            }
        }
    } else {
        printf(ANSI_COLOR_RED"[ERROR] Enter the file in .txt extension\n");
        return FAILURE;
    }

    return SUCCESS;
}
