/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 06:54:33 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/04/10 06:43:46 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	get_next_size(int fd, t_read *red)
{
	int		chars_read;

	if (red->already_read)
		free(red->already_read);
	red->already_read = str_calloc(BUFFER_SIZE + 1, 1);
	if (!(red->already_read))
		return (-1);
	chars_read = read(fd, red->already_read, BUFFER_SIZE);
	if (chars_read < 0)
	{
		free_and_null(red);
		return (-1);
	}
	if (chars_read == 0)
	{
		free_and_null(red);
		return (-2);
	}
	return (chars_read);
}

//0 if smt wrong
static int	checks_and_assignation(t_read *red, char **ret, int fd)
{
	if (!(red->already_read))
	{
		red->n_of_chars = get_next_size(fd, red);
		red->counter = 0;
		if (red->n_of_chars < BUFFER_SIZE)
			red->is_done = 1;
		if (red->n_of_chars <= -1)
			return (0);
	}
	*ret = str_calloc(BUFFER_SIZE + 1, 1);
	if (!(*ret))
	{
		free_and_null(red);
		return (0);
	}
	return (1);
}

//returns 0 if 0 has to be returned, 1 if 1 has to be returned, 2 else
static int	norminette_if(t_read *red, char **ret, int *realloc_counter, int fd)
{
	if (red->is_done)
	{
		free_and_null(red);
		return (1);
	}
	red->n_of_chars = get_next_size(fd, red);
	if (red->n_of_chars == -1)
	{
		free(*ret);
		return (0);
	}
	if (red->n_of_chars < BUFFER_SIZE)
		red->is_done = 1;
	if (red->n_of_chars == -2)
		return (1);
	red->counter = 0;
	*ret = my_realloc(*ret, realloc_counter);
	return (2);
}

//returns 0 if NULL has to be returned, 1 if ret has to be returned, 2 else
static int	norminette_while(t_read *red, char **ret, int *ret_counter, int fd)
{
	int	realloc_counter;
	int	n_i;

	realloc_counter = 1;
	while (red->already_read[red->counter] != '\n')
	{
		if (red->counter >= red->n_of_chars)
		{
			n_i = norminette_if(red, ret, &realloc_counter, fd);
			if (!n_i)
				return (0);
			if (n_i == 1)
				return (1);
		}
		else
			(*ret)[(*ret_counter)++] = red->already_read[red->counter++];
	}
	return (2);
}

char	*get_next_line(int fd)
{
	static t_read	red;
	char			*ret;
	int				ret_counter;
	int				n_w;

	if (!checks_and_assignation(&red, &ret, fd))
		return (NULL);
	ret_counter = 0;
	n_w = norminette_while(&red, &ret, &ret_counter, fd);
	if (!n_w)
		return (NULL);
	if (n_w == 1)
		return (ret);
	ret[ret_counter] = '\n';
	if (++red.counter == red.n_of_chars)
		free_and_null(&red);
	return (ret);
}
