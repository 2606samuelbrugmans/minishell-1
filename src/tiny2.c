#include "../inc/minishell.h"

int	is_interactive(t_minishell *minish)
{
	return (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && minish->non_inter == 0);
}
void	set_non_interactive(t_minishell **minish, int ac, char **av)
{
	if (ac == 3 && ft_strcmp(av[1], "-c") == 0)
	{
		(*minish)->non_inter = 1;
		treat_input(minish, av[2]);
	}
	else
	{
		(*minish)->non_inter = 0;
	}
}
int	cleanup_and_exit(t_minishell *minish)
{
	int	exit;

	if (minish->non_inter == 0)
		printf("exit\n");
	exit = minish->last_exit_status;
	free_minish_total(&minish);
	return (exit);
}

int	is_directory(const char *path)
{
	struct stat	info;

	if (stat(path, &info) != 0)
		return (0); // error: file doesn't exist or can't stat
	return (S_ISDIR(info.st_mode));
}