# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbally <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/30 09:24:07 by hbally            #+#    #+#              #
#    Updated: 2019/03/26 15:05:00 by hbally           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	libftprintf.a

LIBFT				=	../..

SRCSDIR   			=	src

SRCS				:=	$(SRCSDIR)/ft_printf.c				\
						$(SRCSDIR)/ft_dprintf.c				\
						$(SRCSDIR)/ft_asprintf.c			\
						$(SRCSDIR)/parser.c					\
						$(SRCSDIR)/parser_checks.c			\
						$(SRCSDIR)/dispatcher.c				\
						$(SRCSDIR)/printers.c				\
						$(SRCSDIR)/baker_char.c				\
						$(SRCSDIR)/baker_string.c			\
						$(SRCSDIR)/baker_int.c				\
						$(SRCSDIR)/baker_long.c				\
						$(SRCSDIR)/baker_longlong.c			\
						$(SRCSDIR)/baker_double.c			\
						$(SRCSDIR)/baker_longdouble.c		\
						$(SRCSDIR)/baker_pointer.c			\
						$(SRCSDIR)/prefix.c					\
						$(SRCSDIR)/width.c					\
						$(SRCSDIR)/precision.c				\
						$(SRCSDIR)/special_handler.c		\
						$(SRCSDIR)/reset.c					\
						$(SRCSDIR)/exit_clean.c

OBJSDIR   			=	obj

OBJS				:=	$(SRCS:$(SRCSDIR)/%.c=$(OBJSDIR)/%.o)

DEPENDENCIES		=	$(OBJS:%.o=%.d)

INC					=	-I $(LIBFT)/inc/ 				\
						-I inc/							\

CC					=	gcc

CFLAGS				+=	-Wall -Werror -Wextra

all					:	$(NAME)

$(NAME)				: 	$(OBJS)
						ar rc $@ $(OBJS)

-include $(DEPENDENCIES)

$(OBJS)				: 	$(OBJSDIR)/%.o : $(SRCSDIR)/%.c
						@mkdir -p $(OBJSDIR)
						$(CC) -o $@ $(CFLAGS) $(INC) -MMD -c $<

.PHONY				:	clean
clean				:
						rm -rf $(OBJSDIR)

.PHONY				:	fclean
fclean				:	clean
						rm -f $(NAME)

.PHONY				:	re
re					:	fclean all
