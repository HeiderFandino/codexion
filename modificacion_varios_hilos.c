#include <stdio.h>
#include <pthread.h>

void *trabajador(void *arg)
{
	int *productos;

	productos = (int *)arg;
	printf("trabajador: %d productos asignados\n", (*productos * 3));
	return(NULL);
}

int main(void)
{
	pthread_t hilo1;
	pthread_t hilo2;
	int cantidad1;
	int cantidad2;
	int error;

	cantidad1 = 15;
	cantidad2 = 30;

	if(pthread_create(&hilo1, NULL, trabajador, &cantidad1) != 0)
		return(1);

	if(pthread_create(&hilo2, NULL, trabajador, &cantidad2) != 0)
	{	
		pthread_join(hilo1, NULL);
		return(1);
	}

	error = 0;
	if(pthread_join(hilo1, NULL) != 0)
		error = 1;
	if(pthread_join(hilo2, NULL) != 0)
		error = 1;

	return(error);



}
