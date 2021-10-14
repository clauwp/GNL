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
	if (lst_arr == NULL)
	{
		lst_arr = (t_list **)malloc(sizeof(t_list *));
		*lst_arr = NULL;
	}
	lst = ft_getlst(fd, lst_arr);
	len = ft_getstr_len(lst);
	while (len <= 0)
	{
		buf = ft_newstr(fd);
		if (buf == NULL)
			break ;
		ft_addnode(ft_newnode(buf), lst);
		len = ft_getstr_len(lst);
		//printf("2nd len:%d\n", len);
	}
	return (ft_newline(&lst, len));
}

t_list	*ft_getlst(int fd, t_list **lst_arr)
{
	t_list	*retlist;

	while (*lst_arr != NULL)
	{
		if ((*lst_arr)->fd == fd)
			return (*lst_arr);
		lst_arr = &((*lst_arr)->next_list);
	}
	retlist = ft_newlst(fd);
	ft_addlst(retlist, lst_arr);
	return (retlist);
}

t_list	*ft_newlst(int fd)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list) * 1);
	list->fd = fd;
	list->node = NULL;
	list->next_list = NULL;
	return (list);
}

void	ft_addlst(t_list *list, t_list **lst_arr)
{
	if (*lst_arr == NULL)
		*lst_arr = list;
	else
	{
		while ((*lst_arr)->next_list != NULL)
			lst_arr = &((*lst_arr)->next_list);
		(*lst_arr)->next_list = list;
	}
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
