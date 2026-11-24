#include <pthread.h>
#include <stdio.h>

typedef struct s_document
{
	int ready;
	pthread_mutex_t mutex;
	pthread_cond_t cond;

} t_document;

void *making_the_document(void *arg)
{
	t_document *document;

	document = (t_document *)arg;
	pthread_mutex_lock(&document->mutex);
	document->ready = 1;
	printf("document ready to print\n");
	pthread_cond_broadcast(&document->cond);
	pthread_mutex_unlock(&document->mutex);
	return(NULL);

}

void *printing_document(void *arg)
{
	t_document	*document;

	document = (t_document *)arg;
	pthread_mutex_lock(&document->mutex);

	while(document->ready == 0)
		pthread_cond_wait(&document->cond, &document->mutex);

	printf("printing...\n");
	pthread_mutex_unlock(&document->mutex);

	return(NULL);
}


int main(void)
{
	t_document	document;
	pthread_t	preparador;
	pthread_t	impresor;
	pthread_t	impresor2;
	int error;

	document.ready = 0;
	if(pthread_mutex_init(&document.mutex, NULL) != 0)
		return(1);
	if(pthread_cond_init(&document.cond, NULL) != 0)
	{
		pthread_mutex_destroy(&document.mutex);
		return(1);
	}
	if(pthread_create(&preparador, NULL, making_the_document, &document) != 0)
	{	
		pthread_mutex_destroy(&document.mutex);
		pthread_cond_destroy(&document.cond);
		return(1);
	}
	if(pthread_create(&impresor, NULL, printing_document, &document) != 0)
	{
		pthread_join(preparador, NULL);
		pthread_mutex_destroy(&document.mutex);
		pthread_cond_destroy(&document.cond);
		return(1);
	
	}
	if(pthread_create(&impresor2, NULL, printing_document, &document) != 0)
    {
        pthread_join(preparador, NULL);
        pthread_join(impresor, NULL);
        pthread_mutex_destroy(&document.mutex);
        pthread_cond_destroy(&document.cond);
        return(1);

    }


	error = 0;

	if(pthread_join(preparador, NULL) != 0)
		error = 1;
	if(pthread_join(impresor, NULL) != 0)
		error = 1;
	if(pthread_join(impresor2, NULL) != 0)
		error = 1;
	if(pthread_mutex_destroy(&document.mutex)!= 0)
		error = 1;
	if(pthread_cond_destroy(&document.cond)!= 0)
        error = 1;
	
	return(error);

}
