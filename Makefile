# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkraikua <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/18 13:56:10 by tkraikua          #+#    #+#              #
#    Updated: 2022/04/18 13:56:10 by tkraikua         ###   ########.fr        #
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

bonus : all
		gcc $(FLAGS) -c server_bonus.c -o server_bonus.o
		gcc $(FLAGS) -c client_bonus.c -o client_bonus.o
		gcc $(FLAGS) server_bonus.o -o server_bonus
		gcc $(FLAGS) client_bonus.o -o client_bonus

clean :
		rm -rf *.o

fclean : clean
		rm -rf server client server_bonus client_bonus

re : fclean all