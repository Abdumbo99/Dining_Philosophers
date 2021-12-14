#include <stdio.h>
#include "pthread.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define PHIL_NUM 5
#define RIGHT_NEIGHBOR(n) ((n + 4) % PHIL_NUM)
#define LEFT_NEIGHBOR(n) ((n + 1) % PHIL_NUM)
#define MAX_SLEEP_TIME 2
#define MAX_EATING_TIME 3
struct phil
{
    int state;
    int cond;
};

struct arg
{
    int t_index; /* the index of the created thread */
};

pthread_cond_t cond_vars[PHIL_NUM];
pthread_mutex_t mutex;

enum
{
    THINKING,
    HUNGRY,
    EATING
} state[PHIL_NUM];

void test(int index)
{
    if (state[RIGHT_NEIGHBOR(index)] != EATING && state[LEFT_NEIGHBOR(index)] != EATING && state[index] == HUNGRY)
    {
        state[index] = EATING;
        pthread_cond_signal(&cond_vars[index]);
    }
}

void pickupFork(int phil_no)
{
    pthread_mutex_lock(&mutex);

    state[phil_no] = HUNGRY;
    test(phil_no);

    while (state[phil_no] != EATING)
    {
        pthread_cond_wait(&cond_vars[phil_no], &mutex);
    }

    pthread_mutex_unlock(&mutex);
}

void dropFork(int phil_no)
{
    pthread_mutex_lock(&mutex);

    state[phil_no] = THINKING;
    // Signal left and right neighbors
    test(RIGHT_NEIGHBOR(phil_no));
    test(LEFT_NEIGHBOR(phil_no));

    pthread_mutex_unlock(&mutex);
}

static void *philosopher(void *arg_ptr)
{
    // time_t t;
    // srand((unsigned) time(&t));
    // int eat_time;
    // int think_time;

    int philosopher_no = ((struct arg *) arg_ptr)->t_index;

    while (1)
    {
        //eat_time = (int)((rand() % MAX_SLEEP_TIME) + 1);
        sleep(3);

        pickupFork(philosopher_no);

        printf("Philosopher %d is eating\n", philosopher_no);

        //think_time = (int)((rand() % MAX_EATING_TIME) + 1);
       sleep(3);

        printf("Philosopher %d is thinking\n", philosopher_no);
        dropFork(philosopher_no);
    }
    pthread_exit(NULL);
}

int main()
{

    pthread_t tids[PHIL_NUM];
    struct arg t_args[PHIL_NUM];
    int ret;

    for (int i = 0; i < PHIL_NUM; i++)
    {
        state[i] = THINKING;
        pthread_cond_init(&cond_vars[i], NULL);
    }

    pthread_mutex_init(&mutex, NULL);

    int i;

    for (i = 0; i < PHIL_NUM; i++)
    {
        t_args[i].t_index = i;
        pthread_create(&(tids[i]), 0, philosopher, (void *)&t_args[i]);
    }


    printf("main: waiting all threads to terminate\n");
	for (i = 0; i < PHIL_NUM; ++i) {
		ret = pthread_join(tids[i], NULL);
		if (ret != 0) {
			printf("thread join failed \n");
			exit(0);
		}
	}

    return 0;
}
