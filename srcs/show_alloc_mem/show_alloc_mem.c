/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:12:08 by alexafer          #+#    #+#             */
/*   Updated: 2025/11/18 12:45:01 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

static void	ft_printnbr_base(size_t nbr, size_t base)
{
	if (base <= (nbr))
		ft_printnbr_base((nbr / base), base);
	ft_putchar_fd((nbr % base) + '0' + (39 * (9 < (nbr % base))), 1);
}

static int	calculate_block(t_zone *zone, t_block *block, t_block *l_block)
{
	size_t		size;
	size_t		alignment;
	size_t		max_size;

	max_size = (size_t)zone + (SMALL_SIZE * SMALL_NUMBER);
	if (!l_block)
	{
		if (block->size <= 1024)
			max_size = (size_t)zone + (TINY_SIZE * TINY_NUMBER);
	}
	else
	{
		if (l_block->size <= 1024)
			max_size = (size_t)zone + (TINY_SIZE * TINY_NUMBER);
	}
	if (max_size < (size_t)block + block->size + sizeof(t_block) + sizeof(t_block))
		return (0);
	alignment = 2 * sizeof(size_t);
	if ((((unsigned long) (block)) % alignment) != 0)
		return (0);
	if (!l_block)
		return (1);
	size = (size_t)block - (size_t)l_block;
	return (size - (l_block->size + sizeof(t_block)) == 0);
}

void	show_alloc_mem(void)
{
	t_zone	*zone;
	t_zone	*l_zone;
	t_block	*block;
	t_block	*l_block;
	int		i;
	int		j;

	ft_putstr_fd(UGRN REDB "                    SHOW ALLOC MEMORY                    " CRESET "\n", 1);
	i = 0;
	l_zone = 0;
	zone = g_global;
	while (zone)
	{
		j = 0;
		ft_putstr_fd(UWHT "|  ", 1);
		ft_putnbr_fd(i, 1);
		ft_putstr_fd(". Zone : ",1);
		ft_putnbr_fd(zone->size, 1);
		ft_putstr_fd(" | 0x",1);
		ft_printnbr_base(zone->flag, 16);
		ft_putstr_fd(" | 0x",1);
		ft_printnbr_base((size_t)zone, 16);
		ft_putstr_fd(" - 0x",1);
		ft_printnbr_base((size_t)zone->numb, 16);
		ft_putstr_fd(" |\n" CRESET,1);
		l_block = 0;
		block = (t_block *)(zone + 1);
		while (block && PRINT_BLOCK)
		{
			ft_putstr_fd("    ", 1);
			ft_putnbr_fd(i, 1);
			ft_putstr_fd(".", 1);
			ft_putnbr_fd(j, 1);
			ft_putstr_fd(". Block : ", 1);
			ft_putnbr_fd(block->size, 1);
			ft_putstr_fd("\t\t- ",1);
			if (calculate_block(zone, block, l_block))
				ft_putstr_fd(BGRN, 1);
			else
				ft_putstr_fd(BRED, 1);
			ft_putstr_fd("0x",1);
			ft_printnbr_base((size_t)block, 16);
			ft_putstr_fd(CRESET "\n", 1);
			j++;
			l_block = block;
			block = block->next;
		}
		l_zone = zone;
		zone = zone->next;
		i++;
	}
}

