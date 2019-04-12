# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 17:12:52 by hbally            #+#    #+#              #
#    Updated: 2019/04/12 10:50:23 by rle-ru           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Dir Variables

LIBS		:=	libft			\
				libcorewar

MODULES		:=	asm_module		\
				vm_module

.PHONY		:	all
all			:	libs modules

# Main Targets

.PHONY		:	modules
modules		:
				@$(foreach MODULE, $(MODULES), $(MAKE) -C $(MODULE) | grep -v "Nothing" || true ;)

# Libft

.PHONY		:	libs
libs		:	
				@$(foreach LIB, $(LIBS), $(MAKE) -C $(LIB) | grep -v "Nothing" || true ;)


.PHONY		:	libft
libft		:
				@$($(MAKE) -C libft | grep -v "Nothing" || true)

# Cleanup

.PHONY		:	clean
clean		:
				@$(foreach MODULE, $(MODULES), $(MAKE) clean -C $(MODULE);)
				@$(foreach LIB, $(LIBS), $(MAKE) clean -C $(LIB);)

.PHONY		:	fclean
fclean		:	clean
				@$(foreach MODULE, $(MODULES), $(MAKE) fclean -C $(MODULE);)
				@$(foreach LIB, $(LIBS), $(MAKE) fclean -C $(LIB);)

.PHONY		:	re
re			:	fclean all
