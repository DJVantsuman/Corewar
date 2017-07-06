# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itsuman <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/10 18:22:44 by itsuman           #+#    #+#              #
#    Updated: 2017/05/12 21:46:23 by itsuman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	corevar
FLAGS = -Wall -Werror -Wextra
SRC = main.c error_manager.c controller.c model.c free_memory.c start_process.c \
check_cycle_to_die.c operations/live.c
OSRC =	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OSRC)
	make -C libft
	gcc -o $(NAME) $(FLAGS) $(OSRC) libft/libft.a
	make clean

%.o: %.c
	gcc -g $(FLAGS) -c -o $@ $<

clean:
	make clean -C libft
	rm -f $(OSRC)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all
