#include <stdio.h>
struct Book {
    char bname[50];
    int id;
    char author[50];
    float price;
};

int main() {
    struct Book b;
    printf("Enter Book Name: ");
    scanf(" %[^\n]", b.bname);
    printf("Enter Book ID: ");
    scanf("%d", &b.id);
    printf("Enter Author Name: ");
    scanf(" %[^\n]", b.author);
    printf("Enter Price: ");
    scanf("%f", &b.price);

    printf("\nBook Details:\n");
    printf("Name: %s\nID: %d\nAuthor: %s\nPrice: %.2f\n", b.bname, b.id, b.author, b.price);
    return 0;
}

