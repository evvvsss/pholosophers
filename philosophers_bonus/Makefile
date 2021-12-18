# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bferny <bferny@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/01 17:47:05 by bferny            #+#    #+#              #
#    Updated: 2021/12/18 20:01:14 by bferny           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	philosophers_bonus

SRCS		=  	philosophers_bonus.c	\
				main_bonus.c			\
				ft_atoi.c				\
				ft_strlen.c				\
				args_bonus.c			\
				child.c					\
				finish.c				\
				message_bonus.c			\
				life_bonus.c			\

INCLUDES	=	./

OBJS		= 	${SRCS:.c=.o}
HEADERS		=	./philosophers_bonus.h

CC			= 	gcc -g
RM			= 	rm -f

CFLAGS		= 	-Wall -Werror -Wextra 

.c.o:
				${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o ${<:.c=.o}

${NAME}:		${OBJS} ${HEADERS} 
				gcc -o $(NAME) $(OBJS) 

all:			${NAME} 

clean:			
				${RM} ${OBJS} 


fclean:			clean 
				rm -rf ${NAME}


re:				fclean all

.PHONY:			all clean fclean re