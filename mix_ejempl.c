#include <stdio.h>
#include <pthread.h>

typedef struct s_data
{
	int	contador;
	pthread_mutex_t mutex;
} t_data;

void *suma(void *arg)
{
	t_data	*data;
	int i;

	i = 0;
	data = (t_data *)arg;
	while(i < 7)
	{
		pthread_mutex_lock(&data->mutex);
		data->contador++;
		pthread_mutex_unlock(&data->mutex);
		i++;
	}
	return(NULL);
}

int main(void)
{
	pthread_t hilo1;
	pthread_t hilo2;
	pthread_t hilo3;
	int error;

	t_data	data;

	data.contador = 0;

	if(pthread_mutex_init(&data.mutex, NULL) != 0)
		return(1);
	if(pthread_create(&hilo1, NULL, suma, &data) != 0)
	{
		pthread_mutex_destroy(&data.mutex);
		return(1);
	}
	if(pthread_create(&hilo2, NULL, suma, &data) != 0)
	{
		pthread_join(hilo1, NULL);
		pthread_mutex_destroy(&data.mutex);
		return(1);
	}
	if(pthread_create(&hilo3, NULL, suma, &data)!= 0)
	{
		pthread_join(hilo1, NULL);
		pthread_join(hilo2, NULL);
		pthread_mutex_destroy(&data.mutex);
		return(1);
	
	}

	error = 0;
	if(pthread_join(hilo1, NULL) != 0)
		error = 1;
	if(pthread_join(hilo2, NULL) != 0)
		error = 1;
	if(pthread_join(hilo3, NULL) != 0)
		error = 1;
	if(error == 0)
		printf("contador: %d\n", data.contador);
	if(pthread_mutex_destroy(&data.mutex) != 0)
		error = 1;
	

	return(error);
}
