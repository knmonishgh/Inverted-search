#include<stdio.h>



#define namesize 10
#define wordsize 30

/*structure for storing the file names*/
typedef struct file 
{
    char file_name[namesize];
    struct file *flink;
}files;
 
/*struture for main table*/
typedef struct hashnode
{
    int index;
    struct node1 *hlink; 
}hash_t;

/*structure to store the word count in each file*/
typedef struct node 
{
    int word_count;
    char file_name[namesize];
    struct node *link;
}file_node;


/*structure to store file countw where the word is present*/
typedef struct node1 
{
    int file_count;
    char word[30];
    struct node *Flink;
    struct node1 *Wnode;
}word_node;

typedef enum
{
    success,
    failure
}status;


/*To validate the files*/
status readandvalidate(int argc,char **argv,files **file);

/*To insert values at last*/
status insert_last(char *data,files **file);

/*To create the database*/
status create_database(files *file,hash_t hast_table[]);

/*To Display the database created*/
status Display(hash_t hast_table[]);

/*To save the database created into a file*/
status save(hash_t hast_table[]);