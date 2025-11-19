/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:52:08 by alexafer          #+#    #+#             */
/*   Updated: 2025/11/19 20:03:00 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void		*new_alloc;
	uint64_t	size_block;

	new_alloc = 0;
	if (!ptr)
		return (ft_malloc(size));
	if (!size)
	{
		ft_free(ptr);
		return (0);
	}
	new_alloc = ft_malloc(size);
	if (!new_alloc)
		return (0);
	size_block = ((t_block *)(ptr - sizeof(t_block)))->size;
	if (size_block > size)
		ft_memcpy(new_alloc, ptr, size);
	else
		ft_memcpy(new_alloc, ptr, size_block);
	return (new_alloc);
}

