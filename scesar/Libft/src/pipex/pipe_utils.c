/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:06:34 by sbrugman          #+#    #+#             */
/*   Updated: 2025/04/09 12:51:23 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

char	*path_finding(char **argv, char **env, int who)
{
	int		path;
	char	*full_path;

	path = find_string(env, "PATH");
	if (path == -1)
		return (NULL);
	if (who == 1)
		full_path = get_path(argv[2], env[path], 5);
	else
		full_path = get_path(argv[3], env[path], 5);
	return (full_path);
}
