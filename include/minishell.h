
#ifndef MINISHELL_H
# define MINISHELL_H

/////////////////////////      DEFINES     ///////////////////////////////////

# define PWD "pwd"
# define EXIT "exit"

//////////////////////////     INCLUDES    ////////////////////////////////////

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

///////////////////////////     COLORS    ////////////////////////////////////

# define RST "\e[0m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define YELLOW "\e[1;33m"
# define BLUE "\e[1;34m"
# define MAGENTA "\e[1;35m"
# define CYAN "\e[1;35m"
# define WHITE "\e[1;36m"

///////////////////////////////////STRUCTURES///////////////////////////////////

typedef struct s_envp
{
	char	*name;
	char	*val;
}			t_envp;

typedef struct s_command
{
	char	**argv;
	int		pipe_L[2];
	int		pipe_R[2];
	char	*infile;
	char	*outfile;
	bool	append_out;
	pid_t	pid;
}			t_command;

typedef struct s_misc
{
	char	**envp;
	int		prev_status;
	t_list	*cmd_list;
	int		tmpfile_count;
	char	tmpfile_dir[PATH_MAX];
}			t_misc;

///////////////////////////     ENUMS     //////////////////////////////////////

enum e_quote_status
{
	NO_QUOTE = 0,
	DQUOTE = 34,
	QUOTE = 39
};

/**********************************PROTOTYPES**********************************/

///////////////////////////////   BUILTINS   ///////////////////////////////////

int		ft_cd(t_command *cmd, t_misc *misc);
int		ft_pwd(t_command *cmd, t_misc *misc);
int		ft_env(t_command *cmd, t_misc *misc);
int		ft_echo(t_command *cmd, t_misc *misc);
int		ft_export(t_command *cmd, t_misc *misc);
int		ft_unset(t_command *cmd, t_misc *misc);
int		ft_exit(t_command *cmd, t_misc *misc);

void	ft_ascii_sort(t_command *cmd, t_misc *misc);
void	replace_env_var(char **envar_addr, char *var_name, char *var_value);
void	ft_loopenv(t_misc *misc, char *v_name, char *v_val);
bool	ft_isvalid_envname(const char *var_name, const char *context);

///////////////////////////////   ERRORS    ////////////////////////////////////

int		print_err(const char *s1, const char *s2, const char *msg);
void	set_statcode(int errnum, t_misc *misc);

///////////////////////////////    EXEC    /////////////////////////////////////

int		exec_builtin(t_command *command, t_misc *misc);
void	exec_command(t_command *command, t_misc *misc);

////////////////////////////////   FREE    /////////////////////////////////////

void	free_command(void *data);
void	free_envp(t_envp *envp);
void	cleanup(t_misc *misc);
void	ft_close(int fd);
void	close_pipe(int pipefd[2]);
void	delete_tmpfiles(t_misc *misc);

/////////////////////////////    HEREDOC   //////////////////////////////

int		ft_heredoc(char *eof, t_misc *misc, char **storage);

///////////////////////////////     MAIN     //////////////////////////////////

char	**dup_envp(char **envp);

///////////////////////////////   MINISHELL   //////////////////////////////////

void	ft_create_prompt(t_misc *misc);
int		command_handler(t_misc *misc);

///////////////////////////////   PARSING   ////////////////////////////////////

int		quote_skip(char *line, int i);
t_list	*parse_input(char *input, t_misc *misc);
char	**split_args(const char *s, t_misc *misc);
int		redirect_parsing(char *cmd_str, t_command *cmd, t_misc *misc);
char	*substitute(char *arg, t_misc *misc, bool quote_flag);

/////////////////////////////   REDIRECTING   //////////////////////////////////


//////////////////////////////    SIGNAL    ////////////////////////////////////

void	sigint_handler(int sig_num);
void	sig_child_handler(int sig_num);
void	sig_heredoc_handler(int sig_num);
int		rl_replace_line(const char *text, int clear_undo);

//////////////////////////////    UTILS    /////////////////////////////////////

#endif
