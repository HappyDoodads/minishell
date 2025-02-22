/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:48:09 by jdemers           #+#    #+#             */
/*   Updated: 2024/07/22 14:52:25 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

///////////////////////////      DEFINES     ///////////////////////////////////

# define PWD "pwd"
# define EXIT "exit"

///////////////////////////     INCLUDES    ////////////////////////////////////

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

/////////////////////////////     COLORS    ////////////////////////////////////

# define RST "\e[0m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define YELLOW "\e[1;33m"
# define BLUE "\e[1;34m"
# define MAGENTA "\e[1;35m"
# define CYAN "\e[1;35m"
# define WHITE "\e[1;36m"

///////////////////////////////////STRUCTURES///////////////////////////////////
int	g_status;

typedef struct s_heredoc
{
	char	*file;
	char	*eof;
	bool	has_quotes;
}			t_heredoc;

typedef struct s_envp
{
	char	*name;
	char	*val;
}			t_envp;

typedef struct s_command
{
	char	**argv;
	int		pipe_l[2];
	int		pipe_r[2];
	char	*infile;
	char	*outfile;
	bool	append_out;
	pid_t	pid;
}			t_command;

typedef struct s_misc
{
	t_envp	*envp;
	t_list	*cmd_list;
	t_list	*heredoc_list;
	int		envp_size;
	char	tmpfile_path[PATH_MAX];
	int		tmpfile_count;
	bool	exit_flag;
	char	*delet_this;
}			t_misc;

///////////////////////////     ENUMS     //////////////////////////////////////

enum e_quote_status
{
	NO_QUOTE = 0,
	DQUOTE = 34,
	SQUOTE = 39,
};

enum e_substitute_flag
{
	FILENAME = 42,
	NO_SUBST = 43,
	CMD_STR = 101,
	IN_HEREDOC = 418,
};

enum e_redirect_type
{
	INPUT = 60,
	HEREDOC,
	OUTPUT,
	APPEND,
};

/**********************************PROTOTYPES**********************************/

///////////////////////////////   BUILTINS   ///////////////////////////////////

int			ft_cd(t_command *cmd, t_misc *misc);
int			ft_pwd(t_command *cmd, t_misc *misc);
int			ft_env(t_command *cmd, t_misc *misc);
int			ft_echo(t_command *cmd, t_misc *misc);
int			ft_export(t_command *cmd, t_misc *misc);
int			ft_unset(t_command *cmd, t_misc *misc);
int			ft_exit(t_command *cmd, t_misc *misc);

bool		ft_isvalid_envname(const char *var_name, const char *context);
int			export_loopenv(t_misc *misc, const char *v_name, const char *v_val);
char		**ss_envp_creat(const t_envp *envp);
void		ascii_sort(const t_envp *envp, int fd_out);
const char	*envp_getval(const t_envp *envp, const char *v_name);
///////////////////////////////   ERRORS    ////////////////////////////////////

int			print_err(const char *s1, const char *s2, const char *msg);
void		set_stat(int errnum);
int			execve_errno(const char *cmd_name);

///////////////////////////////    EXEC    /////////////////////////////////////

int			exec_builtin(t_command *command, t_misc *misc);
void		exec_command(t_command *command, t_misc *misc);

////////////////////////////////   FREE    /////////////////////////////////////

void		free_command(void *data);
void		free_heredoc(void *data);
void		free_envp(t_envp *envp);
void		cleanup(t_misc *misc);
void		delete_tmpfiles(t_misc *misc);

////////////////////////////////    HEREDOC   //////////////////////////////////

char		*ft_heredoc(char *eof, t_misc *misc);
int			heredoc_fork(t_heredoc *heredoc, t_misc *misc);

///////////////////////////////   MINISHELL   //////////////////////////////////

int			command_handler(t_misc *misc);

///////////////////////////////   PARSING   ////////////////////////////////////

int			quote_skip(char *line, int i);
t_list		*parse_input(char *input, t_misc *misc);
char		**split_args(const char *s, t_misc *misc);
int			redirect_parsing(char *cmd_str, t_command *cmd, t_misc *misc);
char		*substitute(char *arg, t_misc *misc, int flag);

//////////////////////////////    SIGNAL    ////////////////////////////////////

void		sigint_handler(int sig_num);
void		sig_child_handler(int sig_num);
int			rl_replace_line(const char *text, int clear_undo);
void		rl_clear_history(void);

//////////////////////////////    PIPES_UTILS    ///////////////////////////////

void		ft_close(int fd);
void		close_pipe(int pipefd[2]);
void		close_cmd_pipes(t_command *cmd);

#endif
