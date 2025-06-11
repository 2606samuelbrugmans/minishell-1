#ifndef MINISHELL_SCESAR_H
# define MINISHELL_SCESAR_H
# include "../Libft/inc/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <limits.h>

# define PATH_MAX 4096

# define YES 1
# define NOPE 0
# define INVALID_ARG -1
//watch out if it does equal CMD in enum, idrk

// typedef struct s_commands   t_commands;
typedef struct s_myinstructions   t_myinstructions;

typedef struct s_shell
{
    char **env;
}               t_shell;

typedef enum e_token_type
{
    NONE = -1,
    CMD,
    ARG,
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
    char *as_str;
    t_token **args;
    struct s_commands *next_command;

}               t_commands;

typedef struct s_env
{
    char *VAR;
    char *value;
    struct s_env *next;
}              t_env;


typedef struct s_myinstructions
{
	char *cmd_name;
	char *executable;
	int pipe[2];
	t_myinstructions *next;
    char 	*command;
	char 	*path_command;
	int		number_files_to;
	int		*redirection_to;
	int		number_files_from;
	int		*redirection_from;
	char	**from_file_str;
	int		from_file;
	char	**to_file_str;
	int		to_file;
} t_myinstructions;

//split_shell
char **ft_split_shell(char *input);
size_t nbr_of_elem(char *input);
int    put_elem_in_tab(char **tab, size_t tab_index, char *input, size_t *input_index);
size_t next_arg_len(char *input, size_t index);

size_t end_quotes(char *input, size_t *index);

//tokenizer
int tok_type_init(char *content, t_commands *commands, size_t index);
t_commands    *tokenizer(char *input);

//checker
int first_check(char *input);
int second_check(t_commands whole_commands);
int redir_check(t_token *current, t_token *next);
int pipe_check(t_token *current, t_token *next);
int special_symb(char *input, size_t index);
int special_symb_2(char *input);
int unclosed_quotes(char *input);

//utils
char *ft_delchar(char *str, char to_del);
size_t ft_countchar(char *str, char to_count);
size_t tab_size(char **tab);
void free_tab(char **tab);

//init_env
t_env	*set_envp(t_env **minish_env, char **envp);
int	var_already_there(t_env *minish_local_var, t_env *next_var);
char *valid_var_add(char *input);
int add_loc_var(t_env **minish_local_var, char *input);
void free_envp(t_env *env);
t_env *get_VAR(t_env **minish_local_var, char *VAR);

#endif
