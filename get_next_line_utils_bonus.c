/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 12:16:24 by tamighi           #+#    #+#             */
/*   Updated: 2021/09/15 13:07:12 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	len(const char *c, char s)
{
	int	i;

	i = 0;
	if (!c)
		return (0);
	while (c[i] != s && c[i] != '\0')
		i++;
	return (i);
}

int	ft_nl(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strndup(const char *str, int n, t_list *buffers, int *fd)
{
	int		i;
	char	*new;

	i = 0;
	if ((!str) || (n == 0 && str[0] != '\n'))
		return (0);
	new = (char *)malloc(n + 1);
	if (!new)
		return (free_my_buffer(buffers, (char *)str, fd));
	while (str[i] != '\0' && i < n)
	{
		new[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		new[i++] = '\n';
	new[i] = '\0';
	return (new);
}

char	*ft_check_buffers(t_list *buffers, t_list **tmp, int *x)
{
	t_list	*ptr;

	if (!buffers)
		return (0);
	ptr = buffers;
	while (ptr)
	{
		if (ptr->fd == *x)
		{
			*tmp = ptr;
			return (ft_strndup(ptr->buf, len(ptr->buf, '\0'), buffers, x));
		}
		ptr = ptr ->next;
	}
	return (0);
}

char	*ft_strjoin(char *line, const char *buf, t_list *buffers, int *fd)
{
	int		i;
	int		j;
	char	*join;

	i = 0;
	j = 0;
	if (!line)
		return (ft_strndup((char *)buf, len(buf, '\0'), buffers, fd));
	join = (char *)malloc(len(buf, '\0') + len(line, '\0') + 1);
	if (!join)
		return (free_my_buffer(buffers, line, fd));
	while (line[i] != '\0')
	{
		join[i] = line[i];
		i++;
	}
	while (buf[j] != '\0')
	{
		join[i + j] = buf[j];
		j++;
	}
	join[i + j] = '\0';
	free(line);
	return (join);
}
