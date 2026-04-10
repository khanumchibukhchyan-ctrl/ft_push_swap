NAME = push_swap
BONUS_NAME = checker

# Compiler and flags
CC = cc
CFLAGS = -fsanitize=address # -Wall -Wextra -Werror
INCLUDES = -I. -I./libft

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source files
SRCS = main.c \
		atol.c \
		error.c \
		disorder.c \
		parse_utils.c \
		sorting_utils.c \
		main_functions.c \
		list_operations.c \
		simple_algorithm.c \
		medium_algorithm.c \
		stack_operations.c \
		complex_algorithm.c \
		selection_sort_utils.c \
		stack_operations_bonus.c \
		chunk_sort_utils.c \
		benchmark.c \
		benchmark_utils.c

# Bonus files
BONUS_SRCS = atol.c \
			 error.c \
			 disorder.c \
			 parse_utils.c \
			 sorting_utils.c \
			 main_functions.c \
			 list_operations.c \
			 simple_algorithm.c \
			 medium_algorithm.c \
			 stack_operations.c \
			 complex_algorithm.c \
			 selection_sort_utils.c \
			 stack_operations_bonus.c \
			 chunk_sort_utils.c \
			 benchmark.c \
			 benchmark_utils.c \
			 checker_utils.c \
			 checker.c \
			 execute.c


# Object files
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

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

bonus: $(LIBFT) $(BONUS_OBJS)
	@echo "$(GREEN)Linking $(BONUS_NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)
	@echo "$(GREEN)✓ $(BONUS_NAME) compiled successfully!$(RESET)"

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJS) $(BONUS_OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME) $(BONUS_NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re