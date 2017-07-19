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

NAME =	corewar
FLAGS = -Wall -Werror -Wextra
SRC = main.c error_manager.c controller.c model.c free_memory.c start_process.c \
check_live.c run_process.c visualise.c \
operations/live.c \
operations/aff.c \
operations/ft_fork.c \
operations/lfork.c \
operations/and.c \
operations/or.c \
operations/xor.c \
operations/zjmp.c \
operations/ld.c \
operations/lld.c \
#operations/st.c \
#operations/add.c \
#operations/sub.c \
#operations/ldi.c \
#operations/sti.c \
#operations/lldi.c \


OSRC =	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OSRC)
	make -C libft
	gcc -o $(NAME) $(FLAGS) $(OSRC) libft/libft.a -lncurses
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
