NAME		= push_swap
BONUS_NAME	= checker

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I. -I./libft

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

# Shared sources (used by both push_swap and checker)
COMMON_SRCS	= atol.c \
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

# Target-specific sources
MAIN_SRCS	= main.c
BONUS_SRCS	= checker.c \
			  checker_utils.c \
			  execute.c

# Object directories to keep root clean
OBJ_DIR		= obj
COMMON_OBJS	= $(addprefix $(OBJ_DIR)/, $(COMMON_SRCS:.c=.o))
MAIN_OBJS	= $(addprefix $(OBJ_DIR)/, $(MAIN_SRCS:.c=.o))
BONUS_OBJS	= $(addprefix $(OBJ_DIR)/, $(BONUS_SRCS:.c=.o))

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory

$(OBJ_DIR)/%.o: %.c push_swap.h | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(LIBFT) $(COMMON_OBJS) $(MAIN_OBJS)
	@$(CC) $(CFLAGS) $(COMMON_OBJS) $(MAIN_OBJS) $(LIBFT) -o $(NAME)
	@echo "$(NAME) ready"

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(COMMON_OBJS) $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(COMMON_OBJS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)
	@echo "$(BONUS_NAME) ready"

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory

re: fclean all

.PHONY: all bonus clean fclean re