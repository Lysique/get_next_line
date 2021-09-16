/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 13:55:06 by tamighi           #+#    #+#             */
/*   Updated: 2021/09/15 13:55:09 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H 

# include <stdlib.h>

# ifdef BUFFER_SIZE
#  if BUFFER_SIZE < 0
#   undef BUFFER_SIZE
#   define BUFFER_SIZE 0
#  endif 
# endif

typedef struct s_list
{
	int				fd;
	char			buf[BUFFER_SIZE + 1];
	struct s_list	*next;
}				t_list;
int		len(const char *c, char s);
int		ft_nl(char *line);
char	*ft_strndup(const char *str, int n, t_list *buffers, int *fd);
char	*ft_check_buffers(t_list *buffers, t_list **tmp, int *x);
char	*ft_strjoin(char *line, const char *buf, t_list *buffers, int *fd);
char	*ft_change(char *buf, char *line, t_list *buffers, int *fd);
char	*get_next_line(int fd);
void	*free_my_buffer(t_list *buffers, char *str1, int *fd);

#endif
