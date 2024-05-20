/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquet <jcoquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:57:44 by jcoquet           #+#    #+#             */
/*   Updated: 2024/05/17 11:43:58 by jdemers          ###   ########.fr       */
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

# define RST "\033[0m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;35m"
# define WHITE "\033[1;36m"

///////////////////////////////////STRUCTURES///////////////////////////////////

typedef struct s_command
{
	char	*argv;
	int		fd_in;
	int		fd_out;
}			t_command;

/**********************************PROTOTYPES**********************************/

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

//////////////////////////////    UTILS   /////////////////////////////////////

#endif
