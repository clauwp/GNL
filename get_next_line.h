#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
typedef struct s_node{
	char	*str;
	struct s_node 	*next_node;
} t_node;

typedef struct s_list{
    int fd;
    t_node *node;
    struct s_list *next_list;
} t_list;

t_list *ft_getlst(int fd, t_list **lst_arr);
t_list *ft_newlst(int fd);
void ft_addlst(t_list *list, t_list **lst_arr);
t_node *ft_newnode(char *str);
void ft_addnode(t_node *node, t_list *list);
t_node *ft_clearnodes(t_list *lst);
char    *ft_newline(t_list *lst, int len);
int    ft_getstr_len(t_list *lst);
char    *ft_newstr(int fd);
char    *get_next_line(int fd);
#endif