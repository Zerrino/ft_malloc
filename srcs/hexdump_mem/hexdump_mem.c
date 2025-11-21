/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:40:52 by alexafer          #+#    #+#             */
/*   Updated: 2025/11/21 16:31:38 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

void	show_address(void *ptr)
{
	ft_printnbr_base((size_t)ptr, 16);
	ft_putstr_fd("  ", 1);
}

void	print_hexa(char *ptr, size_t size)
{
	char	base[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	size_t	i;

	i = 0;
	while (i < size)
	{
		ft_putchar_fd(base[(ptr[i] >> 4) & 0xf], 1);
		ft_putchar_fd(base[ptr[i] & 0xf], 1);
		if ((i % 16) == 7)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(" ", 1);
		i++;
	}
}

void	print_printable(char *ptr, size_t size)
{
	size_t	i;

	i = 0;
	ft_putstr_fd(" |", 1);
	while (i < size)
	{
		if (ft_isprint(ptr[i]))
			ft_putchar_fd(ptr[i], 1);
		else
			ft_putchar_fd('.', 1);
		i++;
	}
	ft_putchar_fd('|', 1);
}

void	hexdump_style(void *ptr, size_t size)
{
	int		flagstart;
	int		flag;
	char	last[16];
	size_t	i;

	i = 0;
	flagstart = 0;
	flag = 1;
	while (i < size)
	{
		if (i + 16 >= size)
			flag = 1;
		if (flag == 0 && ft_memcmp(last, ptr, 16) == 0)
		{
			if (flagstart == 1)
			{
				ft_putchar_fd('*', 1);
				ft_putstr_fd("\n", 1);
				flagstart = 0;
			}
		}
		else
		{
			show_address(ptr);
			print_hexa(ptr, 16);
			print_printable(ptr, 16);
			ft_putstr_fd("\n", 1);
			flagstart = 1;
		}
		ft_memcpy(last, ptr, 16);
		flag = 0;
		ptr = (void *)((size_t)ptr + 16);
		i += 16;
	}
}

void	hexdump_mem(void *ptr)
{
	size_t	total;
	t_zone	*zone;
	t_block	*block;

	pthread_mutex_lock(&g_lock);
	if (((size_t)ptr % 0x10) != 0 || !ptr)
		goto end;
	zone = g_global;
	while (zone)
	{
		total = (zone->size << 7) + (size_t)zone;
		if (zone->flag & 4)
			total = (size_t)zone + zone->size;
		if ((size_t)ptr > (size_t)zone && (size_t)ptr < total)
			break ;
		zone = zone->next;
	}
	if (!zone)
		goto end;
	block = (t_block *)(zone + 1);
	while (block && (size_t)(block + 1) != (size_t)ptr)
		block = block->next;
	if (!block)
		goto end;
	hexdump_style(ptr, block->size);
end:
	pthread_mutex_unlock(&g_lock);
}
