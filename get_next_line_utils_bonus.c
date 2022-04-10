/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 20:24:15 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/04/10 06:42:02 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*ret;
	unsigned long	c;

	c = 0;
	ret = malloc(count * size);
	if (ret == NULL)
		return (NULL);
	while (c < count)
		((char *)ret)[c++] = 0;
	return (ret);
}

//realoca
char	*my_realloc(char *str, int *realloc_counter)
{
	char	*ret;
	int		counter;

	ret = ft_calloc(BUFFER_SIZE * ++(*realloc_counter) + 1, 1);
	if (!ret)
		return (NULL);
	counter = 0;
	while (str[counter])
	{
		ret[counter] = str[counter];
		counter++;
	}
	free(str);
	return (ret);
}

void	free_and_null(t_read *red)
{
	free(red->already_read);
	red->already_read = NULL;
}

//recieves memory direction of pointer to element of the list
//returns pointer to the needed element
//if it cant find the element it adds it to the list
t_l_read	*find_or_add(t_l_read **list, int fd)
{
	t_l_read	*ret;

	ret = *list;
	while (ret && ret->fd != fd)
	{	
		ret = ret->next;
		if (ret == *list)
			ret = NULL;
	}
	if (!ret)
	{
		ret = ft_calloc(sizeof(t_l_read), 1);
		ret->fd = fd;
		if (!(*list))
		{
			*list = ret;
			ret->next = ret;
		}
		else
		{
			ret->next = (*list)->next;
			(*list)->next = ret;
		}
	}
	return (ret);
}

void	free_list_elem(t_l_read **elem, t_l_read **first)
{
	t_l_read	*wanna_free;

	if ((*first)->next == (*first))
	{
		free(*elem);
		*first = NULL;
		return ;
	}
	wanna_free = (*elem)->next;
	(*elem)->content = ((*elem)->next)->content;
	(*elem)->fd = ((*elem)->next)->fd;
	(*elem)->next = ((*elem)->next)->next;
	*first = *elem;
	free(wanna_free);
}
