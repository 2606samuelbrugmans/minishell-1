/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:04:18 by scesar            #+#    #+#             */
/*   Updated: 2025/05/08 18:56:07 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../Libft/inc/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>

# define PATH_MAX 4096

# define NOPE 0
# define NONE 0
//watch out if it does equal CMD in enum, idrk

typedef struct s_shell
{
    char **env;
}               t_shell;

typedef enum e_token_type
{
    CMD,
    FLAG,
    PIPE,
    REDIR_OUT,
    REDIR_IN,
    HEREDOC,
    APPEND,
    
}            t_token_type;

typedef struct s_token
{
    char *content;
    t_token_type  type;
}               t_token;

typedef struct s_commands
{
    t_token **args;
    bool valid;
    
}               t_commands;


//split_shell
char **ft_split_shell(char *input);
size_t nbr_of_elem(char *input);
int    put_elem_in_tab(char **tab, size_t tab_index, char *input, size_t *input_index);
size_t next_arg_len(char *input, size_t index);
void free_tab(char **tab);

char *ft_delchar(char *str, char to_del);
size_t ft_countchar(char *str, char to_count);
int special_char(char c)

size_t tab_size(char **tab);

#endif