/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:12:08 by alexafer          #+#    #+#             */
/*   Updated: 2025/11/03 16:52:50 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"


void	show_alloc_mem(void)
{
	t_zone	*zone;
	t_block	*block;
	int		i;
	int		j;

	ft_putstr_fd(UGRN REDB "SHOW MEMORY:" CRESET "\n", 1);
	i = 0;
	zone = g_global;
	while (zone)
	{
		j = 0;
		ft_putstr_fd("  ", 1);
		ft_putnbr_fd(i, 1);
		ft_putstr_fd(". Size Zone : ",1);
		ft_putnbr_fd(zone->size, 1);
		ft_putstr_fd("\n",1);
		block = (t_block *)(zone + 1);
		while (block)
		{
			ft_putstr_fd("    ", 1);
			ft_putnbr_fd(i, 1);
			ft_putstr_fd(".", 1);
			ft_putnbr_fd(j, 1);
			ft_putstr_fd(". Size Block : ", 1);
			ft_putnbr_fd(block->size, 1);
			ft_putstr_fd("\n", 1);
			j++;
			block = block->next;
		}
		zone = zone->next;
		i++;
	}
}

