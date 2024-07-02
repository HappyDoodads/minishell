#include "minishell.h"

void	sigint_handler(int sig_num)
{
	(void)sig_num;
	rl_on_new_line();
	ft_dprintf(1, "\n");
	rl_replace_line("", 0);
	rl_redisplay();
}
void	sig_child_handler(int sig_num)
{
	(void)sig_num;
	rl_redisplay();
	ft_dprintf(1, "\n");
}

void	sig_heredoc_handler(int sig_num)
{
	(void)sig_num;
	ft_dprintf(1, "\n");
	exit (0);
}