#include <stdio.h>
#include <string.h>

struct file
{
    char name[20];
    int startblock;
    int numblock;
};
void continuous_allocation(struct file files[], int filecount, char searchfile[])
{
    for (int i = 0; i < filecount; i++)
    {
        if (strcmp(files[i].name, searchfile) == 0)
        {
            printf("file name : %s found\n", files[i].name);
            printf("startblock : %d\n", files[i].startblock);
            printf("Blocks occupied\n");
            for (int j = 0; j < files[i].numblock; j++)
            {
                printf("%d ", files[i].startblock + j);
            }
            printf("\n");
            return;
        }
    }
    printf("Not found\n");
}

int main()
{
    int filecount;
    char searchfile[20];

    printf("Enter the number of files\n");
    scanf("%d", &filecount);
    struct file files[filecount];
    for (int i = 0; i < filecount; i++)
    {
        printf("Enter the file name\n");
        scanf("%s", files[i].name);
        printf("Enter the starting block\n");
        scanf("%d", &files[i].startblock);
        printf("Enter the numBlocks\n");
        scanf("%d", &files[i].numblock);
    }

    printf("Enter the file name to be searched\n");
    scanf("%s", searchfile);
    continuous_allocation(files, filecount, searchfile);
    return 0;
}