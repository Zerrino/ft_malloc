#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <pthread.h>
#define N_THREADS 4

#define M (1024 * 1024)

void *(*ft_malloc)(size_t size);
void (*ft_free)(void *ptr);
void (*show_alloc_mem)(void);

void *thread_worker(void *arg)
{
	(void)arg;
	char *p = ft_malloc(16 * M);
	ft_free(p);
	show_alloc_mem();

	return (NULL);
}

int	main()
{

    void	*handle = dlopen("./libft_malloc.so", RTLD_NOW);
    ft_malloc = dlsym(handle, "ft_malloc");
    ft_free = dlsym(handle, "ft_free");
    show_alloc_mem = dlsym(handle, "show_alloc_mem");
    char *addr[0x80];
    int i = 0;
    ft_malloc(1000);
    ft_malloc(5000);
    while (i < 0x80)
    {
        ft_malloc(1024);
        i++;
    }
    show_alloc_mem();


    return 0;
}

