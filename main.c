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
	char	*addr[0x80];
	int		i;

	i = 0;
	addr[0] = ft_malloc(715);
	printf("addr : %p\n", addr[0]);
	while (i < 715)
	{
		if (addr[0][i] != 0)
		{
			printf("test!\n");
		}
		addr[0][i] = 'a';
		i++;
	}
	show_alloc_mem();
	essaie = (t_block *)(test+1);
	return 0;
}
