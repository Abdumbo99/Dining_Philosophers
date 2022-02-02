#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pthread.h"

#define PHIL_NUM 5
#define RIGHT_NEIGHBOR(n) ((n + 4) % PHIL_NUM)
#define LEFT_NEIGHBOR(n) ((n + 1) % PHIL_NUM)
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define MAX_THINK_TIME 10
#define MAX_EATING_TIME 5

pthread_mutex_t mutex;
pthread_cond_t cond[PHIL_NUM];
int state[PHIL_NUM];
int thread_id[PHIL_NUM];


void test(int ind){
    if (state[RIGHT_NEIGHBOR(ind)] != EATING && state[LEFT_NEIGHBOR(ind)]!= EATING
        && state[ind] == HUNGRY){
        state[ind] = EATING;
        pthread_cond_signal(&cond[ind]);
    }
}

void pickUpFork(int ind){
    pthread_mutex_lock(&mutex);
    state[ind] = HUNGRY;
    test(ind);
    if (state[ind] != EATING)
        pthread_cond_wait(&cond[ind], &mutex);
    pthread_mutex_unlock(&mutex);
}

void putDownFork (int ind){
    pthread_mutex_lock(&mutex);
    state[ind] = THINKING;
    test(RIGHT_NEIGHBOR(ind));
    test(LEFT_NEIGHBOR(ind));
    pthread_mutex_unlock(&mutex);
}

int generateUniRandom (int highRange){
    double myRand = rand()/(1.0 + RAND_MAX); // uniform distribution
    return myRand * highRange + 1;
}

static void* philosiphize(void * indPtr){
    int duration;
    int *index = (int*) indPtr;
    int ind = * index;
    while (1) {
        srand(time(NULL) * ind);
        duration = generateUniRandom(MAX_THINK_TIME);
        printf("Philosopher number (%d) is thinking for (%d) seconds\n", ind ,duration);
        sleep(duration);
        duration = generateUniRandom(MAX_EATING_TIME);
        pickUpFork(ind);
        printf("Philosopher number (%d) is eating for (%d) seconds\n", ind ,duration);
        sleep(duration);
        putDownFork(ind);
    }
}

void init (int ind){
    state[ind] = THINKING;
    thread_id[ind] = ind;
    pthread_cond_init(&cond[ind],NULL);
}

int main() {
    pthread_t tid[PHIL_NUM];
    int i;
    for (i = 0; i < PHIL_NUM; i++){
        init(i);
    }
    pthread_mutex_init(&mutex, NULL);
    int ret = 0;
    for (i = 0; i < PHIL_NUM; i++){
        ret = pthread_create(&(tid[i]),NULL, philosiphize,(void*)&thread_id[i]);
        if (ret != 0) {
            printf("thread create failed \n");
        }
    }
    for (i = 0; i < PHIL_NUM; i++){
        ret = pthread_join((tid[i]), NULL);
        if (ret != 0) {
            printf("thread join failed \n");
        }
    }
    return 0;
}
