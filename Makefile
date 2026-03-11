NAME = push_swap

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIB_DIR = libft

LIB = $(LIB_DIR)/libft.a

SRC =

OBJ = $(SRC:.c=.o)

all: $(LIB) $(NAME)

$(LIB):
	$(MAKE) -C $(LIB_DIR)

$(NAME): $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIB_DIR) -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	$(MAKE) -C $(LIB_DIR) clean
	-rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(LIB_DIR) fclean
	-rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
