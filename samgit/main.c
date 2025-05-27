#include "minishell.h"

int	get_Command(t_minishell *minish, int location, int *has_command, int pars)
{
	// if hascommand = 0 make the executable and the command if not
	int	index;

	index = 0;
	if (*has_command == 0)
		index = get_string(minish, location, pars, 'c');
	else 
		index = get_string(minish, location, pars, 'e');
	*has_command = 1;
	return (index);
}

void	set_up_redirection(t_minishell *minish, char direction, int type, int pars)
{
	if (direction == '<')
	{
		minish->instru[pars].number_files_from++;
		if (minish->instru[pars].number_files_from == 1)
			minish->instru[pars].redirection_from = malloc(1 * sizeof(int));
		else 
			minish->instru[pars].redirection_from
			= realloc(minish->instru[pars].redirection_from,
				minish->instru[pars].number_files_from * sizeof(int));
		minish->instru[pars].redirection_from[minish->instru[pars].number_files_from - 1]
		= type;
	}
	else
	{
		minish->instru[pars].number_files_to++;
		if (minish->instru[pars].number_files_to == 1)
			minish->instru[pars].redirection_to = malloc(1 * sizeof(int));
		else 
			minish->instru[pars].redirection_to
			= realloc(minish->instru[pars].redirection_to,
			minish->instru[pars].number_files_to * sizeof(int));
		minish->instru[pars].redirection_to[minish->instru[pars].number_files_to - 1]
		= type;
	}
}
int get_file_and_redirection(t_minishell *minish, int where, int pars)
{

	if (minish->parsed_string[where] == minish->parsed_string[where +1])
	{
		if (minish->parsed_string[where] == '<')
			set_up_redirection(minish, '<', 2, pars);
		else if (minish->parsed_string[where] == '>')
			set_up_redirection(minish, '>', 2, pars);
	}
	else if (minish->parsed_string[where] == '<')
		set_up_redirection(minish, '<', 1, pars);
	else if (minish->parsed_string[where] == '>')
		set_up_redirection(minish, '>', 1, pars);
	write(1, "tut tes fais encule", 20);
	where = get_string(minish, where, pars, minish->parsed_string[where]);
	
	return (where);
}
void pre_init_command(t_minishell *minish, int pars, int *where)
{
	int has_command;

	/// we can deal with some parsing errors here
	write(2, "sexestr\n", 9);

	minish->instru[pars] = init_instructions(minish->instru[pars]);
	has_command = 0;
	write(2, "sexe1", 6);
	while (minish->parsed_string[*where])
	{
		if ((minish->parsed_string[*where] == '|'))
			break;
		if (redirection(minish, *where) == 0)
			(*where) = get_file_and_redirection(minish, *where, pars);
		else if (minish->parsed_string[*where] != ' ')
			(*where) = get_Command(minish, *where, &has_command, pars);
		(*where)++;
	}
}
int count_commands(t_minishell *minish)
{
	int index;
	int commands;

	commands = 0;
	index = 0;
	while (minish->parsed_string[index] != '\0')
	{
		if (not_quoted(minish) && minish->parsed_string[index] == '|')
			commands++;
		if (minish->doublequote % 2 == 0 && minish->parsed_string[index] == '\'')
			minish->quote++;
		if (minish->quote % 2 == 0 && minish->parsed_string[index] == '\"')
			minish->doublequote++;
		index++;
	}
	minish->fd_pipes = malloc(commands * sizeof(int[2]));
	return (commands + 1);
}
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
	next_instr = NULL;
	index = 0;
	while(cmd_as_tokens)
	{
		next_instr = malloc(sizeof(t_myinstructions));
		next_instr->cmd_name = cmd_as_tokens->args[0];
		next_instr->executable = cmd_as_tokens->args;
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
	t_myinstructions *first_instr;
	t_myinstructions *next_instr;
	size_t	index;
	
	index = 0;
	minish->parsed_string = string;
	cmd_as_tokens = tokenizer(string);
	if(!cmd_as_tokens)
	return(0);		//handle errors
	minish->instru = init_commands(cmd_as_tokens);
	if (!minish->instru)
	return(0);		//handle errors
	return (1);
}
//////////////
//////////////
//////////////

int main(int argc, char **argv, char **envp)
{
	char 			*prompt;
	char 			*string;
	t_minishell		*minish;

	if (argc != 1 || !argv)
		return (-1);
	prompt = ft_strdup("");
	minish = malloc(1 * sizeof(t_minishell));
	while (1)
	{
		minish->envp = envp;
		string = readline(prompt);
		/*
		if (parsing_errors(minish) != 0)
			continue;
		*/
		initialise(minish, string);

		run(minish);
	}
	return (0);
}