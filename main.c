#include <stdio.h>
#include "./includes/malloc.h"
#include <dlfcn.h>


int	main()
{
	void	*handle = dlopen("./libft_malloc.so", RTLD_NOW);
	void	*(*ft_malloc)(size_t size) = dlsym(handle, "ft_malloc");
	void	(*ft_free)(void *ptr) = dlsym(handle, "ft_free");
	void	(*show_alloc_mem)(void) = dlsym(handle, "show_alloc_mem");

	char *addr;
	addr = ft_malloc(5);
	addr = ft_malloc(18);
	addr = ft_malloc(48);
	addr = ft_malloc(0b1000000000000000000000000000000000000);
	printf("addr : %zu\n", (size_t)addr);
	return 0;
}
