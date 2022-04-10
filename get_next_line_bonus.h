/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 20:24:26 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/04/10 06:43:29 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_read
{
	int		counter;
	char	*already_read;
	int		is_done;
	int		n_of_chars;
}	t_read;

typedef struct s_l_read
{
	t_read			content;
	int				fd;
	struct s_l_read	*next;
}	t_l_read;

char		*get_next_line(int fd);
void		*ft_calloc(size_t count, size_t size);
char		*my_realloc(char *str, int *realloc_counter);
void		free_and_null(t_read *red);
t_l_read	*find_or_add(t_l_read **list, int fd);
void		free_list_elem(t_l_read **elem, t_l_read **first);
#endif