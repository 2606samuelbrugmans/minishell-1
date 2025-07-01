#include "../inc/minishell.h"

int	run(t_minishell *minish)
{
	int i;

	i = 0;
	if (built_in_parent(minish->instru[0].executable[0]->content) && minish->number_of_commands == 1)
		exec_builtin(minish->instru[0].executable, minish);
	else
	{
		// print_minishell(minish);
		while (i < minish->number_of_commands)
		{
			if (pipe(minish->fd_pipes[i]) == -1 )
				perror("bablda");				//put an actual message here
			i++;
		}
		process(minish);
	}
	return (0);
}

void	process(t_minishell *minish)
{
	pid_t	forked;
	int		parser;
	int		index;

	parser = 0;
	while (parser < minish->number_of_commands)
	{
		forked = fork();
		if (forked == -1)
			perror("couldn't fork");		//put an actual message here
		else if (forked == 0)
			child_process(minish, &minish->instru[parser], parser);
		parser++;
	}
	index = 0;
	close_parent(minish);
	while (index < minish->number_of_commands)
	{
		wait(NULL);
		index++;
	}
}

void	child_process(t_minishell *minish, t_instructions *instr, int parser)
{
	// in the parsing should test if the path is absolute
	if (is_builtin(instr->executable[0]->content))
		instr->path_command = instr->executable[0]->content;
	else if (access(instr->executable[0]->content, F_OK) == 0)		//should be X_OK no ? what if PATH is unset ?
		instr->path_command = instr->executable[0]->content;
	else
		instr->path_command = path_finding(instr->executable[0]->content, &minish->envp);
	access_test(minish, instr, parser);
	no_redirection_proc(minish, instr, parser);
	if (is_builtin(instr->path_command))
		exec_builtin(instr->executable, minish);
	else
		execute(minish, instr, parser);
}

void	execute(t_minishell *minish, t_instructions *instr, int parser)
{
	int	execror;

	write(2, "reached execution\n", 19);			//see if still necessary
	execror = execve(instr->path_command, instr->exec, NULL);
	if (execror == -1)
		error(minish, "execution failed", parser);
}

void close_parent(t_minishell *minish)
{
	int i;

	i = 0;
	while (i < minish->number_of_commands)
	{
		close(minish->fd_pipes[i][0]);
		close(minish->fd_pipes[i][1]);
        i++;
	}
}

void close_stuff(t_minishell *minish, int parser)
{
	int i;

	i = 0;
	while (i < minish->number_of_commands)
	{
		if (i != parser - 1)
			close(minish->fd_pipes[i][0]); // not reading from this
		if (i != parser)
			close(minish->fd_pipes[i][1]); // not writing to this
        i++;
	}
}

void	error(t_minishell *minish, char *reason, int parser)
{
	int	index;

	index = 0;
	ft_putstr_fd(reason, 2);
	if (minish->instru[parser].path_command)
		free(minish->instru[parser].path_command);
	if (minish->instru[parser].executable)
	{
		while (minish->instru[parser].executable[index] != NULL)
		{
			free(minish->instru[parser].executable[index]);
			index++;
		}
		free(minish->instru[parser].executable);
	}
	exit(-1);
}

