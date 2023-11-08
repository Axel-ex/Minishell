NAME		=	minishell

SRCS_DIR	=	srcs

OBJ_DIR		=	obj

LIBFT_DIR	=	Libft

LIBFT		=	libft.a

SRCS		=	$(wildcard $(SRCS_DIR)/*.c)

OBJS		=	$(patsubst $(SRCS_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

CCFLAGS		=	-Wall -Wextra -Werror

FLAGS		=	-lreadline

INC			=	includes

GREEN		= \033[38;5;47m
YELLOW		= \033[38;5;226m
RED			= \033[38;5;196m
RESET 		= \033[0m

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	@cc $(CCFLAGS) -c $< -o $@
	@echo "[$(GREEN)compiling$(RESET)]: $<"

all: $(NAME)
	@echo "$(GREEN)$(NAME) executable created$(RESET)"

$(NAME): $(OBJS) $(LIBFT)
	@cc $(CCFLAGS) $(FLAGS) -I $(INC) $(OBJS) $(LIBFT_DIR)/$(LIBFT) -o $(NAME)

$(OBJ_DIR):
	@mkdir obj/

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@echo "$(YELLOW)Removing objects files$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo "$(RED)removing $(NAME) executable$(RESET)"

re: fclean all

.PHONY: all clean fclean re