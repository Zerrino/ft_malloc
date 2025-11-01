/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:35:46 by alexafer          #+#    #+#             */
/*   Updated: 2025/10/30 15:05:52 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "../libft/libft.h"
# include <sys/resource.h>
# include <sys/mman.h>
# include <stdio.h>
# include <stdint.h>
# include <pthread.h>

# define n		0x400
# define N		0x80
# define m		0x4000
# define M		0x80

typedef struct s_block
{
	struct s_block	*next;
	uint64_t		size;
} t_block;

typedef struct s_zone
{
	struct s_zone	*next;
	uint64_t		size;
}	t_zone;



extern pthread_mutex_t g_lock;
extern t_block	*g_block;

void	ft_free(void *ptr);


void	*ft_malloc(size_t size);


void	*ft_realloc(void *ptr, size_t size);


void	show_alloc_mem();


void *malloc(size_t)			__attribute__((visibility("default")));
void  free(void *)				__attribute__((visibility("default")));
void *realloc(void *, size_t)	__attribute__((visibility("default")));

#endif
