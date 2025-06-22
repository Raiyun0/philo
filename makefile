NAME = philo

SRC = ft_utils.c main.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror


all: $(NAME)

$(NAME): $(OBJ)
    $(CC) $(CFLAGS) $(OBJ) -o $(NAME)


%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@


clean:
    @rm -f $(OBJ)


fclean: clean
    @rm -f $(NAME) libft.so

re: fclean all

so:
    $(CC) -fPIC $(CFLAGS) -c $(SRC)
    $(CC) -shared -o libft.so $(OBJ)