#include <stdio.h>
#include "pthread.h"

#define PHIL_NUM 5
#define RIGHT_NEIGHBOR(n) ((n + 4) % PHIL_NUM)
#define LEFT_NEIGHBOR(n) ((n + 1) % PHIL_NUM)
#define MAX_SLEEP_TIME 5
#define MAX_EATING_TIME 10


int main() {
    int i =2;
    printf("%d\n",RIGHT_NEIGHBOR(i));
    printf("%d\n",LEFT_NEIGHBOR(i));
    printf("%d\n",RIGHT_NEIGHBOR(4));
    printf("%d\n",LEFT_NEIGHBOR(4));
    printf("%d\n",RIGHT_NEIGHBOR(0));
    printf("%d\n",LEFT_NEIGHBOR(0));
    return 0;
}
