#include "../inc/minishell.h"

void heredoc_child(char *stop, int write_fd)
{
	char *line;

	heredoc_signals(); // set proper signals for heredoc input

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, stop) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
}