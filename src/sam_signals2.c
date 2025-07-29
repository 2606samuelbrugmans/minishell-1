#include "../inc/minishell.h"
void sigint_heredoc_handler(int signum)
{
    (void)signum;
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
	write(1, "\n", 1);
    exit(130);
}
void	heredoc_signals(void)
{
	signal(SIGINT, sigint_heredoc_handler);
	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	enable_echoctl();
}
void	silence_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

}