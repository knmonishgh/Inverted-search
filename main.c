#include "inverted.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
    system("cls");
    files *file = NULL;
    hash_t hash_table[25];
    for (int i = 0; i < 25; i++)
    {
        hash_table[i].index = i;
        hash_table[i].hlink = NULL;
    }

    printf("\n\033[33;45m                        INVERTED SEARCH                                  \033[0m\n\n");

    if (readandvalidate(argc, argv, &file) == success)
    {
        printf("\033[0;32m");
        printf("\tValidated files successfully!! \n");
        printf("\033[0m");
        while (1)
        {
            int choice;
            printf("\n\t 1. Create\n\t 2. Display\n\t 3. Update\n\t 4. Save\n\t 5. Search\n\t 6. Exit\n\n");
            printf("\033[33;45m");
            printf("\tEnter your choice : ");
            printf("\033[0m");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                if (create_database(file, hash_table) == success)
                {
                    printf("\033[0;32m");
                    printf("\n\tDatabase successfully created!!\n");
                    printf("\033[0m");
                }
                else
                {
                    printf("\033[0;31m");
                    printf("\n\tDatabase creation Failed\n");
                    printf("\033[0m");
                }
                break;
            case 2:
                printf("\n");
                if(Display(hash_table)==success)
                {
                    printf("\033[0;32m");
                    printf("\n\tDatabase Displayed successfully!!\n");
                    printf("\033[0m");
                }
                else
                {
                    printf("\033[0;31m");
                    printf("\n\tDatabase could'nt be displayed\n");
                    printf("\033[0m");
                }
                break;
            case 4:
                printf("\n");
                if(save(hash_table)==success)
                {
                    printf("\033[0;32m");
                    printf("\n\tDatabase saved successfully!!\n");
                    printf("\033[0m");
                }
                else
                {
                    printf("\033[0;31m");
                    printf("\n\tDatabase could'nt be saved\n");
                    printf("\033[0m");
                }
                break;
            case 5:
                printf("\n");
                if(search(hash_table)==success)
                {
                    printf("\033[0;32m");
                    printf("\n\tSearch successfull!!\n");
                    printf("\033[0m");
                }
                else
                {
                    printf("\033[0;31m");
                    printf("\n\tData not Found  \n");
                    printf("\033[0m");
                }
                break;
            case 6:
                printf("\n\033[33;45m                                                                         \033[0m\n\n");
                exit(0);

            default:
                break;
            }
        }
    }

    printf("\n\033[33;45m                                                                         \033[0m\n\n");
}