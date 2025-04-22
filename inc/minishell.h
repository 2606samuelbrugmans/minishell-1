/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:04:18 by scesar            #+#    #+#             */
/*   Updated: 2025/04/22 15:26:38 by scesar           ###   ########.fr       */
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

typedef struct s_shell
{
    char **env;
}               t_shell;

typedef struct s_commands
{
    char *args;
    int infile;
    int outfile;
    bool valid;
    
}               t_commands;

typedef enum e_tok_type
{
    TOK_PIPE,
    TOK_REDIR_OUT,
    TOK_REDIR_IN,
    TOK_SINGLE_QUOTE,
    TOK_DOUBLE_QUOTE,
    TOK_HEREDOC,
    TOK_APPEND,
    
}            t_tok_type;

typedef struct s_token
{
    char *token;
    t_tok_type  type;
}               t_token;


#endif