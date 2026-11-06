
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LINES 100
#define MAX_LENGTH 256
#define FILE_NAME "document.txt"

char lines[MAX_LINES][MAX_LENGTH];
int count = 0;

// Undo storage
char oldLines[MAX_LINES][MAX_LENGTH];
int oldCount = 0;
int undoAvailable = 0;

// Read a complete line of input
void readInput(char str[], int size)
{
    if (fgets(str, size, stdin) != NULL)
    {
        str[strcspn(str, "\n")] = '\0';
    }
}

// Read an integer safely
int readInteger()
{
    char input[50];
    char *end;
    long value;

    readInput(input, sizeof(input));

    value = strtol(input, &end, 10);

    while (isspace((unsigned char)*end))
        end++;

    if (input[0] == '\0' || *end != '\0' ||
        value < -2147483647L - 1 || value > 2147483647L)
    {
        return -1;
    }

    return (int)value;
}

// Store the current document for undo
void saveUndo()
{
    oldCount = count;

    for (int i = 0; i < count; i++)
    {
        strcpy(oldLines[i], lines[i]);
    }

    undoAvailable = 1;
}

// Insert a line
void insertLine()
{
    int pos;
    char text[MAX_LENGTH];

    if (count >= MAX_LINES)
    {
        printf("Document is full!\n");
        return;
    }

    printf("Enter line number: ");
    pos = readInteger();

    if (pos < 1 || pos > count + 1)
    {
        printf("Invalid line number!\n");
        return;
    }

    printf("Enter text: ");
    readInput(text, MAX_LENGTH);

    saveUndo();

    for (int i = count; i >= pos; i--)
    {
        strcpy(lines[i], lines[i - 1]);
    }

    strcpy(lines[pos - 1], text);
    count++;

    printf("Line inserted successfully!\n");
}

// Delete a line
void deleteLine()
{
    int pos;

    if (count == 0)
    {
        printf("Document is empty!\n");
        return;
    }

    printf("Enter line number to delete: ");
    pos = readInteger();

    if (pos < 1 || pos > count)
    {
        printf("Invalid line number!\n");
        return;
    }

    saveUndo();

    for (int i = pos - 1; i < count - 1; i++)
    {
        strcpy(lines[i], lines[i + 1]);
    }

    count--;

    printf("Line deleted successfully!\n");
}

// Display document
void displayDocument()
{
    if (count == 0)
    {
        printf("Document is empty!\n");
        return;
    }

    printf("\n========== DOCUMENT ==========\n");

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s\n", i + 1, lines[i]);
    }

    printf("==============================\n");
}

// Save document to file
void saveDocument()
{
    FILE *fp = fopen(FILE_NAME, "w");

    if (fp == NULL)
    {
        printf("Unable to save file!\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s\n", lines[i]);
    }

    fclose(fp);

    printf("Document saved to %s successfully!\n", FILE_NAME);
}

// Load document from file
void loadDocument()
{
    FILE *fp = fopen(FILE_NAME, "r");
    char temp[MAX_LINES][MAX_LENGTH];
    int tempCount = 0;
    int valid = 1;

    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }

    while (fgets(temp[tempCount], MAX_LENGTH, fp) != NULL)
    {
        size_t len = strlen(temp[tempCount]);

        if (len > 0 && temp[tempCount][len - 1] == '\n')
        {
            temp[tempCount][len - 1] = '\0';
        }
        else if (!feof(fp))
        {
            int ch;
            while ((ch = fgetc(fp)) != '\n' && ch != EOF)
            {
                // Discard characters beyond the line limit
            }

            printf("A line exceeds the maximum length!\n");
            valid = 0;
            break;
        }

        if (tempCount == MAX_LINES - 1)
        {
            int ch = fgetc(fp);

            if (ch != EOF)
            {
                printf("Document exceeds maximum line capacity!\n");
                valid = 0;
            }

            break;
        }

        tempCount++;
    }

    fclose(fp);

    if (!valid)
        return;

    saveUndo();

    count = tempCount;

    for (int i = 0; i < count; i++)
    {
        strcpy(lines[i], temp[i]);
    }

    printf("Document loaded successfully!\n");
}

