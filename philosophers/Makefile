# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bferny <bferny@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/01 17:47:05 by bferny            #+#    #+#              #
#    Updated: 2021/12/15 22:01:36 by bferny           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	philosophers

SRCS		=  	philosophers.c	\
				time.c			\
				life.c			\
				main.c			\
				ft_atoi.c		\
				ft_strlen.c		\
				init.c			\
				args.c			\
				destroy.c		\


INCLUDES	=	./

HEADERS		=	./philosophers.h

OBJS		= 	${SRCS:.c=.o}

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