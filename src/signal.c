
#include "minishell.h"

void	sigint_handler(int sig_num)
{
	(void)sig_num;
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int sig_num)
{
	(void)sig_num;
	rl_redisplay();
	return ;
}
