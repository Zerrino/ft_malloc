#include <stdio.h>
#include "./includes/malloc.h"
#include <dlfcn.h>


int	main()
{
	t_zone	*test;
	t_block	*essaie;
	void	*handle = dlopen("./libft_malloc.so", RTLD_NOW);
	void	*(*ft_malloc)(size_t size) = dlsym(handle, "ft_malloc");
	void	(*ft_free)(void *ptr) = dlsym(handle, "ft_free");
	void	(*show_alloc_mem)(void) = dlsym(handle, "show_alloc_mem");
	char *addr[5];
	int		i;

	i = 0;
	while (i < 5)
	{
		addr[i] = ft_malloc(231);
		printf("addr %p s\n", addr[i]);
		i++;
	}
	ft_free(addr[3]);
	show_alloc_mem();
	ft_malloc(241);

	essaie = (t_block *)(test+1);
	show_alloc_mem();
	return 0;
}
