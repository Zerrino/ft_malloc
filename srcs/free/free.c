/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:16:35 by alexafer          #+#    #+#             */
/*   Updated: 2025/11/18 13:42:15 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"


void 	ft_free(void *ptr)
{
	t_zone	*zone;
	t_block	*block;
	size_t	total;

	printf("FREE CALLED AT : %p\n", ptr);
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
	block = (t_block *)(zone + 1);
	while (block && (size_t)block != (size_t)ptr)
	{
		block = block->next;
	}
	printf("Zone  : %p\n", zone);
	printf("Block : %p\n", block);
}
