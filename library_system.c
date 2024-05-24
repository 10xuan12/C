#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BOOKS 100
#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 100
#define MAX_EDITION_LENGTH 50
#define MAX_ISBN_LENGTH 13
#define MAX_STUDENT_ID_LENGTH 20
#define MAX_PASSWORD_LENGTH 5

struct Date {
    int day;
    int month;
    int year;
};

struct Book {
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    int year;
    char edition[MAX_EDITION_LENGTH];
    char isbn[MAX_ISBN_LENGTH];
    int copyCode;
    int borrowed;
    char borrowedBy[MAX_STUDENT_ID_LENGTH];
    struct Date borrowDate;
    struct Date returnDate;
};

struct Student {
    char id[MAX_STUDENT_ID_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct Book library[MAX_BOOKS];
int numBooks = 0;
struct Student students[MAX_BOOKS];
int numStudents = 0;

void addBook(char *title, char *author, int year, char *edition, char *isbn, int copyCode) {
    if (numBooks < MAX_BOOKS) {
        strcpy(library[numBooks].title, title);
        strcpy(library[numBooks].author, author);
        library[numBooks].year = year;
        strcpy(library[numBooks].edition, edition);
        strcpy(library[numBooks].isbn, isbn);
        library[numBooks].copyCode = copyCode;
        library[numBooks].borrowed = 0;
        library[numBooks].borrowedBy[0] = '\0';  // Initialize as not borrowed
        numBooks++;
    } else {
        printf("Library is full!\n");
    }
}

void deleteBook(char *isbn, int copyCode) {
    int index = -1;
	int i;
    for (i = 0; i < numBooks; i++) {
        if (strcmp(library[i].isbn, isbn) == 0 && library[i].copyCode == copyCode) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Book not found!\n");
        return;
    }
    
    int j;
    for (j = index; j < numBooks - 1; j++) {
        library[j] = library[j + 1];
    }

    numBooks--;
    printf("Book deleted successfully!\n");
}

void displayBooks() {
    int i;
	while(i<numBooks){
		printf("%d. Title: %s, Author: %s, Year: %d, Edition: %s, ISBN: %s, Copy Code: %d, Borrowed: %s\n",
               i + 1, library[i].title, library[i].author, library[i].year, library[i].edition, library[i].isbn, library[i].copyCode,
               library[i].borrowed ? "Yes" : "No");
        i++;	
	}
}

void addStudent(char *id, char *password) {
    if (numStudents < MAX_BOOKS) {
        strcpy(students[numStudents].id, id);
        strcpy(students[numStudents].password, password);
        numStudents++;
    } else {
        printf("Maximum number of students reached!\n");
    }
}

void loadStudentsFromFile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    char id[MAX_STUDENT_ID_LENGTH];
    char borrowedBooks[MAX_BOOKS][MAX_ISBN_LENGTH];
    int i = 0;
    while (fscanf(file, "%s", id) == 1) {
        strcpy(students[i].id, id);
        while (fscanf(file, "%s", borrowedBooks[i]) == 1 && strcmp(borrowedBooks[i], "³o¬Ostudents") != 0) {
            i++;
        }
    }

    fclose(file);
}

void loadBooksFromFile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    char title[MAX_TITLE_LENGTH], author[MAX_AUTHOR_LENGTH], edition[MAX_EDITION_LENGTH], isbn[MAX_ISBN_LENGTH];
    int year, copyCode;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int fields = sscanf(line, "%s %s %d %s %s %d", title, author, &year, edition, isbn, &copyCode);
        if (fields == 6) {
            addBook(title, author, year, edition, isbn, copyCode);
        }
    }

    fclose(file);
}

int findBookIndexByTitle(char *title) {
	int i;
    for (i = 0; i < numBooks; i++) {
        if (strcmp(library[i].title, title) == 0) {
            return i;
        }
    }
    return -1;
}

int findBookIndexByAuthor(char *author) {
	int i;
    for (i = 0; i < numBooks; i++) {
        if (strcmp(library[i].author, author) == 0) {
            return i;
        }
    }
    return -1;
}

int findBookIndexByISBN(char *isbn) {
	int i;
    for (i = 0; i < numBooks; i++) {
        if (strcmp(library[i].isbn, isbn) == 0) {
            return i;
        }
    }
    return -1;
}

void searchBookByTitle() {
    char title[MAX_TITLE_LENGTH];
    printf("Enter book title: ");
    scanf("%s", title);

    int index = findBookIndexByTitle(title);
    if (index != -1) {
        printf("Book found:\n");
        printf("Title: %s, Author: %s, Year: %d, Edition: %s, ISBN: %s, Copy Code: %d, Borrowed: %s\n",
               library[index].title, library[index].author, library[index].year, library[index].edition, library[index].isbn,
               library[index].copyCode, library[index].borrowed ? "Yes" : "No");
    } else {
        printf("Book not found!\n");
    }
}

void searchBookByAuthor() {
    char author[MAX_AUTHOR_LENGTH];
    printf("Enter book author: ");
    scanf("%s", author);

    int index = findBookIndexByAuthor(author);
    if (index != -1) {
        printf("Book found:\n");
        printf("Title: %s, Author: %s, Year: %d, Edition: %s, ISBN: %s, Copy Code: %d, Borrowed: %s\n",
               library[index].title, library[index].author, library[index].year, library[index].edition, library[index].isbn,
               library[index].copyCode, library[index].borrowed ? "Yes" : "No");
    } else {
        printf("Book not found!\n");
    }
}

