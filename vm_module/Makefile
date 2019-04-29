# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/26 14:17:52 by hbally            #+#    #+#              #
#    Updated: 2019/04/27 15:28:36 by tlesven          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	../corewar

# Raw Sources

SRCS_RAW			:=	main.c							\
						ft_usage.c						\
						ft_live.c						\
						ft_ld.c							\
						ft_st.c							\
						ft_add.c						\
						ft_sub.c						\
						ft_and.c						\
						ft_or.c							\
						ft_xor.c						\
						ft_zjump.c						\
						ft_ldi.c						\
						ft_sti.c						\
						ft_fork.c						\
						ft_lld.c						\
						ft_lldi.c						\
						ft_lfork.c						\
						ft_aff.c						\
						introduction.c					\
						arguments.c						\
						players.c						\
						arena.c							\
						process.c						\
						game.c							\
						decoding.c 						\
						instructions_4.c				\
						functions_tab.c 				\
						read_exec.c						\
						read_instruction.c				\
						get_pc.c						\
						dump.c							\
						graph_init.c					\
						graph_struct.c					\
						graph_champions.c				\
						graph_registers.c				\
						graph_process.c					\
						graph_infos.c					\
						graph_ctrl.c					\
						graph_ctrl_actions.c			\
						graph_arena.c					\
						graph_tools.c					\
						graph_win.c						\
						get_params.c					\
						ft_game_adj.c					\
						graph_threads.c					\
						check_option.c					\
						graph_move_process.c			\
						graph_game.c					\
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

NCURSES = -lncurses -lpthread

# Main Target

all					:	libs $(NAME)

$(NAME)				: 	$(OBJS) $(LIBFILES)
						$(CC) -o $@ $(CFLAGS) $(OBJS) $(NCURSES) $(INCLIBS) 

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
