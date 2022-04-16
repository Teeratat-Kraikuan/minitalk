# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkraikua <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/15 22:14:48 by tkraikua          #+#    #+#              #
#    Updated: 2022/04/15 22:14:48 by tkraikua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Werror -Wextra

all : server client
		gcc $(FLAGS) server.o -o server
		gcc $(FLAGS) client.o -o client

server :
		gcc $(FLAGS) -c server.c -o server.o

client :
		gcc $(FLAGS) -c client.c -o client.o

clean :
		rm -rf *.o

fclean : clean
		rm -rf server client

re : fclean all