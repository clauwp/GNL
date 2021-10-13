/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clau <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:56:45 by clau              #+#    #+#             */
/*   Updated: 2021/10/13 23:52:34 by clau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

int	ft_getstr_len(t_list *list)
{
	t_node	**current_node;
	int		len;
	char	*temp;

	current_node = &(list->node);
	len = 0;
	while (*current_node != NULL)
	{
		temp = (*current_node)->str;
		while (*temp != 0)
		{
			len++;
			if (*temp++ == '\n')
				return (len);
		}
		current_node = &((*current_node)->next_node);
	}
	return (-len);
}

char	*ft_newstr(int fd)
{
	char	*buf;
	int		byte_read;
	char	*copy_buf;
	const int BUFFER_SIZE = 10;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	byte_read = read(fd, buf, BUFFER_SIZE);
	if (byte_read <= 0)
		return (NULL);
	buf[byte_read] = '\0';
	copy_buf = ft_strdup(buf);
	free(buf);
	return (copy_buf);
}

t_node	*ft_newnode(char *str)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->str = str;
	node->next_node = NULL;
	return (node);
}

void	ft_addnode(t_node *node, t_list *list)
{
	t_node	**current_node;

	current_node = &(list->node);
	if (*current_node == NULL)
		*current_node = node;
	else
	{
		while ((*current_node)->next_node != NULL)
			current_node = &((*current_node)->next_node);
		(*current_node)->next_node = node;
	}
}

/*
Allocate memory and forms a string of a new line from the linked list.
@lst: pointer to linked list
@len: length of string of new line
@return: a pointer to the string created
*/
char	*ft_newline(t_list *lst, int len)
{
	t_node	**current_node;
	char	*retstr;
	char	*copy_retstr;
	char	*marker;

	if (len < 0)
		len = -len;
	else if (len == 0)
		return (NULL);
	current_node = &(lst->node);
	retstr = (char *)malloc(sizeof(char) * (len + 1));
	copy_retstr = retstr;
	while (*current_node != NULL)
	{
		marker = (*current_node)->str;
		while (*((*current_node)->str) != 0 && len-- > 0)
			*copy_retstr++ = *((*current_node)->str++);
		if (len <= 0)
			*copy_retstr = 0;
		if (*((*current_node)->str) == 0)
			free(marker);
		current_node = &((*current_node)->next_node);
	}
	return (retstr);
}
