#include "philosophers.h"
#include <unistd.h>

int aaa = 0;

typedef struct {
	int *value;
    pthread_mutex_t *mutex;
} ThreadData_t;


void	*test_function(void *threadDataArg)
{
	int b;
	
	b = aaa;
	ThreadData_t *thread_t = (ThreadData_t *) threadDataArg;
	pthread_mutex_lock(thread_t->mutex);
	for (size_t i = 0; i < 1000000; i++)
	{
		b += *(thread_t->value);
	}
	pthread_mutex_unlock(thread_t->mutex);
	aaa += b;
}

ThreadData_t thread_data_init(int *value, pthread_mutex_t *mutex)
{
	ThreadData_t td = 
	{ 
		td.value = value,
		td.mutex = mutex
	};
	return td;
}

int	main(int argc, char **argv)
{
    pthread_t t1;
    pthread_t t2;
	pthread_mutex_t mutex;
	int c = 2;
	int d = 4;

	if (argc == 6)
	{
		pthread_mutex_init(&mutex, NULL);
		ThreadData_t td1 = thread_data_init(&c, &mutex);
		ThreadData_t td2 = thread_data_init(&d, &mutex);
	
		pthread_create(&t1, NULL, test_function, &td1);
		pthread_create(&t2, NULL, test_function, &td2);
		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
		printf("%d\n", aaa);
		pthread_mutex_destroy(&mutex);
	}
	else
		return 0;
	
	
}
