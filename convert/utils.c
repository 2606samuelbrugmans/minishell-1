/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:54:24 by scesar            #+#    #+#             */
/*   Updated: 2025/06/12 01:05:26 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char *ft_delchar(char *str, char to_del)
{
    //need to free str after (using a temp before calling fct)
    size_t index;
    size_t index_res;
    size_t new_size;
    char *res;

    index = 0;
    index_res = 0;
    new_size = ft_strlen(str) - ft_countchar(str, to_del) + 1;
    res = malloc(sizeof(char) * new_size);
    if (!res)
        return(NULL);
    while (str[index])
    {
        if(str[index] != to_del)
        {
            res[index_res] = str[index];
            index_res ++;
        }
        index ++;
    }
    res[index_res] = '\0';
    return(res);
}

size_t ft_countchar(char *str, char to_count)
{
    size_t res;
    size_t index;

    res = 0;
    index = 0;
    while(str[index])
    {
        if (str[index] == to_count)
            res++;
        index++;
    }
    return (res);
}

size_t tab_size(char **tab)
{
    size_t index;

    index = 0;

    while (tab[index])
        index++;
    return(index);
}

int special_symb(char *input, size_t index)
{

    if (input[index] == '<' )
    {
        if(input[index + 1] && input[index + 1] == '<' )
            return(HEREDOC);
        else
            return (REDIR_IN);
    }
    else if(input[index] == '>' )
    {
        if(input[index + 1] && input[index + 1] == '>')
            return(APPEND);
        else
            return (REDIR_OUT);
    }
    if(input[index] == '|' ) //put strcmp ? bc compare a char to a char*
        return(PIPE);
    else
        return(NONE);
}

int special_symb_2(char *input)
{
    size_t len;

    len = ft_strlen(input);
    if (ft_strncmp(input, "<", len) == 0)
        return (REDIR_IN);
    if (ft_strncmp(input, ">", len) == 0)
        return (REDIR_OUT);
    if (ft_strncmp(input, ">>", len) == 0)
        return (APPEND);
    if (ft_strncmp(input, "<<", len) == 0)
        return (HEREDOC);
    if (ft_strncmp(input, "|", len) == 0)
        return (PIPE);
    else
        return(NONE);
}

char *fill_renew_str(char *last_str, size_t len_var, t_env * actual_var)
{
    char *renew_str;
    size_t len_value;

    if (actual_var == NULL)
        len_value = 0;
    else
        len_value = ft_strlen(actual_var->value);
    renew_str = malloc(sizeof(char) * (ft_strlen(last_str) - len_var + len_value - 1 + 1)); // (-1 + 1) = (-$ +'\0')
    // in progress.............
}

char    *replace_var(t_env *minish_local_var, char *string, size_t *str_ind, char *new_str, size_t *new_str_ind)
{
    size_t len_var;
    t_env *actual_var;
    char *pres_var;
    char *renew_str;

    len_var = 0;
    renew_str = NULL;
    (*str_ind)++;
    while(string[*str_ind + len_var] && string[*str_ind + len_var] != ' ')
        len_var++;
    pres_var = ft_substr(string, *str_ind, len_var);
    if(!pres_var)
        return(NULL);       //malloc error;
    (*str_ind) += len_var;
    actual_var = get_VAR(minish_local_var, pres_var);
    if(!actual_var)
        renew_str = fill_renew_str(new_str, len_var, NULL);
    else
        renew_str = fill_renew_str(new_str, len_var, actual_var);
    if(!renew_str)
        return(NULL);       //malloc error;
    //find a way to update new_str_ind
    return(renew_str);
    }


char    *get_new_string(t_env *minish_local_var, char *string) // in progress
{
    char *temp;
    char *new_str;
    size_t str_ind;
    size_t new_str_ind;

    str_ind = 0;
    temp = string;
    new_str = NULL;
    while (string[str_ind])
    {
        if(string[str_ind] == '$' && (string[str_ind] && string[str_ind] != ' '))
        {
            temp = new_str;
            new_str = replace_var(minish_local_var, string, &str_ind, temp, &new_str_ind);
            free(temp);
        }
        if(string[str_ind] == '\'')
            end_quotes(string, &str_ind);
        str_ind++;
    }
    if (!temp)
        free(temp);
}
// int special_symb(char c)
// {
//     if(c == '<' )
//         return(REDIR_IN);
//     if(c == '>' )
//         return(REDIR_OUT);
//     if(c == '|' )
//         return(PIPE);
//     else
//         return(NONE);
// }
