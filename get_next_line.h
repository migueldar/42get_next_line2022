/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 22:06:23 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/04/09 21:19:29 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

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

char	*get_next_line(int fd);
char	*str_calloc(size_t count, size_t size);
char	*my_realloc(char *str, int *realloc_counter);
void	free_and_null(t_read *red);

#endif