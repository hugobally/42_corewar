# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbally <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 17:12:52 by hbally            #+#    #+#              #
#    Updated: 2019/03/26 14:37:49 by hbally           ###   ########.fr        #
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
				make -C libft

# Cleanup

.PHONY		:	clean
clean		:
				@$(foreach MODULE, $(MODULES), $(MAKE) -C $(MODULE) clean ;)
				@$(foreach LIB, $(LIBDIRS), $(MAKE) -C $(LIB) clean ;)

.PHONY		:	fclean
fclean		:	clean
				@$(foreach MODULE, $(MODULES), $(MAKE) -C $(MODULE) fclean ;)
				@$(foreach LIB, $(LIBDIRS), $(MAKE) -C $(LIB) fclean ;)

.PHONY		:	re
re			:	fclean all
