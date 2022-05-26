#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>


void* timerA(void* any){
    time_t t;
    struct tm tm;

    while (1) {
        t = time(NULL);
        tm = *localtime(&t);

        printf("timerA: %d-%d-%d %d:%d:%d\n", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        sleep(2);
    }
}

void* timerB(void* any){
    time_t t;
    struct tm tm;

    while (1) {
        t = time(NULL);
        tm = *localtime(&t);

        printf("timerB: %d-%d-%d %d:%d:%d\n", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        sleep(5);
    }
}

int main(int argc, char* argv[]){

	int i;

	// create two pthreads
	pthread_t threads[2];
	pthread_create (&threads[0], NULL, timerA, NULL);
	pthread_create (&threads[1], NULL, timerB, NULL);

	for (i=0; i< 2; i++){
		pthread_join(threads[i], NULL);
	}

	return 0;
}