# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbally <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/26 14:17:52 by hbally            #+#    #+#              #
#    Updated: 2019/04/24 16:13:08 by hbally           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	../asm

# Raw Sources

SRCS_RAW			:=	main.c						\
						scanner.c					\
						scanner_add.c				\
						scanner_tokens.c			\
						scanner_exit.c				\
						lexer.c						\
						lexer_labels.c				\
						lexer_instructions.c		\
						lexer_values.c				\
						lexer_clear.c				\
						error_handler.c				\
						error_print.c				\
						syntax.c					\
						syntax_header.c				\
						syntax_prog.c				\
						syntax_exit.c				\
						output_file.c				\
						output_instruction.c		\
						label_tab.c					\
						deasm.c

# Directories

SRCSDIR   			=	src

OBJSDIR   			=	obj

LIBSPATH			=	..

LIBS				:=	$(LIBSPATH)/libft				\
						$(LIBSPATH)/libcorewar

INCDIR				:=	$(LIBS:%=%/inc) 				\
						inc

# Files

SRCS				:=	$(SRCS_RAW:%.c=$(SRCSDIR)/%.c)

OBJS  				:=	$(SRCS:$(SRCSDIR)/%.c=$(OBJSDIR)/%.o)

DEPENDENCIES		:=	$(OBJS:%.o=%.d)

LIBFILES			:=	$(foreach LIB, $(LIBS), $(LIB)/$(notdir $(LIB)).a)

# Compiler Config

CC					=	gcc

CFLAGS				+=	-Wall -Werror -Wextra

INCLUDES			:=	$(addprefix -I ,$(INCDIR))

INCLIBS				:=	$(foreach LIB,$(LIBS),-L $(LIB) $(subst lib,-l,$(notdir $(LIB))))

# Main Target

all					:	libs $(NAME)

$(NAME)				: 	$(OBJS) $(LIBFILES)
						$(CC) -o $@ $(CFLAGS) $(OBJS) $(INCLIBS)

# Make Libs

.PHONY				:	libs
libs				:
						@$(foreach LIB, $(LIBS), make -C $(LIB);)

# Objs Target

-include $(DEPENDENCIES)

$(OBJS)				: 	$(OBJSDIR)/%.o : $(SRCSDIR)/%.c
						@mkdir -p $(OBJSDIR)
						$(CC) -o $@ $(CFLAGS) $(INCLUDES) -MMD -c $<

# Cleanup

.PHONY				:	clean
clean				:
						rm -rf $(OBJSDIR)

.PHONY				:	fclean
fclean				:	clean
						rm -f $(NAME)

.PHONY				:	re
re					:	fclean all
