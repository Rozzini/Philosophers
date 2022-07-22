# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mraspors <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/26 05:31:37 by mraspors          #+#    #+#              #
#    Updated: 2022/07/13 04:00:02 by mraspors         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

SRC	= ./src/philo/helpers/ph_helpers.c ./src/philo/init/ph_init.c\
		  ./src/philo/routine/routine_helpers.c ./src/philo/routine/routine.c\
		  ./src/philo/start_n_director/director.c ./src/philo/start_n_director/start.c\
		   philo.c

OBJS	= $(SRC:.c=.o)

GCC	= gcc -g3

FLAGS	= -Wall -Wextra -Werror

INCLUDE	= -lpthread

HEADER	= philo.h

all:	$(NAME)

$(NAME): $(OBJS)
	$(GCC) -pthread $(FLAGS) $(OBJS) -o $(NAME) 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c $(HEADER)
	$(GCC) $(FLAGS) -c $<  -o $(<:.c=.o)