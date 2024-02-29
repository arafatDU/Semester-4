#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define N 3

void multiply_row(int row, int (*matrix1)[N], int (*matrix2)[N], int (*result)[N]) {
    for (int j = 0; j < N; j++) {
        int sum = 0;
        for (int k = 0; k < N; k++) {
            sum += matrix1[row][k] * matrix2[k][j];
        }
        result[row][j] = sum;
    }
}

int main() {
    int matrix1[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int matrix2[N][N] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    
    
    int key = ftok("shmfile",65);
    int shmid = shmget(key,sizeof(int[N][N]),0666|IPC_CREAT);
    int (*result)[N] = shmat(shmid,(void*)0,0);

    for (int i = 0; i < N; i++) {
        int pid = fork();
        if (pid == 0) {
            multiply_row(i, matrix1, matrix2, result);
            exit(0); 
        } else if (pid < 0) {
            printf("Fork failed\n");
            return 1;
        }
    }


    for (int i = 0; i < N; i++) {
        wait(NULL);
    }


    printf("Result Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    
    
    shmdt(result);
    shmctl(shmid,IPC_RMID,NULL);

    return 0;
}