// Search for a word or phrase
void searchWord()
{
    char word[MAX_LENGTH];
    int found = 0;

    printf("Enter word or phrase to search: ");
    readInput(word, MAX_LENGTH);

    if (word[0] == '\0')
    {
        printf("Search text cannot be empty!\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        if (strstr(lines[i], word) != NULL)
        {
            printf("Found at line %d: %s\n", i + 1, lines[i]);
            found = 1;
        }
    }

    if (!found)
    {
        printf("Word not found!\n");
    }
}

// Replace occurrences of a phrase in one line
// Returns 1 on success, 0 if the result is too long
int replaceInLine(char source[], char oldWord[],
                  char newWord[], char result[])
{
    char *ptr;
    int len = 0;
    int oldLen = strlen(oldWord);
    int newLen = strlen(newWord);

    result[0] = '\0';

    ptr = source;

    while ((ptr = strstr(ptr, oldWord)) != NULL)
    {
        int prefixLen = ptr - source;

        if (len + prefixLen + newLen >= MAX_LENGTH)
            return 0;

        strncat(result, source, prefixLen);
        len += prefixLen;

        strcat(result, newWord);
        len += newLen;

        ptr += oldLen;
        source = ptr;
    }

    if (len + strlen(source) >= MAX_LENGTH)
        return 0;

    strcat(result, source);

    return 1;
}

// Find and replace
void findReplace()
{
    char oldWord[MAX_LENGTH];
    char newWord[MAX_LENGTH];
    char temp[MAX_LINES][MAX_LENGTH];
    int found = 0;

    printf("Enter word or phrase to replace: ");
    readInput(oldWord, MAX_LENGTH);

    if (oldWord[0] == '\0')
    {
        printf("Search text cannot be empty!\n");
        return;
    }

    printf("Enter replacement text: ");
    readInput(newWord, MAX_LENGTH);

    for (int i = 0; i < count; i++)
    {
        if (!replaceInLine(lines[i], oldWord, newWord, temp[i]))
        {
            printf("Replacement would exceed line length!\n");
            return;
        }

        if (strcmp(lines[i], temp[i]) != 0)
            found = 1;
    }

    if (!found)
    {
        printf("No matching text found!\n");
        return;
    }

    saveUndo();

    for (int i = 0; i < count; i++)
    {
        strcpy(lines[i], temp[i]);
    }

    printf("Replacement completed successfully!\n");
}

// Undo last modification
void undoAction()
{
    if (!undoAvailable)
    {
        printf("No action available to undo!\n");
        return;
    }

    count = oldCount;

    for (int i = 0; i < count; i++)
    {
        strcpy(lines[i], oldLines[i]);
    }

    undoAvailable = 0;

    printf("Last action undone successfully!\n");
}

// Count lines
void lineCount()
{
    printf("Total number of lines: %d\n", count);
}

// Count words
void wordCount()
{
    int total = 0;

    for (int i = 0; i < count; i++)
    {
        int inWord = 0;

        for (int j = 0; lines[i][j] != '\0'; j++)
        {
            if (isspace((unsigned char)lines[i][j]))
            {
                inWord = 0;
            }
            else if (!inWord)
            {
                total++;
                inWord = 1;
            }
        }
    }

    printf("Total number of words: %d\n", total);
}

// Main function
int main()
{
    int choice;

    while (1)
    {
        printf("\n======= SIMPLE LINE EDITOR =======\n");
        printf("1. Insert Line\n");
        printf("2. Delete Line\n");
        printf("3. Display Document\n");
        printf("4. Save Document\n");
        printf("5. Load Document\n");
        printf("6. Search Word\n");
        printf("7. Find and Replace\n");
        printf("8. Undo Last Action\n");
        printf("9. Line Count\n");
        printf("10. Word Count\n");
        printf("11. Exit\n");

        printf("Enter your choice: ");
        choice = readInteger();

        switch (choice)
        {
            case 1:
                insertLine();
                break;

            case 2:
                deleteLine();
                break;

            case 3:
                displayDocument();
                break;

            case 4:
                saveDocument();
                break;

            case 5:
                loadDocument();
                break;

            case 6:
                searchWord();
                break;

            case 7:
                findReplace();
                break;

            case 8:
                undoAction();
                break;

            case 9:
                lineCount();
                break;

            case 10:
                wordCount();
                break;

            case 11:
                printf("Exiting Line Editor. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
