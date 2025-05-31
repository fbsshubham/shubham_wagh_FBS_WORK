#include <stdio.h>
#include <string.h>

struct Movie {
    char title[50];
    char director[50];
    int releaseYear;
    char genre[20];
};

void addMovie(struct Movie movies[], int *count) {
    printf("Enter Movie Title: ");
    scanf(" %[^\n]", movies[*count].title);
    printf("Enter Director: ");
    scanf(" %[^\n]", movies[*count].director);
    printf("Enter Release Year: ");
    scanf("%d", &movies[*count].releaseYear);
    printf("Enter Genre: ");
    scanf(" %[^\n]", movies[*count].genre);
    (*count)++;
}

void displayMovies(struct Movie movies[], int count) {
    printf("\nMovie Database:\n");
    for (int i = 0; i < count; i++) {
        printf("Title: %s, Director: %s, Year: %d, Genre: %s\n",
               movies[i].title, movies[i].director, movies[i].releaseYear, movies[i].genre);
    }
}

void searchMovie(struct Movie movies[], int count, char title[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(movies[i].title, title) == 0) {
            printf("\nMovie Found: Title: %s, Director: %s, Year: %d, Genre: %s\n",
                   movies[i].title, movies[i].director, movies[i].releaseYear, movies[i].genre);
            return;
        }
    }
    printf("Movie not found.\n");
}

int main() {
    struct Movie movies[20];
    int count = 0, choice;
    char searchTitle[50];

    do {
        printf("\n1. Add Movie\n2. Display Movies\n3. Search Movie\n4. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addMovie(movies, &count);
                break;
            case 2:
                displayMovies(movies, count);
                break;
            case 3:
                printf("Enter Title to Search: ");
                scanf(" %[^\n]", searchTitle);
                searchMovie(movies, count, searchTitle);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid Choice. Try Again.\n");
        }
    } while (choice != 4);

    return 0;
}

