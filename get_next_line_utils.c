/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 09:57:18 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/06 11:54:47 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	buffer_update(int fd, t_buffer *buff)
{
	ssize_t	len;

	if (buff->buffer[buff->start])
		len = 1;
	else
	{
		buff->start = 0;
		len = read(fd, buff->buffer, BUFFER_SIZE);
		if (len >= 0)
			buff->buffer[len] = '\0';
		else
			buff->buffer[0] = '\0';
	}
	return (len);
}

t_list	*ft_strappend(t_list *last, char *src, ssize_t len)
{
	t_list	*dest;

	dest = malloc(sizeof(t_list));
	if (NULL == dest)
		return (NULL);
	dest->next = NULL;
	dest->prev = last;
	dest->string = malloc(sizeof(char) * (len + 1));
	if (NULL == dest->string)
	{
		free(dest);
		return (NULL);
	}
	ft_lst_strcpy(dest, src, len);
	dest->len = len;
	last->next = dest;
	return (dest);
}

void	ft_lst_strcpy(t_list *dest, char *src, ssize_t len)
{
	ssize_t	i;

	i = 0;
	while (i < len)
	{
		dest->string[i] = src[i];
		++i;
	}
	dest->string[i] = '\0';
}

void	list_join_util(t_list *line, char *str)
{
	ssize_t		len;
	int			i;

	len = 0;
	while (line)
	{
		i = 0;
		while (line->string[i])
		{
			str[len + i] = line->string[i];
			++i;
		}
		str[len + i] = '\0';
		len += i;
		line = line->next;
	}
}

ssize_t	get_list_len(t_list *lst)
{
	size_t	len;

	len = 0;
	while (lst)
	{
		len += lst->len;
		lst = lst->next;
	}
	return (len);
}
