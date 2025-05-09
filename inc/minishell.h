/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:04:18 by scesar            #+#    #+#             */
/*   Updated: 2025/05/09 13:26:46 by scesar           ###   ########.fr       */
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
//watch out if it does equal CMD in enum, idrk

typedef struct s_shell
{
    char **env;
}               t_shell;

typedef enum e_token_type
{
    NONE = -1,
    CMD,
    FLAG,
    PIPE,
    REDIR_OUT,
    REDIR_IN,
    HEREDOC,
    APPEND,
    FILENAME,
    
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
int tok_type_init(char **tab_input, t_commands *commands, size_t index);
t_commands    tokenizer(char *input);



char *ft_delchar(char *str, char to_del);
size_t ft_countchar(char *str, char to_count);
int special_char(char *input, size_t index);

size_t tab_size(char **tab);
void free_tab(char **tab);

#endif