void searchBookByISBN() {
    char isbn[MAX_ISBN_LENGTH];
    printf("Enter book ISBN: ");
    scanf("%s", isbn);

    int index = findBookIndexByISBN(isbn);
    if (index != -1) {
        printf("Book found:\n");
        printf("Title: %s, Author: %s, Year: %d, Edition: %s, ISBN: %s, Copy Code: %d, Borrowed: %s\n",
               library[index].title, library[index].author, library[index].year, library[index].edition, library[index].isbn,
               library[index].copyCode, library[index].borrowed ? "Yes" : "No");
    } else {
        printf("Book not found!\n");
    }
}

void displayBorrowedBooks(char *studentId) {
    int found = 0;
    printf("Borrowed books for student with ID %s:\n", studentId);
    int i;
    for (i = 0; i < numBooks; i++) {
        if (library[i].borrowed && strcmp(library[i].borrowedBy, studentId) == 0) {
            printf("Title: %s, Author: %s, Year: %d, Edition: %s, ISBN: %s, Copy Code: %d\n",
                   library[i].title, library[i].author, library[i].year, library[i].edition, library[i].isbn, library[i].copyCode);
            found = 1;
        }
    }
    if (!found) {
        printf("No borrowed books found for this student.\n");
    }
}


void borrowBook(char *isbn, int copyCode, char *studentId) {
    int index = findBookIndexByISBN(isbn);

    if (index == -1 || library[index].copyCode != copyCode) {
        printf("Book not found.\n");
        return;
    }

    if (library[index].borrowed) {
        printf("Book already borrowed.\n");
        return;
    }

    library[index].borrowed = 1;
    strcpy(library[index].borrowedBy, studentId);
    printf("Book borrowed successfully!\n");
}

void returnBook(char *isbn, int copyCode, char *studentId) {
    int index = findBookIndexByISBN(isbn);

    if (index == -1 || library[index].copyCode != copyCode) {
        printf("Book not found.\n");
        return;
    }

    if (library[index].borrowed && strcmp(library[index].borrowedBy, studentId) == 0) {
        library[index].borrowed = 0;
        library[index].borrowedBy[0] = '\0';
        printf("Book returned successfully!\n");
    } else {
        printf("Book not borrowed by this student.\n");
    }
}

int main() {
    char studentsFilename[] = "Students.txt";
    char booksFilename[] = "Books.txt";
    char isbn[MAX_ISBN_LENGTH];
    int copyCode;
    char studentId[MAX_STUDENT_ID_LENGTH];

    loadStudentsFromFile(studentsFilename);
    loadBooksFromFile(booksFilename);

    int choice;

    do {
        printf("\nLibrary Management System\n");
        printf("A. Add a book\n");
        printf("D. Delete a book\n");
        printf("S. Search for a book\n");
        printf("B. Borrow a book\n");
        printf("R. Return a book\n");
        printf("I. View personal borrowed books\n");
        printf("P. Print all books\n");
        printf("E. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'A':
            case 'a': {
                char title[MAX_TITLE_LENGTH], author[MAX_AUTHOR_LENGTH], edition[MAX_EDITION_LENGTH];
                int year;

                printf("Enter book title: ");
                scanf("%s", title);
                printf("Enter book author: ");
                scanf("%s", author);
                printf("Enter publication year: ");
                scanf("%d", &year);
                printf("Enter edition: ");
                scanf("%s", edition);
                printf("Enter ISBN: ");
                scanf("%s", isbn);
                printf("Enter copy code: ");
                scanf("%d", &copyCode);

                addBook(title, author, year, edition, isbn, copyCode);
                break;
            }
            case 'D':
            case 'd': {
                printf("Enter ISBN: ");
                scanf("%s", isbn);
                printf("Enter copy code: ");
                scanf("%d", &copyCode);

                deleteBook(isbn, copyCode);
                break;
            }
            case 'S':
            case 's': {
                int searchChoice;
                printf("Search by:\n");
                printf("1. Title\n");
                printf("2. Author\n");
                printf("3. ISBN\n");
                printf("Enter your choice: ");
                scanf("%d", &searchChoice);

                switch (searchChoice) {
                    case 1:
                        searchBookByTitle();
                        break;
                    case 2:
                        searchBookByAuthor();
                        break;
                    case 3:
                        searchBookByISBN();
                        break;
                    default:
                        printf("Invalid choice!\n");
                }
                break;
            }
            case 'B':
            case 'b': {
                printf("Student ID: ");
                scanf("%s", studentId);
                printf("Enter ISBN: ");
                scanf("%s", isbn);
                printf("Enter copy code: ");
                scanf("%d", &copyCode);

                borrowBook(isbn, copyCode, studentId);
                break;
            }
            case 'R':
            case 'r': {
                printf("Student ID: ");
                scanf("%s", studentId);
                printf("Enter ISBN: ");
                scanf("%s", isbn);
                printf("Enter copy code: ");
                scanf("%d", &copyCode);

                returnBook(isbn, copyCode, studentId);
                break;
            }
            case 'I':
            case 'i': {
                printf("Student ID: ");
                scanf("%s", studentId);
                displayBorrowedBooks(studentId);
                break;
            }
            case 'P':
            case 'p':
                displayBooks();
                break;
            case 'E':
            case 'e':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 'E' && choice != 'e');

    return 0;
}

