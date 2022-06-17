/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalfredi <dalfredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:04:25 by dalfredi          #+#    #+#             */
/*   Updated: 2022/06/16 16:40:14 by dalfredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Includes */
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"

/* Defines */
# define PATH_MAX				1024
# define DEFAULT_PROMPT			"\e[36m$ \e[0m"
# define TMP_FILENAME			".tmp_heredoc"

# define EXIT_INTERRUPTED		130

# define IN						0
# define OUT					1

/* Structures */
enum e_token_type {
	TOKEN = 0,
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_OUTPUT_APPEND,
	REDIR_DELIMITER,
	REDIR_ERROR,
	PIPE,
};

enum e_chars {
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_PIPE = '|',
	CHAR_LESS = '<',
	CHAR_GREAT = '>',
	CHAR_DOLLAR = '$',
};

enum e_parser_expectations {
	EXPECT_OPERATOR = 1,
	EXPECT_TOKEN = 2,
	EXPECT_TOKEN_OR_OPERATOR = 2,
};

enum e_tokenizer_state {
	STATE_GENERAL = 1,
	STATE_QUOTE,
	STATE_DQUOTE,
};

/* Structures */
typedef struct s_token
{
	int				type;
	char			*value;
}	t_token;

typedef struct s_redirect
{
	int		type;
	char	*filename;
}	t_redirect;

typedef struct s_command
{
	char		*name;
	char		**args;
	char		**envp;
	t_list		*redirect_list;
	int			fd[2];
	pid_t		pid;
}	t_command;

typedef struct s_tokenizer
{
	char		*input;
	t_list		*token_list;
	int			state;
	int			token_start;
	char		curr_char;
	size_t		i;
}	t_tokenizer;

typedef struct s_table_builder
{
	int			tok_type;
	char		*tok_value;
	t_command	*cmd;
	int			ret;
	t_list		*command_list;
}	t_table_builder;

typedef struct s_data
{
	char		**envp;
	char		**to_export;
	int			last_exit_status;
	t_list		*command_list;
	int			std_fd[2];
	int			tmp_files_counter;
	int			heredoc_fails;
	int			redirect_fails;
}	t_data;

/* Variables */
extern t_data	g_data;

/* Init */
void		init_all(char **envp);

/* Main functions */
char		*get_line(void);
void		signal_set_input(void);
void		signal_set_execute(void);
void		signal_set_heredoc(void);

/* Enviroment variable managment */
char		*env_get(char *name);

/* Parser */
t_list		*parse(char *input);
void		delete_quote(t_tokenizer *tok, t_token *token);
int			expand_dollar(t_tokenizer *tok);
int			is_operator(char c);
t_tokenizer	*tokenizer_init(char *input);
t_list		*tokenize(char *input);
void		expand_variables(t_list *tokens);
t_list		*build_command_table(t_list *tokens);
void		token_trim_spaces(void *v_token);
void		token_delete_empty(t_list **lst, void (*del)(void *));
void		token_delete(void *v_token);
int			token_is_operator(int token_type);
int			token_is_redirect(int token_type);
void		token_get_value(void *v_token, int *type, char **value);
void		*create_token(int type, char *value);
void		*create_command(char *name, char **args,
				char **envp, t_list *redirect_list);
void		*create_redirect(int type, char *filename);
void		command_delete(void *v_command);

/* Executor */
void		execute(t_list *command_list);
void		make_redirects(t_list *redirect_list);
void		heredoc_input(t_redirect *redirect);
int			redir_input(char *filename, int open_flags);
char		*get_full_path(char	*command);
void		pipes_close_all(void);
void		pipes_create_all(void);
void		set_command_pipes(t_command *cmd);
void		read_all_heredocs(void	*v_command);
void		delete_tmp_files(void	*v_command);
void		heredoc_clean_up(t_redirect *redirect, char *tmp_filename);
void		builtin_execute(t_command *cmd);
int			is_builtin(char *cmd_name);

/* Utils */
char		*get_exit_status(void);
char		*make_prompt(char *prompt);
int			func_error(char *func_name);
void		fds_save_standard(int fds[2]);
void		fds_restore_standard(int fds[2]);
void		fds_close(int fd[2]);

/* String arrays */
int			strs_size(char **strs);
char		**strs_copy(char **strs);
void		strs_append(char ***env, char *value);
void		strs_free(char ***strs);
int			strs_in_list(char *value, char **strs);
void		strs_delete(char ***strs, char *str_to_delete);

/* Enviroment variables */
char		*env_get(char *name);
void		env_change(char *name, char *value);
int			env_set(char *name, char *value);
void		ft_env_remove(char ***strings, char *part);
int			env_delete(char *name);

/* Builtins */
int			echo(char **args);
int			pwd(void);
int			cd(char **args);
int			env(char **env);
int			export(char **list);
int			unset(char **list);
void		exit_builtin(char **code);

#endif
