/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:54:24 by scesar            #+#    #+#             */
/*   Updated: 2025/04/27 15:44:54 by scesar           ###   ########.fr       */
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