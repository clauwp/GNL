#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "get_next_line.h"

t_list	*ft_getlst(int fd, t_list **lst_arr)
{
	t_list	*retlist;

	if (*lst_arr == NULL)
	{
		retlist = ft_newlst(fd);
		ft_addlst(retlist, lst_arr);
		return (retlist);
	}
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

	buf = (char *)malloc(sizeof(char) * BUFFERSIZE);
	byte_read = read(fd, buf, BUFERFSIZE);
	if (byte_read <= 0)
		return (NULL);
	buf[byte_read]= '\0';
	copy_buf = strdup(buf);
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

	if (len < 0)
		len = -len;
	else if (len == 0)
		return (NULL);
	current_node = &(lst->node);
	retstr = (char *)malloc(sizeof(char) * (len + 1));
	if (retstr == NULL)
		return (NULL);
	copy_retstr = retstr;
	while (*current_node != NULL)
	{
		while (*((*current_node)->str) != 0 && len-- > 0)
			*copy_retstr++ = *((*current_node)->str++);
		if (len <= 0)
			*copy_retstr = 0;
		current_node = &((*current_node)->next_node);
	}
	return (retstr);
}