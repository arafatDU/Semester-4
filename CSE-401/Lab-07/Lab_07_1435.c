#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define NUM_THREADS 10
#define POINTS_PER_THREAD 100

int c = 0, s = 0;

void *floatRandom(void *arg) {
    int tid = *((int *)arg); 
    int seed = time(NULL) + tid; 

    srand(seed);

    for (int i = 0; i < POINTS_PER_THREAD; i++) {
        float x = ((float)rand() / RAND_MAX) * 2 - 1;
        float y = ((float)rand() / RAND_MAX) * 2 - 1;
        float dis = sqrt(x * x + y * y);

        if (dis >= 1.0) {
            s++;
        } else {
            c++;
        }

        printf("%f %f %f\n", x, y, dis);
    }

    return NULL;
}

int main() {
    pthread_t tid[NUM_THREADS];

    int thread_ids[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&tid[i], NULL, floatRandom, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }

    printf("%d %d %f\n", s, c, 4 * ((float)c / (float)(c + s)));

    return 0;
}
