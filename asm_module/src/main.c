#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "asm.h"

t_code				check_filename(char *name)
{
	size_t			len;

	len = ft_strlen(name);
	if (len < 2)
		return (error);
	if (name[len - 1] != 's' || name[len - 2] != '.')
		return (error);
	return (done);
}

t_code				compile_file(t_file *file)
{
	error_handler(no_error, 0, file);
	if (check_filename(file->name) == error)
		return (error_handler(bad_filename, 0, 0));
	else
	{
		file->fd = open(file->name, O_RDONLY);
		if (file->fd == -1)
			return (error_handler(open_error, 0, 0));
		else
		{
			scanner(file);
			if (file->out_name)
				ft_memdel((void**)&(file->out_name));
			close(file->fd);
		}
	}
	return (done);
}

int				print_usage(void)
{
	ft_printf("\n%sUsage : ./asm file1.s file2.s [...]%s\n\n", WHT, RESET);
	return (0);
}

int					main(int argc, char **argv)
{
	int32_t			argnum;
	t_file			file;

	if (argc == 1)
		return (print_usage());
	argnum = 1;
	while (argnum < argc)
	{
		ft_bzero(&file, sizeof(t_file));
		file.name = argv[argnum];
		compile_file(&file);
		argnum++;
	}
	return (0);
}
