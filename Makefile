# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/12 09:51:25 by sait-amm          #+#    #+#              #
#    Updated: 2024/07/30 10:48:38 by sait-amm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = philo.c \
		ft_atoi.c \
		parting.c \
		routine.c \
		tools.c \
		init_function.c \
		monitor.c \
		helper.c


OBJF = $(SRC:.c=.o)


NAME = philo


C = cc

CFLAGS =  -Wall -Werror -Wextra # -fsanitize=thread -g#-O3 -fsanitize=address -g #   -g 

all: $(NAME)


$(NAME): $(OBJF)
		$(C) $(CFLAGS) $(OBJF) -o $(NAME)

clean:
	rm -rf $(OBJF) 
fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re