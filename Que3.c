#include <stdio.h>
struct Player {
    char name[50];
    int matches, runs, wickets;
};

void acceptPlayers(struct Player players[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Enter details for Player %d:\n", i + 1);
        printf("Name: ");
        scanf(" %[^\n]", players[i].name);
        printf("Matches Played: ");
        scanf("%d", &players[i].matches);
        printf("Runs: ");
        scanf("%d", &players[i].runs);
        printf("Wickets: ");
        scanf("%d", &players[i].wickets);
    }
}

void displayPlayers(struct Player players[], int n) {
    printf("\nPlayer Details:\n");
    for (int i = 0; i < n; i++) {
        printf("Name: %s, Matches: %d, Runs: %d, Wickets: %d\n",
               players[i].name, players[i].matches, players[i].runs, players[i].wickets);
    }
}

void findBestPlayers(struct Player players[], int n) {
    int maxRuns = 0, maxWickets = 0, runIndex = 0, wicketIndex = 0;
    for (int i = 0; i < n; i++) {
        if (players[i].runs > maxRuns) {
            maxRuns = players[i].runs;
            runIndex = i;
        }
        if (players[i].wickets > maxWickets) {
            maxWickets = players[i].wickets;
            wicketIndex = i;
        }
    }
    printf("\nPlayer with Maximum Runs: %s, Runs: %d\n", players[runIndex].name, maxRuns);
    printf("Player with Maximum Wickets: %s, Wickets: %d\n", players[wicketIndex].name, maxWickets);
}

int main() {
    struct Player players[10];
    acceptPlayers(players, 10);
    displayPlayers(players, 10);
    findBestPlayers(players, 10);
    return 0;
}

