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

int	main(void)
{
	int	fd = open("text2.txt", O_RDONLY);
	int	fd2 = open("text.txt", O_RDONLY);
	
	
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd2));
}