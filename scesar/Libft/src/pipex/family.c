/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:04:55 by sbrugman          #+#    #+#             */
/*   Updated: 2025/04/09 13:26:23 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	index;
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	index = 0;
	while (index < len)
	{
		write(fd, &s[index], 1);
		index++;
	}
}

void	error(char *reason, char **args, char *path, int file)
{
	int	index;

	index = 0;
	ft_putstr_fd(reason, 2);
	if (path)
		free(path);
	if (args)
	{
		while (args[index] != NULL)
		{
			free(args[index]);
			index++;
		}
		free(args);
	}
	if (file != -1)
		close(file);
	exit(-1);
}

void	child_process(char **argv, char **env, int *fd)
{
	int		openfile;
	char	*path;
	char	**args;

	if (access(argv[1], F_OK) == 0)
	{
		if (access(argv[1], R_OK) != 0)
			error("permission denied:", NULL, NULL, -1);
	}
	openfile = open(argv[1], O_RDONLY, 0644);
	if (openfile == -1)
		error("no such file or directory:", NULL, NULL, -1);
	args = ft_split(argv[2], ' ');
	if (access(args[0], F_OK) == 0)
		path = args[0];
	else
		path = path_finding(argv, env, 1);
	if (path == NULL)
		error("command not found:", args, NULL, openfile);
	dup2(openfile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	execute(path, args, openfile);
}

void	execute(char *path, char **args, int file)
{
	int	execror;

	execror = execve(path, args, NULL);
	if (execror == -1)
		error("execution failed", args, path, file);
}

void	second_child(char **argv, char **env, int *fd)
{
	int		writefile;
	char	*path;
	char	**args;

	if (access(argv[4], F_OK) == 0)
	{
		if (access(argv[4], W_OK) != 0)
			error("permission denied:", NULL, NULL, -1);
	}
	writefile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (writefile == -1)
		error("Error opening the file", NULL, NULL, -1);
	args = ft_split(argv[3], ' ');
	if (access(args[0], F_OK) == 0)
		path = args[0];
	else
		path = path_finding(argv, env, 2);
	if (path == NULL)
		error("command not found:", args, NULL, writefile);
	dup2(fd[0], STDIN_FILENO);
	dup2(writefile, STDOUT_FILENO);
	close(fd[1]);
	execute(path, args, writefile);
}
