#include <stdio.h>
#include "pthread.h"

#define PHIL_NUM 5
#define RIGHT_NEIGHBOR(n) ((n + 4) % PHIL_NUM)
#define LEFT_NEIGHBOR(n) ((n + 1) % PHIL_NUM)
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define MAX_SLEEP_TIME 5
#define MAX_EATING_TIME 10
struct phil {
    int state;
    int cond;
};


int main() {
    int count = 0;
    pthread_mutex_lock(&count);
    pthread_mutex_unlock(&count);
    printf("The following lines are to make sure the macros work as intended\n");
    int i =2;
    printf("%d\n",RIGHT_NEIGHBOR(i));
    printf("%d\n",LEFT_NEIGHBOR(i));
    printf("%d\n",RIGHT_NEIGHBOR(4));
    printf("%d\n",LEFT_NEIGHBOR(4));
    printf("%d\n",RIGHT_NEIGHBOR(0));
    printf("%d\n",LEFT_NEIGHBOR(0));
    return 0;
}
