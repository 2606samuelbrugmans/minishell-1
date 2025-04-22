/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:54:24 by scesar            #+#    #+#             */
/*   Updated: 2025/04/22 16:26:36 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

////////////////////////////////////////////////////////////////////
//ft_split_shell in the making...
size_t nbr_of_elem(char *input)
{
    size_t index;
    size_t res;
    
    index = 0;
    res = 0;
    while(input[index])
    {
        if (input[index] == "\'")
        {
            while(input[index] != "\'" || input[index] != '\0')
                index++;
            res++;
        }
        else if (input[index] == "\"" || input[index] != '\0')
        {
            while(input[index] != "\"")
                index++;
            res++;
        }
        while(input[index] != ' ' && input[index] != '\0')
            res++;
    }
    return(res);
}

char **ft_split_shell(char *input)
{
	size_t	index;
    char **tab_of_elem;
    
    tab_of_elem = (char**)malloc(sizeof(char *) * (nbr_of_elem(input) + 1));
}
////////////////////////////////////////////////////////////////////

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