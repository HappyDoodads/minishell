/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:57:44 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/28 15:54:18 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <limits.h>
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
}			t_command;

///////////////////////////     ENUMS     //////////////////////////////////////

enum e_quote_status
{
	NO_QUOTE = 0,
	DQUOTE = 34,
	QUOTE = 39
};

/**********************************PROTOTYPES**********************************/

///////////////////////////////   ECHO  ///////////////////////////////////

void	ft_echo(char *input);

///////////////////////////////   ERRORS   ///////////////////////////////////

void	free_command(void *data);

///////////////////////////////   EXIT   ///////////////////////////////////

void	ft_exit(char *input);

//////////////////////////////    FREE      ///////////////////////////////////

///////////////////////////////   MINISHELL   //////////////////////////////////

void	ft_create_prompt(void);
int		command_handler(t_list *cmd_list, int fd_arr[MAX_FD]);
void	exec_command(t_command *command, int fd_arr[MAX_FD]);

///////////////////////////////   PARSING   ////////////////////////////////////

t_list	*parse_input(char *input, int fd_arr[MAX_FD]);
char	**split_args(const char *s);

///////////////////////////////   PWD   ////////////////////////////////////

void	ft_pwd(void);

//////////////////////////////    SIGNAL   /////////////////////////////////////

void	sigint_handler(int sig_num);
void	sigquit_handler(int sig_num);

//////////////////////////////    UTILS   /////////////////////////////////////

void	reset_fd_array(int fd_arr[MAX_FD]);
void	add_fd(int fd_arr[MAX_FD], int fd);
int		get_last_fd(int fd_arr[MAX_FD]);
int		close_all(int fd_arr[MAX_FD], int fd1, int fd2);

#endif
