#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include "get_next_line.h"


/*int	main(void)
{
	int fd = open("text2.txt", O_RDONLY);
	int fd2 = open("text.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd2));
}
*/

char	*get_next_line(int fd)
{
	static t_list	**lst_arr;
	t_list			*lst;
	int				len;
	char			*buf;

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
	} 
	return (ft_newline(lst, len));
}

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
