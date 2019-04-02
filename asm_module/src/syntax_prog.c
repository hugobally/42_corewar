#include "asm.h"
#include "errors.h"
#include "types.h"

t_code			syntax_prog(t_tokenlst *lst,
							t_label **label_tab, 
							header_t *header)
{
	return (done);
}

t_code			syntax_prog(t_tokenlst *lst,
							t_label **label_tab, 
							header_t *header)
{
	lst->current = lst->prog_start;
	if (!lst->current)
		return (error_handler(no_instructions, 0, 0));
	while (lst->current)
	{
		parse_line(lst, label_tab, header);
		if (header->prog_size > CHAMP_MAX_SIZE
				|| header->prog_size > MAX_OUTPUT_BYTE_SIZE)
			return (error_handler(bytesize, lst->current, 0));
	}
	return (done);
}
