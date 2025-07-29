/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SAM_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:33:26 by scesar            #+#    #+#             */
/*   Updated: 2025/07/17 17:51:55 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
// Disable readline's default signal handlers

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "^C\n", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();

}
// if the line buffer is not empty
	/// print "Quit: 3" and exit with status 131
	// this is the behavior for Ctrl+\ (SIGQUIT)
	// Do nothing if prompt is empty

void	sigquit_handler(int sig)
{
	(void)sig;
	write(1, "Quit: 3\n", 8);
}

void	enable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
int	handle_exit_status(int status)
{
	int sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			write(2, "Quit (core dumped)\n", 20);
		else if (sig == SIGINT)
			write(2, "\n", 1);
		return (128 + sig);
	}
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	enable_echoctl();
}

// Note: Handle Ctrl+D (EOF) in your main loop:
// if (!input) { exit/relaunch }eeeee
