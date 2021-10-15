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
#include <stdio.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	**lst_arr;
	t_list			*lst;
	int				len;
	char			*buf;

	if (fd <= 0)
		return (NULL);
	lst = ft_getlst(fd, lst_arr);
	len = ft_getstr_len(lst);
	while (len <= 0)
	{
		buf = ft_newstr(fd);
		if (buf == NULL)
		{
			free(lst);
			break ;
		}
		ft_add_newnode(buf, lst);
		len = ft_getstr_len(lst);
	}
	return (ft_newline(&lst, len));
}

t_list	*ft_getlst(int fd, t_list **lst_arr)
{
	t_list	*retlist;

	if (lst_arr == NULL)
	{
		lst_arr = (t_list **)malloc(sizeof(t_list *));
		*lst_arr = NULL;
	}
	while (*lst_arr != NULL)
	{
		if ((*lst_arr)->fd == fd)
			return (*lst_arr);
		lst_arr = &((*lst_arr)->next_list);
	}
	retlist = ft_add_newlst(fd, lst_arr);
	return (retlist);
}

t_list	*ft_add_newlst(int fd, t_list **lst_arr)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list) * 1);
	list->fd = fd;
	list->node = NULL;
	list->next_list = NULL;
	if (*lst_arr == NULL)
		*lst_arr = list;
	else
	{
		while ((*lst_arr)->next_list != NULL)
			lst_arr = &((*lst_arr)->next_list);
		(*lst_arr)->next_list = list;
	}
	return (list);
}

char	*ft_newstr(int fd)
{
	char	*buf;
	int		byte_read;
	char	*copy_buf;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	byte_read = read(fd, buf, BUFFER_SIZE);
	if (byte_read <= 0)
	{
		free(buf);
		return (NULL);
	}
	buf[byte_read] = '\0';
	copy_buf = ft_strdup(buf);
	free(buf);
	return (copy_buf);
}

char	*ft_strdup(const char *s1)
{
	char	*retstr;
	char	*copyretstr;
	int		len;

	len = 0;
	while (s1[len])
		len++;
	retstr = (char *)malloc(sizeof(char) * (len + 1));
	if (retstr != NULL)
	{
		copyretstr = retstr;
		while (*s1)
			*retstr++ = *s1++;
		*retstr = 0;
		return (copyretstr);
	}
	else
		return (NULL);
}
