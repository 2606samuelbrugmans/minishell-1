/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:28:51 by stephen           #+#    #+#             */
/*   Updated: 2025/04/25 20:07:32 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;
	size_t	len_s;

	if (!s)
		return (NULL);
	len_s = len;
	if (len > ft_strlen(s) - start)
		len_s = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	new_str = malloc(sizeof(char) * (len_s + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len && *(s + start) && start < ft_strlen(s))
	{
		new_str[i] = *(char *)(s + start);
		s++;
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}