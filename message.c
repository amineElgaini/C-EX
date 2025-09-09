#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Funcs
{
    ADD = 1,
    DELETE,
    SEARCH,
    DISPLAY,
    UPDATE,
    SORT,
    TOTAL,
    EXIT
};



typedef struct Adress {
    char street[100];
    char city[100];
    char country[100];
} Adress;

typedef struct Book {
    char title[100];
    char author[100];
    float price;
    int quantity;
    int year;
    Adress adress;
} Book;

int books_count = 0;

void clear_buffer() {
    while (getchar() != '\n');
}

void clear_newline(char str[]) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }else
    {
        clear_buffer();
    }
}

void addBook(Book **arr){
    Book newBook;
    printf("Enter book title: ");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    clear_newline(newBook.title);
    
    printf("Enter book author: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    clear_newline(newBook.author);
    
    printf("Enter book price: ");
    scanf("%f", &newBook.price);
    clear_buffer();
    
    printf("Enter book quantity: ");
    scanf("%d", &newBook.quantity);
    clear_buffer();
    
    printf("Enter book year: ");
    scanf("%d", &newBook.year);
    clear_buffer();

    printf("Enter book author street: ");
    fgets(newBook.adress.street, sizeof(newBook.adress.street), stdin);
    clear_newline(newBook.adress.street);

    printf("Enter book author city: ");
    fgets(newBook.adress.city, sizeof(newBook.adress.city), stdin);
    clear_newline(newBook.adress.city);

    printf("Enter book author country: ");
    fgets(newBook.adress.country, sizeof(newBook.adress.country), stdin);
    clear_newline(newBook.adress.country);
    
    *arr = realloc(*arr, (books_count + 1) * sizeof(Book));
    (*arr)[books_count] = newBook;
    books_count++;

    FILE *fp = fopen("./books.dat", "wb");
    fwrite(*arr, sizeof(Book), books_count, fp);
    fclose(fp);
    
    printf("Book added successfully!\n");
}

void deleteBook(Book **arr){
    char title[100];
    printf("Enter book title: ");
    fgets(title, sizeof(title), stdin);
    clear_newline(title);
    
    for (int i = 0; i < books_count; i++)
    {
        if (strcmp((*arr)[i].title , title) == 0)
        {
            for (int j = i; j < books_count - 1; j++)
            {
                (*arr)[j] = (*arr)[j + 1];
            }
            
            *arr = realloc(*arr, (--books_count) * sizeof(Book));
            break; 
        } 
    }
    
    printf("Book deleted successfully!\n");
}

void displayBooks(Book **arr){
    for (int i = 0; i < books_count; i++)
    {
        printf("Title: %s, Author: %s, Adress: %s, %s, %s, Price: %.2f, Quantity: %d, Year: %d\n", (*arr)[i].title, (*arr)[i].author, (*arr)[i].adress.street, (*arr)[i].adress.country, (*arr)[i].adress.city, (*arr)[i].price, (*arr)[i].quantity, (*arr)[i].year);
    }
}

void sortBooksByYear(Book **arr){
    Book temp;
    for (int i = 0; i < books_count - 1 ; i++){   
        for (int j = 0; j < books_count - i - 1 ; j++){   
            temp = (*arr)[j];
            if (temp.year > (*arr)[j+1].year)
            {
                (*arr)[j] = (*arr)[j + 1];
                (*arr)[j + 1] = temp;
            }
        }
    }
    printf("Books sorted successfully!\n");

    displayBooks(arr);
}

void searchBook(Book **arr){
    char title[100];
    printf("Enter book title: ");
    fgets(title, sizeof(title), stdin);
    clear_newline(title);

    for (int i = 0; i < books_count; i++)
    {
        if (strcmp((*arr)[i].title , title) == 0)
        {
            printf("Title: %s, Author: %s, Adress: %s, %s, %s, Price: %.2f, Quantity: %d, Year: %d\n", (*arr)[i].title, (*arr)[i].author, (*arr)[i].adress.street, (*arr)[i].adress.country, (*arr)[i].adress.city, (*arr)[i].price, (*arr)[i].quantity, (*arr)[i].year);
            break;
        }
    }
}

void updateBookQuantity(Book **arr){
    char title[100];
    int quantity;
    printf("Enter book title: ");
    fgets(title, sizeof(title), stdin);
    clear_newline(title);

    printf("Enter new quantity: ");
    scanf("%d", &quantity);
    clear_buffer();

    for (int i = 0; i < books_count; i++)
    {
        if (strcmp((*arr)[i].title , title) == 0)
        {
            (*arr)[i].quantity = quantity;
            break;
        }
    }

    printf("Book quantity updated successfully!\n");
}

int main()
{
    FILE *fp = fopen("./books.dat", "rb");
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);
    books_count = fileSize / sizeof(Book);

    Book *Books = calloc(books_count, sizeof(Book));
    fread(Books, sizeof(Book), books_count, fp);
    fclose(fp);

    while (1)
    {
        printf("Enter 1 to add a book\n");
        printf("Enter 2 to delete a book\n");
        printf("Enter 3 to search a book\n");
        printf("Enter 4 to display all books\n");
        printf("Enter 5 to update book quantity\n");
        printf("Enter 6 to sort book by year\n");
        printf("Enter 7 to calculate total inventory value\n");
        printf("Enter 8 to exit\n");
        printf("Your choice: ");
        int choice;
        scanf("%d", &choice);
        clear_buffer();

        switch (choice)
        {
        case ADD:
            addBook(&Books);
            break;
        case DELETE:
            deleteBook(&Books);
            break;
        case SEARCH:
            searchBook(&Books);
            break;
        case DISPLAY:
            displayBooks(&Books);
            break;
        case UPDATE:
            updateBookQuantity(&Books);
            break;
        case SORT:
            sortBooksByYear(&Books);
            break;
        case TOTAL:
            printf("Total books: %d\n", books_count);
            break;
        case EXIT:
            free(Books);
            exit(0);
        default:
            printf("Invalid choice\n");
            break;
        }
    }
    return 0;
}