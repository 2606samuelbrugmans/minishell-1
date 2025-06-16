#include "../inc/minishell.h"

//////////////principal changes
//////////////
//////////////
void	*init_commands(t_commands	*cmd_as_tokens)
{
	t_myinstructions *first_instr;
	t_myinstructions *current_instr;
	t_myinstructions *next_instr;
	size_t index;

	first_instr = NULL;
	current_instr = NULL;
	next_instr = NULL;
	index = 0;
	while(cmd_as_tokens)
	{
		next_instr = malloc(sizeof(t_myinstructions));
		next_instr->cmd_name = cmd_as_tokens->args[0]->content;
		next_instr->executable = cmd_as_tokens->as_str;
		next_instr->next = NULL;
		if (!first_instr)
			first_instr = next_instr;
		else
			current_instr->next = next_instr;
		current_instr = next_instr;
		cmd_as_tokens = cmd_as_tokens->next_command;
	}
	return(first_instr);
}

int initialise(t_minishell *minish, char *string)
{
	t_commands *cmd_as_tokens;
	size_t	index;

	index = 0;
	if(!string || *string == '\0')
		return(1);
	if(!first_check(string))
        return(0);
	if(add_loc_var(&minish->envp, &minish->local_var, string))
		return(1);
	minish->parsed_string = get_new_string(minish->envp, minish->local_var, string);		//finish this
	// minish->parsed_string = string;
	printf("after var_loc : \n|%s|\n", minish->parsed_string);
	cmd_as_tokens = tokenizer(minish->parsed_string);
	if(!cmd_as_tokens)
		return(0);		//handle errors
	minish->instru = init_commands(cmd_as_tokens);
	if (!minish->instru)
		return(0);		//handle errors or empty inputs
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char 			*prompt;
	char 			*string;
	t_minishell		*minish;

	if (argc != 1 || !argv)
		return (-1);
	prompt = ft_strdup("");
	minish = malloc(1 * sizeof(t_minishell));
	minish->local_var = NULL;					//need an init to set everything  NULL;
	set_envp(&minish->envp, envp);
	/***********************************if you want to try env var***********************************/
	t_env *env = minish->envp;
	// printf("|---------environment variable :---------|\n");
	// while(env)
	// {
	// 	printf("key : [%s]\n", env->VAR);
	// 	printf("value : [%s]\n", env->value);
	// 	env = env->next;
	// }
	while (1)
	{
		string = readline(prompt);
		initialise(minish, string);
	/***********************************if you want to try loc var***********************************/
		// printf("|---------local variable :---------|\n");
		// t_env *loc = minish->local_var;
		// while(loc)
		// {
		// 	printf("key : [%s]\n", loc->VAR);
		// 	printf("value : [%s]\n", loc->value);
		// 	loc = loc->next;
		// }
		// printf("|----------------------------------|\n");
	}
	return (0);
}

