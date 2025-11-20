/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerrino <zerrino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:16:35 by alexafer          #+#    #+#             */
/*   Updated: 2025/11/20 20:54:03 by zerrino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

void 	ft_free(void *ptr)
{
	t_zone	*zone;
	t_zone	*l_zone;
	t_block	*block;
	t_block	*tmp;
	t_block	*l_block;
	size_t	total;


	pthread_mutex_lock(&g_lock);
	if (((size_t)ptr % 0x10) != 0 || !ptr)
		goto end;
	zone = g_global;
	l_zone = 0;
	while (zone)
	{
		if ((size_t)(zone + 1) == (size_t)ptr && (zone->flag & 0x4))
		{
			if (!l_zone)
				g_global = zone->next;
			else
				l_zone->next = zone->next;
			munmap(zone, zone->size);
			goto end;
		}
		total = (zone->size << 7) + (size_t)zone;
		if ((size_t)ptr > (size_t)zone && (size_t)ptr < total)
			break ;
		l_zone = zone;
		zone = zone->next;
	}
	if (!zone)
		goto end;
	block = (t_block *)(zone + 1);
	l_block = 0;
	while (block && (size_t)(block + 1) != (size_t)ptr)
	{
		l_block = block;
		block = block->next;
	}
	if (!block)
		goto end;
	if (zone->flag > ((size_t)block | (zone->flag & 0xf)))
		zone->flag = (size_t)block | (zone->flag & 0xf);
	zone->flag &= ~(1 << 1);
	ft_bzero(ptr, block->size);
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
	block = (t_block *)(zone + 1);

	if (block->size == 0 && block->next == 0 && !(zone->flag & 1))
	{
		if (!l_zone)
			g_global = zone->next;
		else
			l_zone->next = zone->next;
		munmap((void *)zone, zone->size << 7);
	}
end:
	pthread_mutex_unlock(&g_lock);
}
