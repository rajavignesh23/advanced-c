#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

int N;

void sigintHandler(int sig)
{
    printf("\nSIGINT (Ctrl+C) received. Program continues...\n");
}

int isPrime(int n)
{
    if(n < 2)
        return 0;

    for(int i = 2; i * i <= n; i++)
    {
        if(n % i == 0)
            return 0;
    }

    return 1;
}

void *primeSumThread(void *arg)
{
    time_t startTime, endTime;
    time(&startTime);

    long long sum = 0;
    int count = 0;
    int num = 2;

    while(count < N)
    {
        if(isPrime(num))
        {
            sum += num;
            count++;
        }
        num++;
    }

    time(&endTime);

    printf("\n[Thread A]\n");
    printf("Sum of first %d prime numbers = %lld\n", N, sum);
    printf("Execution Time = %.0f seconds\n",
           difftime(endTime, startTime));

    pthread_exit(NULL);
}

void *thread1(void *arg)
{
    time_t startTime, endTime;
    time(&startTime);

    while(difftime(time(NULL), startTime) < 100)
    {
        printf("[Thread B] Thread 1 running\n");
        sleep(2);
    }

    time(&endTime);

    printf("[Thread B] Finished\n");
    printf("[Thread B] Execution Time = %.0f seconds\n",
           difftime(endTime, startTime));

    pthread_exit(NULL);
}

void *thread2(void *arg)
{
    time_t startTime, endTime;
    time(&startTime);

    while(difftime(time(NULL), startTime) < 100)
    {
        printf("[Thread C] Thread 2 running\n");
        sleep(3);
    }

    time(&endTime);

    printf("[Thread C] Finished\n");
    printf("[Thread C] Execution Time = %.0f seconds\n",
           difftime(endTime, startTime));

    pthread_exit(NULL);
}

int main()
{
    pthread_t A, B, C;

    signal(SIGINT, sigintHandler);

    time_t programStart, programEnd;
    time(&programStart);

    printf("===== Flow of Execution =====\n");
    printf("1. Register SIGINT Handler\n");
    printf("2. Read N\n");
    printf("3. Create Thread A\n");
    printf("4. Create Thread B\n");
    printf("5. Create Thread C\n");
    printf("6. Execute Threads Concurrently\n");
    printf("7. Wait for Threads to Finish\n\n");

    printf("Enter N: ");
    scanf("%d", &N);

    pthread_create(&A, NULL, primeSumThread, NULL);
    pthread_create(&B, NULL, thread1, NULL);
    pthread_create(&C, NULL, thread2, NULL);

    pthread_join(A, NULL);
    pthread_join(B, NULL);
    pthread_join(C, NULL);

    time(&programEnd);

    printf("\nAll Threads Completed\n");
    printf("Total Program Execution Time = %.0f seconds\n",
           difftime(programEnd, programStart));

    return 0;
}
