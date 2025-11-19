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
	char *addr[0x80];
	int		i;

	i = 0;
	while (i < 0x80)
	{
		addr[i] = ft_malloc(1024);
		i++;
	}
	i = 0;
	while (i < 0x80)
	{
		ft_free(addr[i]);
		i++;
	}
	ft_malloc(1024);
	show_alloc_mem();
	essaie = (t_block *)(test+1);
	return 0;
}
