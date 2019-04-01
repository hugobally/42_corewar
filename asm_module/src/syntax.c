#include "libft.h"
#include "errors.h"
#include "types.h"
#include "asm.h"

t_code				syntax(t_tokenlst *lst, const t_file *file)
{
	header_t		header;
	t_label			*label_tab;

	ft_bzero(&header, sizeof(header_t));
	if (get_header(lst, &header) == error)
		return (error);
	(void)file;
	(void)label_tab;
	//build_label_tab(lst, label_tab);
//	header.prog_size += syntax_check(lst);
	//output
	return (done);
}
