/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:40:36 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/06 11:17:45 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	ssize_t	i;
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
	dest->len = len;
	last->next = dest;
	i = 0;
	while (i < len)
	{
		dest->string[i] = src[i];
		++i;
	}
	dest->string[i] = '\0';
	return (dest);
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

t_buffer	*init_buffer(t_buffer *buff)
{
	if (buff != NULL)
		return (buff);
	buff = malloc(sizeof(t_buffer));
	if (NULL == buff)
		return (NULL);
	buff->start = 0;
	buff->buffer[0] = '\0';
	return (buff);
}
