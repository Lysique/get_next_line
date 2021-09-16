/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 10:19:44 by tamighi           #+#    #+#             */
/*   Updated: 2021/09/15 13:52:25 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "get_next_line.h"

void	*free_my_buffer(t_list *buffers, char *str1, int *fd)
{
	t_list	*ptr;
	t_list	*ptr2;

	ptr = buffers;
	if (str1)
	{
		free(str1);
		str1 = 0;
	}
	while (ptr)
	{
		ptr2 = ptr->next;
		free(ptr);
		ptr = ptr2;
	}
	*fd = -1;
	return (0);
}

static t_list	*ft_lstadd_front(t_list *buffers, t_list **tmp, int *x)
{
	t_list	*new;
	t_list	*ptr;

	ptr = buffers;
	while (ptr)
	{
		if (ptr->fd == *x)
		{
			*tmp = ptr;
			return (buffers);
		}
		ptr = ptr->next;
	}
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (free_my_buffer(buffers, 0, x));
	new->fd = *x;
	new->next = buffers;
	*tmp = new;
	return (new);
}

static t_list	*ft_del_buf(t_list *buffers, int x)
{
	t_list	*ptr;
	t_list	*ptr2;

	if (!buffers)
		return (0);
	ptr = buffers;
	ptr2 = 0;
	while (ptr)
	{
		if (ptr->fd == x)
			break ;
		ptr2 = ptr;
		ptr = ptr ->next;
	}
	if (!ptr2)
	{
		ptr2 = ptr->next;
		free(ptr);
		return (ptr2);
	}
	ptr2->next = ptr->next;
	free(ptr);
	return (buffers);
}

char	*ft_change(char *buf, char *line, t_list *buffers, int *fd)
{
	char	*c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	c = (char *)malloc(len(line, '\n') + 2);
	if (!c)
		return (free_my_buffer(buffers, line, fd));
	while (line[i] != '\0')
	{
		c[i] = line[i];
		if (line[i++] == '\n')
			break ;
	}
	c[i] = '\0';
	while (line[i + j] != '\0')
	{
		buf[j] = line[i + j];
		j++;
	}
	buf[j] = '\0';
	free(line);
	return (c);
}

char	*get_next_line(int fd)
{
	static t_list	*buffers = NULL;
	int				ret;
	char			*line;
	t_list			*tmp;

	ret = 1;
	line = ft_check_buffers(buffers, &tmp, &fd);
	if (!line)
		buffers = ft_lstadd_front(buffers, &tmp, &fd);
	while (fd >= 0 && BUFFER_SIZE > 0 && ret > 0 && ft_nl(line) == 0 && buffers)
	{
		ret = read(fd, tmp->buf, BUFFER_SIZE);
		if (ret == -1)
		{
			buffers = ft_del_buf(buffers, fd);
			return (free_my_buffer(0, line, &fd));
		}
		tmp->buf[ret] = '\0';
		line = ft_strjoin(line, tmp->buf, buffers, &fd);
	}
	if (ft_nl(line))
		return (ft_change(tmp->buf, line, buffers, &fd));
	buffers = ft_del_buf(buffers, fd);
	return (line);
}
