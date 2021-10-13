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
