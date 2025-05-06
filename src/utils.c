/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:54:24 by scesar            #+#    #+#             */
/*   Updated: 2025/05/06 20:39:26 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    run_command(char **tab_input)
{
    pid_t   pid;
    int status;

    if (!tab_input || !tab_input[0])
        return;
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }
    else if (pid == 0)
    {
        if (execve(tab_input[0], tab_input, NULL) == -1)
        {
            perror("execve");
            return;
        }
    }
    else
        waitpid(pid, &status, 0);
}

char *ft_delchar(char *str, char to_del)    //need to free str after (using a temp before calling fct)
{
    size_t index;
    size_t index_res;
    size_t new_size;
    char *res;

    index = 0;
    index_res = 0;
    while (str[index])
    {
        if(str[index] != to_del)
        new_size++;
        index++;
    }
    new_size++;
    index = 0;
    res = malloc(sizeof(char) * new_size);
    if (!res)
        return(NULL);
    while (index < new_size)
    {
        if(str[index] != to_del)
        {
            res[index_res] = str[index];
            index ++;
        }
        index_res ++;
    }
    res[index_res] = '\0';
    return(res);
}
