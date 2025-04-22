/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:09:04 by sbrugman          #+#    #+#             */
/*   Updated: 2025/04/09 12:51:17 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

char	*potential_pathing(char *paths, char *command_to_path, int *index)
{
	char	*potential_path;
	int		size;

	size = ft_strlen(paths, *index);
	size += ft_strlen(command_to_path, 0);
	potential_path = malloc((size + 2) * sizeof(char));
	if (potential_path == NULL)
		error("malloc failed", NULL, NULL, -1);
	potential_path[size + 1] = '\0';
	size = 0;
	while (paths[*index] != '\0' && paths[*index] != ':')
	{
		potential_path[size] = paths[*index];
		size++;
		(*index)++;
	}
	if (paths[*index] == ':')
		(*index)++;
	potential_path[size] = '/';
	size++;
	putcommand(command_to_path, potential_path, size);
	return (potential_path);
}

int	find_string(char **env, char *path)
{
	int	index;
	int	index_two;

	index = 0;
	index_two = 0;
	while (env[index][index_two] != '\0' && env[index][index_two] != '=')
	{
		index_two = 0;
		while (path[index_two] != '\0'
			&& env[index][index_two] == path[index_two])
			index_two++;
		if (path[index_two] == '\0')
			return (index);
		index++;
	}
	return (-1);
}

char	*get_path(char *command_to_path, char *paths, int index)
{
	char	*full_path;

	if (command_to_path == NULL || command_to_path[0] == 32)
		return (NULL);
	while (paths[index] != '\0')
	{
		full_path = potential_pathing(paths, command_to_path, &index);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		if (full_path != NULL)
			free(full_path);
	}
	return (NULL);
}

void	process(char **argv, char **env, int *fd)
{
	pid_t	forked;
	pid_t	forker;

	forked = fork();
	if (forked == -1)
		perror("couldn't fork");
	else if (forked == 0)
		child_process(argv, env, fd);
	forker = fork();
	if (forker == 0)
		second_child(argv, env, fd);
	else if (forker == -1)
		perror("couldn't fork");
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
}

int	main(int argc, char **argv, char **env)
{
	int	fd[2];

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			perror("couldn't pipe");
		process(argv, env, fd);
	}
	else
		write(2, "Error bad format", 17);
	return (0);
}
