#include <stdio.h>
#include <string.h>

#define DAYS 7
#define MAX_TASKS 3
#define MAX_LEN 100

struct Day {
    char dayName[20];
    char tasks[MAX_TASKS][MAX_LEN];
    int taskCount;
};

int main() {
    struct Day week[DAYS] = {
        {"Monday", {}, 0},
        {"Tuesday", {}, 0},
        {"Wednesday", {}, 0},
        {"Thursday", {}, 0},
        {"Friday", {}, 0},
        {"Saturday", {}, 0},
        {"Sunday", {}, 0}
    };

    int i, j;

    for(i = 0; i < DAYS; i++) {
        printf("\nEnter number of tasks for %s (max 3): ", week[i].dayName);
        scanf("%d", &week[i].taskCount);
        getchar();

        if(week[i].taskCount > MAX_TASKS)
            week[i].taskCount = MAX_TASKS;

        for(j = 0; j < week[i].taskCount; j++) {
            printf("Enter task %d: ", j + 1);
            fgets(week[i].tasks[j], MAX_LEN, stdin);

            week[i].tasks[j][strcspn(week[i].tasks[j], "\n")] = '\0';
        }
    }

    printf("\n===== Weekly Calendar =====\n");

    for(i = 0; i < DAYS; i++) {
        printf("\n%s:\n", week[i].dayName);

        if(week[i].taskCount == 0) {
            printf("No tasks\n");
        } else {
            for(j = 0; j < week[i].taskCount; j++) {
                printf("- %s\n", week[i].tasks[j]);
            }
        }
    }

    return 0;
}