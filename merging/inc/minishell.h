#ifndef MINISHELL_H

# define MINISHELL_H

# include "../Libft/inc/libft.h"
# include <stdbool.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stddef.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
///

# define YES 1
# define NOPE 0
# define INVALID_ARG -1
# define PATH_MAX 4096

typedef struct s_instructions   t_instructions;

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


typedef struct s_token		//need to understand this
{
	char *content;
    t_token_type  type;
}               t_token;

typedef struct s_commands	//don't really care, it's for me only
{
	char *as_str;
	t_token **args;
	struct s_commands *next_command;

}               t_commands;

typedef struct s_redir
{
	t_token_type type;
	char		*file_name;
	struct s_redir *next;
}			t_redir;


typedef struct s_env		//linked list of variable, always good to see how it works (basically a dictionnary)
{
    char *VAR;
    char *value;
    struct s_env *next;
}              t_env;

typedef struct s_instructions
{
	t_token **executable; 	// change here because too complex without it, basically for instr == ls -la file.txt
							//executable.args[0].content = "ls"				and so executable.arg[0].type = CMD
							//executable.args[1].content = "-la"			and so executable.arg[1].type = FLAG
							//executable.args[2].content = "file.txt"		and so executable.arg[2].type = FILENAME
							//executable.args[3] = NULL
	char	*command;;		// = whole str = "ls -la file.txt"
	int pipe[2];
	t_redir	*in_redir;
	t_redir	*out_redir;
	t_instructions *next;
	char 	*path_command;
} t_instructions;

typedef struct t_minishell
{
	t_env *envp;
	t_env *local_var;
	t_instructions *instru;
	int		number_of_commands;
	int		(*fd_pipes)[2];
	char	*parsed_string;
} 	t_minishell;

///////////////////////////////////////////////////////PARSING///////////////////////////////////////////////////////
int main(int argc, char **argv, char **envp);
void	init_minish(t_minishell **minish, char **envp);
t_instructions	*init_insrtu(t_minishell *minish, t_commands	*cmd_as_tokens);

//prompt
char *get_prompt(t_env **envp);
char *get_path(t_env **envp);

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
char *ft_strjoinchar(char *str, char c);

//init_env
t_env	*set_envp(t_env **minish_env, char **envp);
int	var_already_there(t_env **minish_envp, t_env **minish_local_var, char *next_var);
char *valid_var_add(char *input);
t_env *get_VAR(t_env **minish_envp, t_env **minish_local_var, char *VAR);

//loc_var
char *fill_renew_str(char *last_str, size_t last_str_ind, size_t len_var, t_env *actual_var);
char *replace_var(t_minishell minishell, char *string, size_t *str_ind, char *temp);
char *get_new_string(t_minishell minishell, char *string);
int add_loc_var(t_env **minish_envp, t_env **minish_local_var, char *input);

//init_instr
t_instructions	*init_insrtu(t_minishell *minish, t_commands	*cmd_as_tokens);
void set_redir(t_instructions *instr, t_commands *cmd);
void  *add_redir(t_redir **redir_list, t_token_type type, char *file);
int	count_commands(t_commands *cmd_as_token);

//free everything
void free_minish(t_minishell **minish);
void free_envp(t_env *env);



// char	*remove_quote(char *string, char quote);
// void	child_process(t_minishell *minish, int parser);
// void 	close_stuff(t_minishell *minish);
// void	store(t_minishell *minish, int pars,
// 	char *filename, char direction);
// int		get_string(t_minishell *minish, int where, int pars, char direction);
// void	skip_quotes(const char *str, int base_index, int *offset_index);
// int 	count_commands(t_minishell *minish);
// void 	pre_init_command(t_minishell *minish, int pars, int *where);
// int 	get_file_and_redirection(t_minishell *minish, int where, int pars);
// void 	set_up_redirection(t_minishell *minish, char direction, int type, int pars);
// int		get_Command(t_minishell *minish, int location, int *has_command, int pars);
// int		find_end_index(char *str, int where, char quote);
// int		is_stopper(char c);
// int		initialise(t_minishell *minish, char *string);

// int		skip_spaces(char *str, int where);
// int 	within_executable(t_minishell *minish, int i);
// int 	redirection(t_minishell *minish, int i);
// int 	not_quoted(t_minishell *minish);
// void 	nested(t_minishell *minish, int parser);
// int 	pipe_nested(t_minishell *minish, int length);
// void 	no_redirection_proc(t_minishell *minish, int parser);
// void 	access_test(t_minishell *minish, int parser);
// void	execute(t_minishell *minish, int parser);
// void	process(t_minishell *minish);
// int		run(t_minishell *minish);
// void	error(t_minishell *minish, char *reason, int parser);
// void	ft_putstr_fd(char *s, int fd);
// size_t	ft_strlen(const char *s);
// char	*ft_strdup(const char *s1);
// void	store(t_minishell *minish, int pars,
// 	char *filename, char direction);
// int	count_quote(char *string, char c);
// char	*ft_substr(char const *s, unsigned int start,
// 	size_t len);
// ////////////////////////////////// paths
// char	*path_finding(char *pathed, char **env);
// char	*potential_pathing(char *paths, char *command_to_path, int *index);
// int		find_string(char **env, char *path);
// char	*get_path(char *command_to_path, char *paths, int index);
// int	path_len(char *string, int index);
// void	putcommand(char *command_to_path, char *potential_path, int size);
// t_instructions init_instructions(t_instructions instr);
// /////////////// debug
// void print_minishell(t_minishell *minish);
// void print_instructions(t_instructions *instr);






#endif
