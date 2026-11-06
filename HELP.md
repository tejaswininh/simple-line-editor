# HELP – Simple Line Editor

## 1. Introduction

The Simple Line Editor is a command-line text editing application developed using C. It allows users to create, modify, search and manage a document through a menu-driven interface.

## 2. Starting the Program

Compile the program:

```bash
gcc main.c -o main
```

Run on Windows:

```powershell
.\main.exe
```

The main menu will appear.

## 3. Menu Options

### 1. Insert Line
- Enter option `1`.
- Enter the position where the new line should be inserted.
- Type the text.
- The line will be inserted at the specified position.

### 2. Delete Line
- Enter option `2`.
- Enter the line number to delete.
- The selected line will be removed.

### 3. Display Document
- Enter option `3`.
- All document lines will be displayed with their line numbers.

### 4. Save Document
- Enter option `4`.
- The current document will be saved in `document.txt`.
- The file is created automatically when saving.

### 5. Load Document
- Enter option `5`.
- Previously saved content from `document.txt` will be loaded.

### 6. Search Word
- Enter option `6`.
- Type the word or phrase to search.
- Matching lines and their line numbers will be displayed.

### 7. Find and Replace
- Enter option `7`.
- Enter the existing word or phrase.
- Enter the replacement text.
- Matching occurrences will be replaced.

### 8. Undo Last Action
- Enter option `8`.
- The most recent supported modification will be undone.
- Only one previous modification can be undone.

### 9. Line Count
- Enter option `9`.
- The total number of lines in the document will be displayed.

### 10. Word Count
- Enter option `10`.
- The total number of words in the document will be displayed.

### 11. Exit
- Enter option `11`.
- The program will terminate.

## 4. Important Notes

- Maximum number of lines: 100.
- Maximum characters per line: 255.
- Search and replace are case-sensitive.
- Line numbers start from 1.
- Undo supports only the most recent modification.
- Save the document before exiting if you want to retain your changes.

## 5. Example

If the user inserts these lines:

```text
Hello world!
I love C programming.
This is my project.
```

The Display Document option shows:

```text
1. Hello world!
2. I love C programming.
3. This is my project.
```

## 6. Error Handling

The application handles:
- Invalid menu choices.
- Invalid line numbers.
- Empty document operations.
- Missing files during loading.
- Document capacity limits.
- Replacement text exceeding the maximum line length.