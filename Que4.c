#include <stdio.h>
struct Product {
    char name[50];
    float price;
    int quantity;
};

int main() {
    struct Product cart[10];
    int count = 0;
    char choice;
    float totalCost = 0;

    do {
        printf("Enter Product Name: ");
        scanf(" %[^\n]", cart[count].name);
        printf("Enter Price: ");
        scanf("%f", &cart[count].price);
        printf("Enter Quantity: ");
        scanf("%d", &cart[count].quantity);

        totalCost += cart[count].price * cart[count].quantity;
        count++;

        printf("Add another product? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' && count < 10);

    printf("\nCart Details:\n");
    for (int i = 0; i < count; i++) {
        printf("Product: %s, Price: %.2f, Quantity: %d\n",
               cart[i].name, cart[i].price, cart[i].quantity);
    }
    printf("Total Cost: %.2f\n", totalCost);
    return 0;
}

