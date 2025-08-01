/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:01:27 by scesar            #+#    #+#             */
/*   Updated: 2025/07/23 20:39:58 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*path_finding(char *pathed, t_env **envp)
{
	t_env		*path;
	char		*full_path;

	if (access(pathed, F_OK) == 0 && ft_strchr(pathed, '/'))
	{
		if (is_directory(pathed))
		{
			ft_printf(2, "%s: Is a directory\n", pathed);
			exit(126);
		}
		if (access(pathed, X_OK) == 0)
			return (ft_strdup(pathed));
		else
		{
			ft_printf(2, "Permission denied");
			exit(126);
		}
	}
	path = get_var(envp, NULL, "PATH");
	if (path == NULL)
		return (NULL);
	full_path = get_path(pathed, path->value, 5);
	if (full_path == pathed)
		return (NULL);
	return (full_path);
}

char	*potential_pathing(char *paths, char *command_to_path, int *index)
{
	char	*potential_path;
	int		size;

	size = path_len(paths, *index);
	size += ft_strlen(command_to_path);
	potential_path = malloc((size + 2) * sizeof(char));
	if (potential_path == NULL)
		return (NULL);
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
