#include "asm.h"

#include <fcntl.h>//move if open is moved elsewhere

int					main(int argc, char **argv)
{
	//TEMPORARY
	int fd;
	(void)argc;
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	lexer_scanner(fd);
	//END TEMPORARY
}
