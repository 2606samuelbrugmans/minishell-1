#include "../inc/minishell.h"

int add_loc_var(t_env **minish_envp, t_env **minish_local_var, char *input) //minish_loc_var has to be set NULL
{
	t_env *last_var;
	t_env *next_var;
	char *equal;
	size_t key_len;
	size_t i;

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
	if(var_already_there(minish_envp, minish_local_var, next_var->VAR))
	{
		free(get_VAR(minish_envp, minish_local_var, next_var->VAR)->value);
		get_VAR(minish_envp, minish_local_var, next_var->VAR)->value = next_var->value;
		free((next_var)->VAR);	//should I free it in var_already_there ?
		free(next_var);
		return(1);
	}
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

// char *fill_renew_str(char *last_str, size_t len_var, t_env * actual_var)
// {
//     char *renew_str;
//     size_t len_value;
//     size_t len_renew;
//     size_t r_index;
//     size_t l_index;
//     size_t v_index;

//     r_index = 0;
//     l_index = 0;
//     v_index = 0;
//     if (actual_var == NULL)
//         len_value = 0;
//     else
//         len_value = ft_strlen(actual_var->value);
//     len_renew = (ft_strlen(last_str) + len_value - len_var - 1 + 1); // (-1 + 1) = (-$ +'\0')
//     // printf("len_last_str : %zu\n", ft_strlen(last_str));
//     // printf("len_var : %zu\n", len_var);
//     // printf("len_value : %zu\n", len_value);
//     // printf("len_renew : %zu\n", len_renew);
//     renew_str = malloc(sizeof(char) * len_renew);
//     if (!renew_str)
//         return(NULL);   //malloc error
//     while(last_str[l_index] && last_str[l_index] != '$')
//         renew_str[r_index ++] = last_str[l_index ++];
//     // if(last_str[l_index] == '\0')
//     //     return(renew_str);
//     if(actual_var)
//     {
//         while(actual_var->value[v_index])
//             renew_str[r_index ++] = actual_var->value[v_index ++];
//     }
//     l_index += len_var + 1;
//     while(last_str[l_index])
//         renew_str[r_index ++] = last_str[l_index ++];
//     renew_str[r_index] = '\0';
//     printf("last_str : %s\n", last_str);
//     printf("renew_str : %s\n", renew_str);
//     return(renew_str);
// }
char *fill_renew_str(char *last_str, size_t last_str_ind, size_t len_var, t_env *actual_var)
{
    char *renew_str;
    size_t len_value;
    size_t len_renew;

    renew_str = malloc(sizeof(char) * len_renew);
    if (!renew_str)
        return(NULL);   //malloc error
    if (actual_var == NULL)
        len_value = 0;
    else
        len_value = ft_strlen(actual_var->value);
    len_renew = (ft_strlen(last_str) + len_value - len_var - 1 + 1); // (-1 + 1) = (-$ +'\0')

    ft_strlcpy(renew_str, last_str, last_str_ind + 1);
    if(actual_var && actual_var->value)
        ft_strlcat(renew_str, actual_var->value, len_renew);
    ft_strlcat(renew_str, last_str + last_str_ind + len_var, len_renew);
    return(renew_str);
}

char    *replace_var(t_env *minish_envp, t_env *minish_local_var, char *string, size_t *str_ind, char *new_str, size_t *new_str_ind)
{
    size_t len_var;
    t_env *actual_var;
    char *pres_var;
    char *renew_str;

    len_var = 0;
    renew_str = NULL;
    (*str_ind)++;
    while(string[*str_ind + len_var] && string[*str_ind + len_var] != ' ' && string[*str_ind + len_var] != '\"')
        len_var++;
    pres_var = ft_substr(string, *str_ind, len_var);
    if(!pres_var)
        return(NULL);       //malloc error;
    (*str_ind) += len_var;
    // printf("str[%zu] : |%c|\n", *str_ind, string[*str_ind]);
    // printf("pres_var : %s\n", pres_var);
    actual_var = get_VAR(&minish_envp, &minish_local_var, pres_var);
    // printf("VAR : %s\n", actual_var->VAR);
    // printf("value : %s\n", actual_var->value);
    free(pres_var);
    //maybe this part is not needed but more clear, intead, just put renew_str = fill_renew_str(new_str, len_var, NULL);
    if(!actual_var)
        renew_str = fill_renew_str(new_str, *new_str_ind, len_var, NULL);
    else
        renew_str = fill_renew_str(new_str, *new_str_ind, len_var, actual_var);
    // printf("renew_str : %s\n", renew_str);
    if(!renew_str)
        return(NULL);       //malloc error;
    if(!actual_var)
        (*new_str_ind) += 1;
    else
        (*new_str_ind) += len_var;
    return(renew_str);
}


char    *get_new_string(t_env *minish_envp, t_env *minish_local_var, char *string) // in progress
{
    // int i = 0;
    char *temp;
    char *new_str;
    bool in_double;
    size_t str_ind;
    size_t new_str_ind;

    str_ind = 0;
    new_str_ind = 0;
    in_double = false;
    new_str = ft_strdup(string);
    if(!new_str)
        return(NULL);   //malloc error
    temp = ft_strdup(string);
        if(!temp)
            return(NULL);   //malloc error
    while (string[str_ind])
    {
        if(string[str_ind] == '\"')
        {
            if(in_double == false)
                in_double = true;
            else
                in_double = false;
        }
        if(string[str_ind] == '\'' && !in_double)
        {
            end_quotes(string, &str_ind);
            continue;
        }
        // printf("str[%zu] : |%c|\n", str_ind, string[str_ind]);
        // printf("full str: %s\n", string + str_ind);
        // exit(1);
		if(string[str_ind] == '$')
		{
            // i++;
            // printf("i : %d\n", i);
            new_str = replace_var(minish_envp, minish_local_var, string, &str_ind, temp, &new_str_ind);
            if (!new_str)
            {
                free(temp);
                return(NULL);
            }
            free(temp);
            temp = new_str;
            continue;
		}
		str_ind++;
    }
    return(new_str);
}
