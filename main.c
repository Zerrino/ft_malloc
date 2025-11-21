#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <pthread.h>
#define N_THREADS 4

#define M (1024 * 1024)

void *(*ft_malloc)(size_t size);
void (*ft_free)(void *ptr);
void (*show_alloc_mem)(void);
void (*hexdump_mem)(void *ptr);

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
    hexdump_mem = dlsym(handle, "hexdump_mem");
    char *addr[0x80];
    int i = 0;
    while (i < 2)
    {
        addr[i] = ft_malloc(0x105);
        i++;
    }
    strcpy(addr[0], "salut comment ca va?");
    strcpy((addr[0]+70), "salut comment ca va?");
    hexdump_mem(addr[0]);
    //show_alloc_mem();


    return 0;
}

