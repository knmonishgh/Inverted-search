#include "inverted.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

FILE *fptr;
FILE *save_fptr;

status insert_last(char *data, files **file)
{
    files *new_file = malloc(sizeof(files));
    if (new_file == NULL)
    {
        printf("\033[0;31m");
        printf("\t X ERROR\t: Memory allocation failed\n\n");
        printf("\033[0m");
        return failure;
    }

    strcpy(new_file->file_name, data);
    new_file->flink = NULL;

    if (*file == NULL)
    {
        *file = new_file;
    }
    else
    {
        files *cur = *file;
        files *prev = NULL;
        int flag = 0;

        while (cur != NULL)
        {
            if (strcmp(cur->file_name, data) == 0)
            {
                flag = 1;
                printf("\033[0;31m");
                printf("\t X Duplicate found\t: %s\n\n", cur->file_name);
                printf("\033[0m");
                break;
            }
            prev = cur;
            cur = cur->flink;
        }

        if (flag == 0)
        {
            prev->flink = new_file;
        }
        else
        {
            free(new_file);
        }
    }
}

status readandvalidate(int argc, char **argv, files **file)
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (strstr(argv[i], ".txt") != NULL)
            {
                FILE *temp_fptr = fopen(argv[i], "r");
                if (!temp_fptr)
                {
                    printf("\033[0;31m");
                    printf("\t X ERROR\t:failed to open the file %s\n\n", argv[i]);
                    printf("\033[0m");
                    return failure;
                }

                fseek(temp_fptr, 0, SEEK_END);
                int size = ftell(temp_fptr);
                fclose(temp_fptr);

                if (size == 0)
                {
                    printf("\033[0;31m");
                    printf("\t X Empty file\t\t: %s\n\n", argv[i]);
                    printf("\033[0m");
                    continue;
                }
                insert_last(argv[i], &*file);
            }
            else
            {
                printf("\033[0;31m");
                printf("\t X Error : ./Usage\t: filename.txt \n\n");
                printf("\033[0m");
            }
        }
    }
    else
    {
        printf("\033[0;31m");
        printf("\t X Error : No arguments found \n\n");
        printf("\033[0;31m");
        return failure;
    }
    return success;
}

status open_files(char *name)
{
    fptr = fopen(name, "r");
    if (!fptr)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", name);
        return failure;
    }
}

status create_database(files *file, hash_t hast_table[])
{
    files *each_file = file;
    char buff[30];
    while (each_file != NULL)
    {
        open_files(each_file->file_name);
        rewind(fptr);
        while (fscanf(fptr, "%s", buff) != EOF)
        {
            buff[0] = toupper(buff[0]);
            int ind = buff[0] % 65;
            word_node *new = malloc(sizeof(word_node));
            strcpy(new->word, buff);
            new->Flink = NULL;
            new->Wnode = NULL;
            new->file_count = 1;
            file_node *subnew = malloc(sizeof(file_node));
            strcpy(subnew->file_name, each_file->file_name);
            subnew->word_count = 1;
            subnew->link = NULL;
            if (hast_table[ind].hlink == NULL)
            {
                new->Flink = subnew;
                hast_table[ind].hlink = new;
            }
            else
            {
                word_node *maintemp = hast_table[ind].hlink;
                word_node *mainprev = NULL;
                while (maintemp != NULL)
                {
                    if (strcmp(maintemp->word, new->word) == 0)
                    {
                        file_node *subtemp = maintemp->Flink;
                        file_node *subprev = NULL;
                        while (subtemp != NULL)
                        {
                            if (strcmp(subtemp->file_name, subnew->file_name) == 0)
                            {
                                subtemp->word_count++;
                                break;
                            }
                            subprev = subtemp;
                            subtemp = subtemp->link;
                        }
                        if (subtemp == NULL)
                        {
                            maintemp->file_count++;
                            subprev->link = subnew;
                        }
                        break;
                    }
                    mainprev = maintemp;
                    maintemp = maintemp->Wnode;
                }
                if (maintemp == NULL)
                {
                    new->Flink = subnew;
                    mainprev->Wnode = new;
                }
            }
        }
        fclose(fptr);
        each_file = each_file->flink;
    }
    return success;
}

status Display(hash_t hast_table[])
{
    printf("\033[0;36m");
    for (int i = 0; i < 25; i++)
    {

        word_node *distemp = hast_table[i].hlink;
        while (distemp != NULL)
        {
            printf("\t%d:%s:", distemp->file_count, distemp->word);
            file_node *disfile = distemp->Flink;
            for (int j = 0; j < distemp->file_count; j++)
            {
                printf("%d:%s:", disfile->word_count, disfile->file_name);
                disfile = disfile->link;
            }
            printf("\n\n");
            distemp = distemp->Wnode;
        }
    }
    printf("\033[0m");
    return success;
}

status save(hash_t hast_table[])
{
    save_fptr = fopen("Output.txt", "wb+");
    if (!save_fptr)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", "Output.txt");
        return failure;
    }
    for (int i = 0; i < 25; i++)
    {
        word_node *distemp = hast_table[i].hlink;
        while (distemp != NULL)
        {
            fprintf(save_fptr, "\t%d:%s:", distemp->file_count, distemp->word);
            file_node *disfile = distemp->Flink;
            for (int j = 0; j < distemp->file_count; j++)
            {
                fprintf(save_fptr, "%d:%s:", disfile->word_count, disfile->file_name);
                disfile = disfile->link;
            }
            fprintf(save_fptr, "\n\n");
            distemp = distemp->Wnode;
        }
    }
    return success;
}