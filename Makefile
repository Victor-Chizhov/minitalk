CLIENT = client
SERVER = server

CLIENT_B = client_bonus
SERVER_B = server_bonus

SRCS =	./utils/ft_putchar_fd.c \
		./utils/ft_putstr_fd.c \
		./utils/ft_atoi.c \
		./utils/ft_putnbr_fd.c			

SRCS_C = ./src/client.c
SRCS_S = ./src/server.c
	   
SRCS_C_B = ./src/client_bonus.c
SRCS_S_B = ./src/server_bonus.c

HEADER = ./inc

OBJS = $(SRCS:.c=.o)

OBJS_C = $(SRCS_C:.c=.o)
OBJS_S = $(SRCS_S:.c=.o)

OBJS_C_B = $(SRCS_C_B:.c=.o)
OBJS_S_B = $(SRCS_S_B:.c=.o)


CFLAGS = -Werror -Wextra -Wall -I

all: $(CLIENT) $(SERVER) $(CLIENT_B) $(SERVER_B)

CC = cc

%.o : %.c 
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(CLIENT) : $(OBJS_C) $(OBJS)
	$(CC) $(OBJS_C) $(OBJS) -o $(CLIENT)

$(SERVER) : $(OBJS_S) $(OBJS)
	$(CC) $(OBJS_S) $(OBJS) -o $(SERVER)

$(CLIENT_B) : $(OBJS_C_B) $(OBJS)
	$(CC) $(OBJS_C_B) $(OBJS) -o $(CLIENT_B)

$(SERVER_B) : $(OBJS_S_B) $(OBJS)
	$(CC) $(OBJS_S_B) $(OBJS) -o $(SERVER_B)

clean:
	rm -rf $(OBJS) $(OBJS_C) $(OBJS_S) $(OBJS_C_B) $(OBJS_S_B)

fclean:
	rm -rf $(OBJS) $(OBJS_C) $(OBJS_S) $(OBJS_C_B) $(OBJS_S_B) $(CLIENT) $(SERVER) $(CLIENT_B) $(SERVER_B)

re:	fclean all

.PHONY:	all clean fclean re
