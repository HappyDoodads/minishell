
#ifndef MINISHELL_H
# define MINISHELL_H

/////////////////////////      DEFINES     ///////////////////////////////////

# define PWD "pwd"
# define EXIT "exit"
# ifndef MAX_FD
#  define MAX_FD 256
# endif
# define STDIN_DUP 3
# define STDOUT_DUP 4

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
# include "../libft/include/libft.h"

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

typedef struct s_command
{
	char	**argv;
	int		rd_fd;
	int		wr_fd;
	char	*infile;
	char	*outfile;
	bool	append_out;
}			t_command;

typedef struct s_misc
{
	int		fd_arr[MAX_FD];
	char	**envp;
	int		prev_status;
	t_list	*cmd_list;
	int		tmpfile_count;
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
int		ft_pwd(t_command *cmd);
int		ft_env(t_command *cmd, t_misc *misc);
int		ft_echo(t_command *cmd);
int		ft_export(t_command *cmd, t_misc *misc);
int		ft_unset(t_command *cmd, t_misc *misc);
int		ft_isvalid_envname(char *var_name);
int		ft_exit(t_command *cmd, t_misc *misc);

void	ft_ascii_sort(t_command *cmd, t_misc *misc);
void	replace_env_var(char **envar_addr, char *var_name, char *var_value);
void	ft_loopenv(t_misc *misc, char *v_name, char *v_val);
///////////////////////////////   ERRORS    ////////////////////////////////////

///////////////////////////////    EXEC    /////////////////////////////////////

int		exec_builtin(t_command *command, t_misc *misc);
void	exec_command(t_command *command, t_misc *misc);

////////////////////////////////   FREE    /////////////////////////////////////

void	free_command(void *data);

/////////////////////////////    HEREDOC   //////////////////////////////

int		ft_heredoc(char *eof, t_misc *misc, char **storage);

///////////////////////////////     MAIN     //////////////////////////////////

char	**dup_envp(char **envp);

///////////////////////////////   MINISHELL   //////////////////////////////////

void	ft_create_prompt(t_misc *misc);
int		command_handler(t_misc *misc);

///////////////////////////////   PARSING   ////////////////////////////////////

t_list	*parse_input(char *input, int fd_arr[MAX_FD]);
char	**split_args(const char *s);

/////////////////////////////   REDIRECTING   //////////////////////////////////


//////////////////////////////    SIGNAL    ////////////////////////////////////

void	sigint_handler(int sig_num);
void	sigquit_handler(int sig_num);

//////////////////////////////    UTILS    /////////////////////////////////////

void	reset_fd_array(int fd_arr[MAX_FD]);
void	add_fd(int fd_arr[MAX_FD], int fd);
int		get_last_fd(int fd_arr[MAX_FD]);
int		close_all(int fd_arr[MAX_FD], int fd1, int fd2);
char	**get_envp(void);

#endif
