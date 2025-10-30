/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:00:10 by alexafer          #+#    #+#             */
/*   Updated: 2025/06/02 15:04:26 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASM_H
# define LIBASM_H

# include <sys/types.h>
# include <errno.h>
# include <stdlib.h>

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;

ssize_t	ft_write(int x, const void *y, size_t z);
ssize_t	ft_read(int x, void *y, size_t z);
size_t	ft_strlen(const char *x);
char	*ft_strcpy(char *x, const char *y);
char	*ft_strdup(const char *x);
int		ft_strcmp(const char *x, const char *y);

/******************BONUS*****************/
int		ft_atoi_base(char *x, char *y);
int		ft_list_size(t_list *x);
void	ft_list_push_front(t_list **x, void *y);
void	ft_list_sort(t_list **x, int (*cmp)());
t_list	*ft_create_elem(void *data);
void	ft_list_remove_if(t_list **begin_list,
			void *data_ref, int (*cmp)(), void (*free_fct)(void *));

#endif