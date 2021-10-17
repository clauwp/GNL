/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clau <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:53:59 by clau              #+#    #+#             */
/*   Updated: 2021/10/13 22:54:59 by clau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	**lst_arr;
	t_list			**lst_ptr;
	char			*buf;

	if (lst_arr == NULL)
	{
		lst_arr = (t_list **)malloc(sizeof(t_list *));
		*lst_arr = NULL;
	}
	if (fd < 0)
		return (NULL);
	lst_ptr = ft_getlst(fd, lst_arr);
	while (ft_getstr_len(*lst_ptr) <= 0)
	{
		buf = ft_newstr(fd);
		if (buf == NULL)
			break;
		ft_add_newnode(buf, *lst_ptr);
	}
	if (buf == NULL && (*lst_ptr)->node == NULL)
	{
		free((*lst_ptr));
		*lst_ptr = NULL;
	}
	if (*lst_arr == NULL)
		free(lst_arr);
	return (ft_newline(lst_ptr, ft_getstr_len(*lst_ptr)));
}

t_list	**ft_getlst(int fd, t_list **lst_arr)
{
	while (*lst_arr != NULL)
	{
		if ((*lst_arr)->fd == fd)
			return (lst_arr);
		lst_arr = &((*lst_arr)->next_list);
	}
	return (ft_add_newlst(fd, lst_arr));
}

t_list	**ft_add_newlst(int fd, t_list **lst_arr)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list) * 1);
	list->fd = fd;
	list->node = NULL;
	list->next_list = NULL;
	if (*lst_arr == NULL)
	{
		*lst_arr = list;
		return (lst_arr);
	}
	else
	{
		while ((*lst_arr)->next_list != NULL)
			lst_arr = &((*lst_arr)->next_list);
		(*lst_arr)->next_list = list;
	}
	return (&((*lst_arr)->next_list));
}

char	*ft_newstr(int fd)
{
	char	buf[BUFFER_SIZE];
	int		byte_read;
	char	*copy_buf;

	byte_read = read(fd, buf, BUFFER_SIZE);
	if (byte_read <= 0)
		return (NULL);
	buf[byte_read] = '\0';
	copy_buf = ft_strdup(buf, byte_read);
	return (copy_buf);
}

char	*ft_strdup(const char *s1, int bytes)
{
	char	*retstr;
	char	*copyretstr;

	retstr = (char *)malloc(sizeof(char) * (bytes + 1));
	if (retstr != NULL)
	{
		copyretstr = retstr;
		while (bytes-- > 0)
			*retstr++ = *s1++;
		*retstr = 0;
		return (copyretstr);
	}
	else
		return (NULL);
}
