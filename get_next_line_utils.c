/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clau <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:56:45 by clau              #+#    #+#             */
/*   Updated: 2021/10/14 01:21:13 by clau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

/*
calculate the number of characters that exists in current list
returns num of chars if a line (ie '\n' is present) can be formed
else, returns a negative num.
*/
int	ft_getstr_len(t_list *list)
{
	t_node	*current_node;
	int		len;

	current_node = list->node;
	len = 0;
	while (current_node != NULL)
	{
		if (current_node->c != 0)
			len++;
		if (current_node->c == '\n')
			return (len);
		current_node = current_node->next_node;
	}
	return (-len);
}

void	ft_add_newnode(char *str, t_list *lst)
{
	t_node	*node;
	int		i;

	i = 0;
	while (str[i])
	{
		node = (t_node *)malloc(sizeof(t_node));
		node->c = str[i];
		node->next_node = NULL;
		ft_addnode(node, lst);
		i++;
	}
	free(str);
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
char	*ft_newline(t_list **lst, int len)
{
	t_node	**current_node;
	char	*retstr;
	int		i;

	i = 0;
	if (len < 0)
		len = -len;
	else if (len == 0 || *lst == NULL)
		return (NULL);
	current_node = &((*lst)->node);
	retstr = (char *)malloc(sizeof(char) * (len + 1));
	if (retstr == NULL)
		return (NULL);
	while (*current_node != NULL && len-- > 0)
	{
		retstr[i++] = (*current_node)->c;
		retstr[i] = 0;
		(*current_node)-> c = 0;
		current_node = &((*current_node)->next_node);
	}
	ft_delnode(lst);
	return (retstr);
}

void ft_delnode(t_list **lst)
{
	t_node **current_node;
	t_node *temp_node;

	current_node = &((*lst)->node);
	while (*current_node != NULL)
	{
		temp_node = (*current_node)->next_node;
		if ((*current_node)->c == 0)
		{
			free(*current_node);
			*current_node = temp_node;
		}
		else
			break ;
	}		
}