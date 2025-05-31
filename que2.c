#include <stdio.h>
struct Time {
    int hrs, min, sec;
};

void addTime(struct Time t1, struct Time t2, struct Time *result) {
    result->sec = t1.sec + t2.sec;
    result->min = t1.min + t2.min + (result->sec / 60);
    result->hrs = t1.hrs + t2.hrs + (result->min / 60);
    result->sec %= 60;
    result->min %= 60;
}

int timeToSeconds(struct Time t) {
    return t.hrs * 3600 + t.min * 60 + t.sec;
}

int main() {
    struct Time t1, t2, sum;
    printf("Enter Time 1 (hrs min sec): ");
    scanf("%d %d %d", &t1.hrs, &t1.min, &t1.sec);
    printf("Enter Time 2 (hrs min sec): ");
    scanf("%d %d %d", &t2.hrs, &t2.min, &t2.sec);

    addTime(t1, t2, &sum);
    printf("\nAdded Time: %02d:%02d:%02d\n", sum.hrs, sum.min, sum.sec);

    printf("Time 1 in seconds: %d\n", timeToSeconds(t1));
    return 0;
}

