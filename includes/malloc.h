/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:35:46 by alexafer          #+#    #+#             */
/*   Updated: 2025/10/23 19:06:21 by alexafer         ###   ########.fr       */
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

# define n		1024
# define N		256
# define m		4096
# define M		128

typedef struct s_block
{
	uint32_t		special;  //4  8
	uint16_t		nb_used;  //2
	uint16_t		size;    // 2     16
	struct s_block	*next;   // 8
	struct s_block	*prev;	 // 8  16     32
	struct s_zone	*zone;  //  8
} t_block;

typedef struct s_zone
{
	int				size;
	int				is_used;
	struct s_zone	*next;
}	t_zone;



extern pthread_mutex_t g_lock;
extern t_block	*g_block;


void	ft_free(void *ptr);
void	*ft_malloc(size_t size);
void	*ft_realloc(void *ptr, size_t size);
t_block	*returnFreeBlock(void *ptr);
void	show_alloc_mem();
void	show_alloc_mem_block(char *ptr);
void	show_alloc_mem_hexa(char *ptr);


void *malloc(size_t)			__attribute__((visibility("default")));
void  free(void *)				__attribute__((visibility("default")));
void *realloc(void *, size_t)	__attribute__((visibility("default")));

#endif
