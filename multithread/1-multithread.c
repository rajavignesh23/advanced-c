#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int N;

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

    printf("\nSum of first %d prime numbers = %lld\n", N, sum);

    return NULL;
}

void *thread1(void *arg)
{
    time_t start = time(NULL);

    while(time(NULL) - start < 100)
    {
        printf("Thread 1 running\n");
        sleep(2);
    }

    return NULL;
}

void *thread2(void *arg)
{
    time_t start = time(NULL);

    while(time(NULL) - start < 100)
    {
        printf("Thread 2 running\n");
        sleep(3);
    }

    return NULL;
}

int main()
{
    pthread_t A, B, C;

    printf("Enter N: ");
    scanf("%d", &N);

    pthread_create(&A, NULL, primeSumThread, NULL);
    pthread_create(&B, NULL, thread1, NULL);
    pthread_create(&C, NULL, thread2, NULL);

    pthread_join(A, NULL);
    pthread_join(B, NULL);
    pthread_join(C, NULL);

    printf("\nAll threads completed.\n");

    return 0;
}
