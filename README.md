# Simple Line Editor in C

## Project Overview
The Simple Line Editor is a command-line application developed using the C programming language. It allows users to create and edit a text document by inserting, deleting, searching and replacing lines.

The application also supports saving and loading documents using file handling.

## Features

1. **Insert Line** – Insert a new line at a specified position.
2. **Delete Line** – Delete a line using its line number.
3. **Display Document** – Display all lines in the document.
4. **Save Document** – Save the document to `document.txt`.
5. **Load Document** – Load previously saved content.
6. **Search Word** – Search for a word or phrase in the document.
7. **Find and Replace** – Replace matching text.
8. **Undo Last Action** – Undo the most recent modification.
9. **Line Count** – Display the total number of lines.
10. **Word Count** – Display the total number of words.

## Technologies Used
- Programming Language: C
- Compiler: GCC
- Data Structure: Two-dimensional character array
- Concepts: Arrays, Functions, Strings, Pointers, File Handling

## Limitations
- Maximum document capacity: 100 lines.
- Maximum characters per line: 255.
- Undo supports one previous modification at a time.
- Search and replace are case-sensitive.

## How to Compile and Run

Open the project folder in the terminal.

Compile:

```bash
gcc main.c -o main
```

Run on Windows:

```powershell
.\main.exe
```

Run on Linux/macOS:

```bash
./main
```

## Project Structure

```text
lineEditor/
│
├── main.c
├── .gitignore
├── README.md
├── HELP.md
└── document.txt  (created when saving)
```

## Author
Tejaswini

## Project Type
Portfolio Building – Activity 7