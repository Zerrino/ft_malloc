#include <stdio.h>
#include "./includes/malloc.h"
#include <dlfcn.h>


int	main()
{
	t_block	*test;
	void	*handle = dlopen("./libft_malloc.so", RTLD_NOW);
	void	*(*ft_malloc)(size_t size) = dlsym(handle, "ft_malloc");
	void	(*ft_free)(void *ptr) = dlsym(handle, "ft_free");
	void	(*show_alloc_mem)(void) = dlsym(handle, "show_alloc_mem");

	char *addr;
	addr = ft_malloc(50);
	test = ft_malloc(1800);
	test = ft_malloc(100);
	test = ft_malloc(100);
	test = ft_malloc(1800);
	test = ft_malloc(100);
	printf("addr : %p\n", (void *)test);
	printf("addr next : %p\n", (void *)test->next);
	printf("size : %d\n", test->size);
	printf("next size : %d\n", test->next->size);
	return 0;
}
