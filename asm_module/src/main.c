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
		file.fd = open(file.name, O_RDONLY);
		if (file.fd == -1)
			error_handler(open_error, 0, &file);
		error_handler(no_err, 0, &file);
	}
	else
		file.fd = 0;
	scanner(&file);
//	close(file.fd);
	//END TEMPORARY
}
