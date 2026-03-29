NAME = push_swap

# Compiler and flags
CC = cc
CFLAGS = -fsanitize=address # -Wall -Wextra -Werror
INCLUDES = -I. -I./libft

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source files
SRCS = main.c \
       main_functions.c \
       error.c \
       disorder.c \
       parse_utils.c \
       stack_operations.c \
       list_operations.c \
       simple_algorithm.c \
       medium_algorithm.c \
       complex_algorithm.c \
	   sorting_utils.c \
	   selection_sort_utils.c \
	   atol.c

# Object files
OBJS = $(SRCS:.c=.o)

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Rules
all: $(NAME)

$(LIBFT):
	@echo "$(GREEN)Compiling libft...$(RESET)"
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS) 
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

%.o: %.c push_swap.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re