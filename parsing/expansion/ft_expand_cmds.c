/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:57:32 by sojammal          #+#    #+#             */
/*   Updated: 2025/04/26 20:01:16 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char *ft_get_env_value(char *key, t_env *env)
{
    while (env)
    {
        if (ft_strcmp(env->name, key) == 0)
            return (env->value);
        env = env->next;
    }
    return (""); // Return empty string if variable not found
}

// Helper function to join and free strings
static char *ft_strjoin_free(char *s1, char *s2)
{
    char *res = ft_strjoin(s1, s2);
    free(s1);
    free(s2);
    return (res);
}
static char	*ft_expand_var(const char *str, int *i, t_env *env)
{
	char	*key;
	char	*val;

	if (str[*i + 1] == '{') // Handle ${VAR}
	{
		int start = *i + 2;
		int end = start;
		while (str[end] && str[end] != '}')
			end++;
		if (str[end] == '}')
		{
			key = ft_substr(str, start, end - start);
			val = ft_strdup(ft_get_env_value(key, env));
			free(key);
			*i = end + 1;
			return (val);
		}
        // TODO: Handle error for unmatched {
	}
	else if (ft_isalpha(str[*i + 1]) || str[*i + 1] == '_') // Handle $VAR
	{
		int start = ++(*i);
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
		key = ft_substr(str, start, *i - start);
		val = ft_strdup(ft_get_env_value(key, env));
		free(key);
		return (val);
	}
    else if (str[*i + 1] == '?') // Handle $? for last command status
    {
        (*i) += 2;
        return (ft_strdup(ft_itoa(ft_get_exit_status())));
    }
	else // Just a single $
	{
		(*i)++;
		return (ft_strdup("$"));
	}
    return (NULL); // Should not reach here
}


static char *ft_expand_string(char *str, t_env *env)
{
    char *result = ft_calloc(1, 1);
    int i = 0;
    int in_single_quotes = 0;
    int in_double_quotes = 0;

    while (str[i])
    {
        if (str[i] == '\'' && !in_double_quotes)
        {
            in_single_quotes = !in_single_quotes;
            i++;
        }
        else if (str[i] == '\"' && !in_single_quotes)
        {
            in_double_quotes = !in_double_quotes;
            i++;
        }
        else if (str[i] == '$' && !in_single_quotes)
        {
            char *expanded_value = ft_expand_var(str, &i, env);
            result = ft_strjoin_free(result, expanded_value);
        }
        else
        {
            result = ft_strjoin_free(result, ft_substr(str, i, 1));
            i++;
        }
    }

    return result;
}

static char *ft_remove_quates(char *str)
{
    char *res = ft_calloc(1, 1);
    int i = 0;
    int in_single = 0;
    int in_double = 0;

    while (str[i])
    {
        if (str[i] == '\'' && !is_double)
            is_single = !is_single;
        else if (str[i] == '\"' && !is_single)
            is_double = !is_double;
        else
        {
            char *temp = ft_substr(str, i, 1);
            res = ft_strjoin_free(res, temp);
        }
        i++;
    }
    free(str);
    return res;
}

// Function to handle the expansion of commands (called after parsing)
void ft_expand_cmds(t_cmd *cmd_list, t_env *env)
{
    char *expanded_value;
    char **split_fields;
    int i;
    t_token *arg;
    t_redir *redir;
    t_token *new_node;
    t_token *next_arg;

    while (cmd_list)
    {
        arg = cmd_list->args;
        while (arg)
        {
            next_arg = arg->next;
            if (arg->type == WORD && arg->value)
            {
                expanded_value = ft_expand_string(arg->value, env);
                split_fields = ft_split(expanded_value, ' ');
                free(expanded_value);
                free(arg->value);

                if (split_fields && split_fields[0])
                {
                    arg->value = ft_remove_quotes(ft_strtrim(split_fields[0], " \t\n"));
                    i = 1;
                    while (split_fields[i])
                    {
                        new_node = malloc(sizeof(t_token));
                        if (!new_node)
                            return; // handle malloc fail maybe later
                        new_node->type = WORD;
                        new_node->value = ft_remove_quotes(ft_strtrim(split_fields[i], " \t\n"));
                        new_node->next = arg->next;
                        arg->next = new_node;
                        arg = new_node;
                        i++;
                    }
                }
                free(split_fields);
            }
            arg = next_arg;
        }

        redir = cmd_list->redir;
        while (redir)
        {
            if (redir->value)
            {
                expanded_value = ft_expand_string(redir->value, env);
                free(redir->value);
                redir->value = ft_remove_quotes(ft_strtrim(expanded_value, " \t\n"));
                free(expanded_value);
            }
            redir = redir->next;
        }
        cmd_list = cmd_list->next;
    }
}

