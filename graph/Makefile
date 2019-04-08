# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlesven <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/01 14:29:27 by tlesven           #+#    #+#              #
#    Updated: 2019/04/02 11:53:11 by tlesven          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc -Wall -Werror -Wextra
RM = rm -rf

NAME = graph

SRC = init_graph.c \
	  struct_graph.c

PATH_SRC = .

OBJ = $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))
PATH_OBJ = obj

NCURSES = -lncurses

INCLUDES = includes/
INCFLAGS = -I includes/ -I ../libft/inc/.

LIBSPATH = ../libft
LIB = $(LIBSPATH)/libft.a
LIBFLAGS = -L $(LIBSPATH) -lft

all: $(LIB) $(NAME)

$(NAME): $(OBJ)
		@$(CC) -o $(NAME) $(OBJ) $(NCURSES) $(INCFLAGS) $(LIBFLAGS)
		@echo "$@ done"

$(PATH_OBJ)/%.o : $(addprefix $(PATH_SRC)/, %.c)
		@mkdir -p $(PATH_OBJ)
		@$(CC) -o $@ -c $< $(INCFLAGS)
		@echo "$@ done"

$(LIB) :
		make -C $(LIBSPATH)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all
