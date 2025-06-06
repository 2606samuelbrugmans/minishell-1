#include "minishell.h"

void free_envp(t_env *env)
{
	t_env *next;

	while(env)
	{
		next = env->next;
		free(env->VAR);
		free(env->value);
		free(env);
		env = next;
	}
}

t_env	*set_envp(t_env **minish_env, char **envp)
{
	size_t i;
	size_t key_len;
	char *equal_is_there;
	t_env *current_env;
	t_env *next_envv;

	i = 0;
	*minish_env = NULL;
	current_env = NULL;
	next_envv = NULL;
	while(envp[i])
	{
		next_envv = malloc(sizeof(t_env));								//need to free at the end
		if(!next_envv)
			return(NULL);
		equal_is_there = ft_strchr(envp[i], '=');
		if(!equal_is_there)
		{
			free(next_envv);
			return(NULL);								//print an env message error that means wrong format
		}
		key_len = equal_is_there - envp[i];
		next_envv->VAR = ft_substr(envp[i], 0, key_len);
		next_envv->value = ft_strdup(equal_is_there + 1);
		if (!next_envv->VAR || !next_envv->value)
			return(NULL);					//handle errors
		if(*minish_env == NULL)
			*minish_env = next_envv;
		else
			current_env->next = next_envv;
		current_env = next_envv;
		i++;
	}
	current_env->next = NULL;
	return(*minish_env);
}

char *valid_var_add(char *input)
{
	size_t i;
	char *equal;
	char *extra_check;

	if(!input || input[0] == '=' || ft_isdigit(input[0]))
		return (NULL);
	equal = ft_strchr(input, '=');
	if(!equal)
		return (NULL);
	if(*(equal + 1) == '\0')
		return(NULL);
	i = 0;
	while(input[i] && input[i] != '=')
	{
		if(!ft_isalnum(input[i]) && input[i] != '_')
			return(NULL);
		i++;
	}
	extra_check = equal;
	while(*extra_check)
	{
		if(*extra_check == '|')
			return(NULL);
		extra_check++;
	}
	return(equal);
}

int add_loc_var(t_env **minish_local_var, char *input) //minish_loc_var has to be set NULL
{
	t_env *last_var;
	t_env *next_var;
	char *equal;
	size_t key_len;

	last_var = NULL;
	next_var = NULL;
	equal = valid_var_add(input);
	if (!equal)
		return(0);
	next_var = malloc(sizeof(t_env));
	if(!next_var)
		return(0);							//malloc error
	key_len = equal - input;
	next_var->VAR = ft_substr(input, 0, key_len);
	next_var->value = ft_strdup(equal + 1);
	next_var->next = NULL;
	if(!*minish_local_var)
		*minish_local_var = next_var;
	else
	{
		last_var = *minish_local_var;
		while(last_var->next)
			last_var = last_var->next;
		last_var->next = next_var;
	}
	return(1);
}
