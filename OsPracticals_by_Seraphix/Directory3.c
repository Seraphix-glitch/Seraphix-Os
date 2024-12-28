#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 256
void write_details(int fd, const char *details)
{
    write(fd, details, strlen(details));
}
int main()
{
    int file1, file2;
    char buffer1[BUFFER_SIZE], buffer2[BUFFER_SIZE];
    ssize_t bytesRead1, bytesRead2;
    file1 = open("my_details.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file1 == -1)
    {
        perror("Error opening file my_details.txt");
        return 1;
    }
    write_details(file1, "Name: John\nAge: 30\nCity: New York\n");
    close(file1);
    file2 = open("friend_details.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file2 == -1)
    {
        perror("Error opening file friend_details.txt");
        return 1;
    }
    write_details(file2, "Name: John\nAge: 30\nCity: Los Angeles\n");
    close(file2);
    file1 = open("my_details.txt", O_RDONLY);
    file2 = open("friend_details.txt", O_RDONLY);

    if (file1 == -1 || file2 == -1)
    {
        perror("Error opening files for reading");
        return 1;
    }
    printf("Matching lines in both files:\n");
    while ((bytesRead1 = read(file1, buffer1, sizeof(buffer1) - 1)) > 0 &&
           (bytesRead2 = read(file2, buffer2, sizeof(buffer2) - 1)) > 0)
    {
        buffer1[bytesRead1] = '\0';
        buffer2[bytesRead2] = '\0';

        char *line1 = strtok(buffer1, "\n");
        while (line1 != NULL)
        {
            char *line2 = strtok(buffer2, "\n");
            while (line2 != NULL)
            {
                if (strcmp(line1, line2) == 0)
                {
                    printf("%s\n", line1);
                }
                line2 = strtok(NULL, "\n");
            }
            line1 = strtok(NULL, "\n");
        }
    }
    close(file1);
    close(file2);
    return 0;
}
