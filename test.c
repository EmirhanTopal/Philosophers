#include "philosophers.h"

int aaa;

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

int main()
{
	printf("%ld\n", get_time());
	usleep(1000);
	printf("%ld", get_time());
    return 0;
}