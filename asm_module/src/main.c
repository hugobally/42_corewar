#include "asm.h"

#include <fcntl.h>//move if open is moved elsewhere

int					main(int argc, char **argv)
{
	//TEMPORARY
	int fd;
	(void)argc;
	fd = open(argv[1], O_RDONLY);
	lexer_scanner(fd);
	//END TEMPORARY
}
