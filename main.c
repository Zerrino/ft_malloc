#include <stdio.h>
#include "./includes/malloc.h"
#include <dlfcn.h>
#include <string.h>

#define M (1024 * 1024)

int	main()
{
	t_zone	*test;
	t_block	*essaie;
	void	*handle = dlopen("./libft_malloc.so", RTLD_NOW);
	void	*(*ft_malloc)(size_t size) = dlsym(handle, "ft_malloc");
	void	(*ft_free)(void *ptr) = dlsym(handle, "ft_free");
	void	(*show_alloc_mem)(void) = dlsym(handle, "show_alloc_mem");
	char	*addr[0x80];
	int		i;

	i = 0;
	addr[0] = ft_malloc(16*M);
	printf("addr : %p\n", addr[0]);
	show_alloc_mem();
	addr[1] = ft_malloc(16*M);
	return 0;
}
