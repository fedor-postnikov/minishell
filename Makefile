NAME = minishell

# includes
LIBFT_DIR = libft/
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

INCLUDES_DIR = includes/
HEADERS = $(LIBFT_DIR)libft.h $(INCLUDES_DIR)minishell.h

# main files
MAIN_DIR = main/
MAIN_SRC = input.c \
	main.c \
	signals.c \
	\

SRC = $(addprefix $(MAIN_DIR), $(MAIN_SRC))

# init files
INIT_DIR = init/
INIT_SRC = init.c \
	\

SRC += $(addprefix $(INIT_DIR), $(INIT_SRC))

# parser files
PARSER_DIR = parser/
PARSER_SRC = parser.c \
	tokenizer.c \
	expansion.c \
	expansion2.c \
	command_table.c \
	utils.c \
	utils2.c \
	utils3.c \
	\

SRC += $(addprefix $(PARSER_DIR), $(PARSER_SRC))

# executor files
EXECUTE_DIR = execute/
EXECUTE_SRC = execute.c \
	execute_builtin.c \
	redirect.c \
	path.c \
	pipes.c \
	heredoc_input.c \
	heredoc_input2.c \
	\

SRC += $(addprefix $(EXECUTE_DIR), $(EXECUTE_SRC))

# utils files
UTILS_DIR = utils/
UTILS_SRC = get_exit_status.c \
	strings_array.c \
	strings_array1.c \
	envp.c \
	fds.c \
	\

SRC += $(addprefix $(UTILS_DIR), $(UTILS_SRC))

# builtins files
BUILTIN_DIR = builtins/
BUILTIN_SRC = cd.c \
	echo.c \
	pwd.c \
	env.c \
	export.c \
	unset.c \
	exit.c \
	\

SRC += $(addprefix $(BUILTIN_DIR), $(BUILTIN_SRC))

OBJS = $(SRC:.c=.o)
INCS = -I$(LIBFT_DIR) -I$(INCLUDES_DIR) -I$(HOME)/.brew/opt/readline/include
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CFLAGS_DEBUG = -Wall -Wextra -Werror -g -fsanitize=address
LFLAGS = -L $(LIBFT_DIR) -L$(HOME)/.brew/opt/readline/lib \
	-lft \
	-lreadline \


%.o:	%.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCS) $(OBJS) $(LFLAGS) -o $(NAME)

$(LIBFT):
	@make -C libft

clean:
	$(RM) $(OBJS)
	@make clean -C libft

fclean:	clean
	$(RM) $(NAME)
	@make fclean -C libft

re:	fclean all

d:
	@make re CFLAGS="$(CFLAGS_DEBUG)"
	@make

v:
	@make re CFLAGS="$(CFLAGS) -g -O0"
	valgrind --leak-check=full -s ./$(NAME)

norm:
	norminette $(SRC) $(HEADERS)

.PHONY:		all clean fclean re debug norm
