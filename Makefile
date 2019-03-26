# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbally <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 17:12:52 by hbally            #+#    #+#              #
#    Updated: 2019/03/26 15:08:47 by hbally           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Dir Variables

LIBS		:=	libft

MODULES		:=	asm_module		\
				vm_module

.PHONY		:	all
all			:	libft modules

# Main Targets

.PHONY		:	modules
modules		:
				@$(foreach MODULE, $(MODULES), $(MAKE) -C $(MODULE) | grep -v "Nothing" || true ;)

# Libft

.PHONY		:	libft
libft		:
				$($(MAKE) -C libft | grep -v "Nothing" || true)

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
