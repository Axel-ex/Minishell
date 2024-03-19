NAME		=	minishell

SRCS_DIR	=	srcs

OBJ_DIR		=	bin

LIBFT_DIR	=	Libft

LIBFT		=	libft.a

SRCS		=	$(wildcard $(SRCS_DIR)/*.c)\
				$(wildcard $(SRCS_DIR)/**/*.c)

OBJS		=	$(patsubst $(SRCS_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

CCFLAGS		=	-Wall -Wextra -Werror -g

FLAGS		=	-lreadline -L /opt/homebrew/Cellar/readline/8.2.1/lib -I /opt/homebrew/Cellar/readline/8.2.1/include

INC			=	includes

MODE		=	normal

GREEN		= \033[38;5;47m
YELLOW		= \033[38;5;226m
RED			= \033[38;5;196m
CYAN 		= \033[1;36m
RESET 		= \033[0m

ifeq ($(MODE), debug)
	FLAGS += -fsanitize=address
endif

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	@cc $(CCFLAGS) -c $< -o $@
	@echo "[$(CYAN)compiling$(RESET)]:\t $<"

all: $(NAME)
	@echo "[$(GREEN)DONE$(RESET)]:\t\t $(GREEN)minishell$(RESET)"

$(NAME): $(OBJS) $(LIBFT)
	@cc $(CCFLAGS) -I $(INC) $(OBJS) $(LIBFT_DIR)/$(LIBFT) $(FLAGS) -o $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)/
	@mkdir $(OBJ_DIR)/builtins
	@mkdir $(OBJ_DIR)/init_exit
	@mkdir $(OBJ_DIR)/parsing
	@mkdir $(OBJ_DIR)/execution
	@mkdir $(OBJ_DIR)/debug
	@mkdir $(OBJ_DIR)/signals
	@mkdir $(OBJ_DIR)/envp
	@mkdir $(OBJ_DIR)/utils

$(LIBFT):
	@echo "[$(CYAN)linking$(RESET)]:\t $@"
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
