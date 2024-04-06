/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:34:18 by rertzer           #+#    #+#             */
/*   Updated: 2022/11/23 14:16:51 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define FD_MAX 1024

typedef struct s_buffer
{
	ssize_t	start;
	char	buffer[BUFFER_SIZE + 1];
}	t_buffer;

typedef struct s_list
{
	ssize_t			len;
	char			*string;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

/* get_next_line.c functions */
char		*get_next_line(int fd);
void		clean_all(t_list *list, t_buffer **buff, int fd);
char		*get_line(int fd, t_list *line, t_buffer *buff);
char		*list_join(t_list *line);
ssize_t		get_toappend_len(char *buffer);

/* get_next_line_utils.c functions */
ssize_t		buffer_update(int fd, t_buffer *buff);
t_list		*ft_strappend(t_list *last, char *src, ssize_t len);
void		list_join_util(t_list *line, char *str);
t_buffer	*init_buffer(t_buffer *buff);
#endif
