/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:52:08 by alexafer          #+#    #+#             */
/*   Updated: 2025/11/21 15:39:41 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = ft_malloc(size);
	if (((size_t)ptr % 0x10) != 0 || !ptr)
		return (new_ptr);
	if ((((t_block *)ptr) - 1)->size < size)
		ft_memcpy(new_ptr, ptr, (((t_block *)ptr) - 1)->size);
	else
		ft_memcpy(new_ptr, ptr, size);
	ft_free(ptr);
	return (new_ptr);
}

