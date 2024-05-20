/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:57:44 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/20 18:34:49 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/////////////////////////      DEFINES     ///////////////////////////////////

# define PWD "pwd"
# define EXIT "exit"

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
	int		fd_in;
	int		fd_out;
}			t_command;

///////////////////////////     ENUMS     //////////////////////////////////////

enum e_quote_status
{
	NO_QUOTE = 0,
	SQUOTE,
	DQUOTE
};

/**********************************PROTOTYPES**********************************/

///////////////////////////////   ECHO  ///////////////////////////////////

void	ft_echo(char *input);

///////////////////////////////   ERRORS   ///////////////////////////////////

///////////////////////////////   EXIT   ///////////////////////////////////

void	ft_exit(char *input);

//////////////////////////////    FREE      ///////////////////////////////////

///////////////////////////////   MINISHELL   //////////////////////////////////

void	ft_create_prompt(void);
int		command_handler(char *input);

///////////////////////////////   PARSING   ////////////////////////////////////

///////////////////////////////   PWD   ////////////////////////////////////

void	ft_pwd(void);

//////////////////////////////    SIGNAL   /////////////////////////////////////

void	sigint_handler(int sig);
void	signal_handler(int signal, siginfo_t *info, void *ucontext);
void	sigint_handler(int sig);

//////////////////////////////    UTILS   /////////////////////////////////////

#endif
