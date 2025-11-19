/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:16:35 by alexafer          #+#    #+#             */
/*   Updated: 2025/11/19 18:24:10 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"


void 	ft_free(void *ptr)
{
	t_zone	*zone;
	t_block	*block;
	t_block	*tmp;
	t_block	*l_block;
	size_t	total;


	if (((size_t)ptr % 0x10) != 0)
		return ;
	zone = g_global;
	while (zone)
	{
		total = (zone->size << 7) + (size_t)zone;
		if ((size_t)ptr > (size_t)zone && (size_t)ptr < total)
			break ;
		zone = zone->next;
	}
	if (!zone)
		return ;
	block = (t_block *)(zone + 1);
	l_block = 0;
	while (block && (size_t)block != (size_t)ptr)
	{
		l_block = block;
		block = block->next;
	}
	if (!block)
		return ;
	if (zone->flag > ((size_t)block | (zone->flag & 0xf)))
		zone->flag = (size_t)block | (zone->flag & 0xf);
	zone->flag &= ~(1 << 1);
	block->size = 0;
	if (block->next && block->next->size == 0)
	{
		tmp = block->next->next;
		block->next->next = 0;
		block->next = tmp;
	}
	if (l_block && l_block->size == 0)
	{
		l_block->next = block->next;
		block->next = 0;
	}
}
