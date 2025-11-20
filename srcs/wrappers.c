/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:00:17 by alexafer          #+#    #+#             */
/*   Updated: 2025/11/20 14:19:35 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void *malloc(size_t size)
{
	return (ft_malloc(size));
}
void  free(void *p)				{
	return ;
	write(1, "test\n", 5);
	ft_free(p); }
void *realloc(void *p,size_t size)	{

	write(1, "test\n", 5);
	return ft_realloc(p,size); }
