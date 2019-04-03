#include "libft.h"
#include "errors.h"
#include "types.h"
#include "asm.h"

t_code				syntax(t_tokenlst *lst, t_file *file)
{
	header_t		header;
	t_label			*label_tab;

	label_tab = NULL;
	ft_bzero(&header, sizeof(header_t));
	header.magic = COREWAR_EXEC_MAGIC;
	if (get_header(lst, &header) == error)
		return (error);
	build_label_tab(lst, &label_tab);
	syntax_prog(lst, &label_tab, &header);
	if (error_handler(query, 0, 0) != error)
	{
		if (!header.prog_size)
			return (syntax_exit(&label_tab, &header, no_instructions));
		if (output_file(lst, &label_tab, &header, file) == error)
			return (syntax_exit(&label_tab, &header, write_crash));
	}
	return (syntax_exit(&label_tab, &header, no_error));
}
