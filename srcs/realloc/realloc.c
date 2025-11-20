/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerrino <zerrino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:52:08 by alexafer          #+#    #+#             */
/*   Updated: 2025/11/20 21:13:00 by zerrino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = ft_malloc(size);
	if (((size_t)ptr % 0x10) != 0 || !ptr)
		return (new_ptr);
	ft_memcpy(new_ptr, ptr, ((t_block *)(ptr - 16))->size);
	ft_free(ptr);
	return (new_ptr);
}

