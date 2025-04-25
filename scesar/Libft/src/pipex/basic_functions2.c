/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:00:26 by sbrugman          #+#    #+#             */
/*   Updated: 2025/04/09 12:51:30 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	index;
	size_t	src_len;

	src_len = 0;
	index = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (dstsize == 0)
		return (src_len);
	while (index < dstsize - 1 && src[index] != '\0')
	{
		dst[index] = src[index];
		index++;
	}
	if (dstsize > 0)
		dst[index] = '\0';
	return (src_len);
}

void	putcommand(char *command_to_path, char *potential_path, int size)
{
	int	j;

	j = 0;
	while (command_to_path[j] != '\0' && command_to_path[j] != ' ')
	{
		potential_path[size + j] = command_to_path[j];
		j++;
	}
}
