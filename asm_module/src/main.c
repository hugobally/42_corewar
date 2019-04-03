#include "asm.h"

#include <fcntl.h>//move if open is moved elsewhere

int					main(int argc, char **argv)
{
	t_file			file;

	//TEMPORARY
	(void)argc;
	if (argc == 2)
	{
		file.name = argv[1];
		error_handler(no_error, 0, &file);
		file.fd = open(file.name, O_RDONLY);
		if (file.fd == -1)
			error_handler(open_error, 0, 0);
	}
	else
		file.fd = 0;
	scanner(&file);
//	close(file.fd);
	//END TEMPORARY
	return (0);
}
