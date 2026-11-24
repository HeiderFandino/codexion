#include <pthread.h>
#include <stdio.h>

typedef struct s_data
{
    int             contador;
    pthread_mutex_t mutex;
}   t_data;

void *incrementar(void *arg)
{
    t_data  *data;
    int     i;

    data = (t_data *)arg;
    i = 0;
    while (i < 1000)
    {
        pthread_mutex_lock(&data->mutex);
        data->contador++;
        pthread_mutex_unlock(&data->mutex);
        i++;
    }
    return (NULL);
}

int main(void)
{
    t_data      data;
    pthread_t   hilos[2];
    int         creados;
    int         i;
    int         error;

    data.contador = 0;
    if (pthread_mutex_init(&data.mutex, NULL) != 0)
        return (1);
    creados = 0;
    error = 0;
    while (creados < 2)
    {
        if (pthread_create(&hilos[creados], NULL,
                incrementar, &data) != 0)
        {
            error = 1;
            break;
        }
        creados++;
    }
    i = 0;
    while (i < creados)
    {
        if (pthread_join(hilos[i], NULL) != 0)
            error = 1;
        i++;
    }
    if (error == 0)
        printf("Contador final: %d\n", data.contador);
    if (pthread_mutex_destroy(&data.mutex) != 0)
        error = 1;
    return (error);
}
