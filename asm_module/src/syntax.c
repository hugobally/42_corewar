#include "libft.h"
#include "errors.h"
#include "types.h"
#include "asm.h"

t_code				syntax(t_tokenlst *lst, const t_file *file)
{
	header_t		header;
	t_label			*label_tab;

	label_tab = NULL;
	ft_bzero(&header, sizeof(header_t));
	if (get_header(lst, &header) == error)
		return (error);
	build_label_tab(lst, &label_tab);
	syntax_prog(lst, &label_tab, &header);

	(void)file;
//	if no error
	//check if prog size != 0 (only labels)
	//output
//	syntax_exit(&label_tab);
	return (done);
}
