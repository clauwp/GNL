#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "get_next_line.h"

// utils function = strlen, strcat
/* Edge cases: 
* 1. start with \n
* 2. empty file
* 3. file with only \n
*/
char *ft_temp(void)
{
	char *str =(char *)malloc(sizeof(char) * 4);
	str = "hi!";
	return (str);
}
int	main(void)
{
	get_next_line(open("text2.txt", O_RDONLY));
}