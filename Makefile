# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gabguerr <gabguerr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/05 13:57:25 by gabguerr          #+#    #+#              #
#    Updated: 2024/06/05 23:07:57 by gabguerr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = program
SERVER = server
CLIENT = client
CC = gcc
LIB = ./minitalk_utils.c
CFLAGS = -Wall -Werror -Wextra

all: $(SERVER) $(CLIENT)

$(NAME): all

$(SERVER):
	$(CC) $(CFLAGS) server.c $(LIB) -o $(SERVER)

$(CLIENT):
	$(CC) $(CFLAGS) client.c $(LIB) -o $(CLIENT)

clean:
	rm -rf $(SERVER) $(CLIENT) 

fclean: clean

re: fclean all

.PHONY: all flean clean re
