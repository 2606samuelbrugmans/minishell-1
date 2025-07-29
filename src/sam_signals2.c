#include "../inc/minishell.h"

void	heredoc_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	enable_echoctl();
}
