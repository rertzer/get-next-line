/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:36:06 by rertzer           #+#    #+#             */
/*   Updated: 2024/04/06 11:11:32 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_buffer	*buff[FD_MAX];
	char			*str;
	t_list			*line;

	if (fd < 0 || fd >= FD_MAX)
		return (NULL);
	buff[fd] = init_buffer(buff[fd]);
	if (buff[fd] == NULL)
		return (NULL);
	line = malloc(sizeof(t_list));
	if (NULL == line)
		return (NULL);
	line->string = malloc(sizeof(char));
	if (NULL == line->string)
	{
		free(line);
		return (NULL);
	}
	line->string[0] = '\0';
	line->len = 0;
	line->next = NULL;
	line->prev = NULL;
	str = get_line(fd, line, buff[fd]);
	clean_all(line, buff, fd);
	return (str);
}

void	clean_all(t_list *list, t_buffer **buff, int fd)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->string)
			free(tmp->string);
		free(tmp);
	}
	if (buff[fd]->buffer[buff[fd]->start] == '\0')
	{
		free(buff[fd]);
		buff[fd] = NULL;
	}
}

char	*get_line(int fd, t_list *line, t_buffer *buff)
{
	ssize_t	toappend_len;
	t_list	*last;

	last = line;
	while (last->len == 0 || last->string[last->len - 1] != '\n')
	{
		if (buffer_update(fd, buff) <= 0)
			break ;
		toappend_len = get_toappend_len(&buff->buffer[buff->start]);
		last = ft_strappend(last, &buff->buffer[buff->start], toappend_len);
		buff->start += toappend_len;
	}
	return (list_join(line));
}

char	*list_join(t_list *line)
{
	ssize_t		len;
	t_list		*lst;
	char		*str;

	len = 0;
	lst = line;
	str = NULL;
	while (lst)
	{
		len += lst->len;
		lst = lst->next;
	}
	if (len != 0)
	{
		str = malloc(sizeof(char) * (len + 1));
		if (str != NULL)
			list_join_util(line, str);
	}
	return (str);
}

ssize_t	get_toappend_len(char *buffer)
{
	ssize_t	len;

	len = 0;
	while (buffer[len] != '\0' && buffer[len] != '\n')
		++len;
	if (buffer[len] == '\n')
		++len;
	return (len);
}
