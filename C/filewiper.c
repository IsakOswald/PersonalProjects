#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* getFileHandle(char* fileName, char* mode)
{
    FILE* file = fopen(fileName, mode);

    if (file == NULL)
    {
        fprintf(stderr, "Error getting file handle! \n");
        exit(1);
        return NULL;
    }

    return file;
}

void readFile(FILE* file)
{
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file))
    {
        // fgets will automatically add terminator

        printf("%s", buffer);
    }
}

void writeFile(FILE* file)
{
    char* buffer = "WIPED!";

    fwrite(buffer, sizeof(char), strlen(buffer), file);
}

int main()
{
    char usrFile[100];

    printf("Enter target file: ");
    fgets(usrFile, sizeof(usrFile), stdin);

    size_t len = strlen(usrFile);

    if (len > 0 && usrFile[len - 1] == '\n')
    {
        usrFile[len - 1] = '\0';
    }

    readFile(getFileHandle(usrFile, "r"));
    writeFile(getFileHandle(usrFile, "wb"));

    return 0;
}
