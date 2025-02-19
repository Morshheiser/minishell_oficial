NAME	=	minishell

CC		= 	cc

CFLAGS	=	-Wall -Wextra -Werror -g

RM		=	rm -f

LIBRARY	=	./libft/

SRCS	=	./src/builtins/ft_cd.c\
			./src/builtins/ft_echo.c\
			./src/builtins/ft_env.c\
			./src/builtins/ft_exit.c\
			./src/builtins/ft_export.c\
			./src/builtins/ft_builtins.c\
			./src/builtins/ft_pwd.c\
			./src/builtins/ft_unset.c\
			./src/cleanup/cleanup_cmd.c\
			./src/cleanup/cleanup_env.c\
			./src/cleanup/cleanup_fd.c\
			./src/cleanup/cleanup_shell.c\
			./src/utils/ft_alloc_utils.c\
			./src/utils/ft_cmd_utils.c\
			./src/utils/ft_env_utils.c\
			./src/utils/ft_pid_utils.c\
			./src/utils/ft_free_utils.c\
			./src/env/ft_utils_env_1.c\
			./src/env/ft_utils_env.c\
			./src/env/ft_find_env.c\
			./src/env/ft_init_env.c\
			./src/executor/ft_executer.c\
			./src/executor/ft_executor_utils_1.c\
			./src/executor/ft_executor_utils.c\
			./src/executor/ft_get_path_name.c\
			./src/expansion/ft_expansion.c\
			./src/expansion/ft_expan_two_quote.c\
			./src/expansion/ft_expan_env.c\
			./src/expansion/ft_expan_one_quote.c\
			./src/expansion/ft_expan_txt.c\
			./src/expansion/ft_merge.c\
			./src/lexer/ft_lexer.c\
			./src/main/main.c\
			./src/main/ft_check_space.c\
			./src/main/ft_error_utils.c\
			./src/main/ft_set_prompt.c\
			./src/main/ft_start_shell.c\
			./src/parser/ft_parser.c\
			./src/parser/ft_heredoc.c\
			./src/parser/ft_process_cmd.c\
			./src/parser/ft_prompt_split.c\
			./src/parser/ft_config_redir.c\
			./src/parser/ft_find_quote.c\
			./src/signals/ft_signal_handler.c\
			./src/signals/ft_signal.c\
		
all: $(NAME)

libft:
	cd $(LIBRARY) && $(MAKE) && cp -v libft.a ../

minishell: libft
	cc -g $(SRCS) libft.a -lreadline -o $(NAME)

run: re
	./$(NAME)

val: re
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=supressions.supp --track-fds=yes ./$(NAME)

norm:
	@-norminette -R CheckForbiddenSourceHeader

clean:
	cd $(LIBRARY) && $(MAKE) clean

fclean:	clean
	$(RM) $(NAME)
	$(RM) libft.a
	cd $(LIBRARY) && $(MAKE) fclean

re:	fclean all

.PHONY:	all clean fclean re libft