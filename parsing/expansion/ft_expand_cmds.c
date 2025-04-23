/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:12:50 by sojammal          #+#    #+#             */
/*   Updated: 2025/04/23 14:09:58 by sojammal         ###   ########.fr       */
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
    return res;
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
        else if (str[i] == '$' && !in_single_quotes && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
        {
            int var_start = ++i;
            while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
                i++;
            char *key = ft_substr(str, var_start, i - var_start);
            char *val = ft_strdup(ft_get_env_value(key, env));
            result = ft_strjoin_free(result, val);
            free(key);
        }
        else
        {
            result = ft_strjoin_free(result, ft_substr(str, i, 1));
            i++;
        }q
    }

    return result;
}

// Function to handle the expansion of commands (called after parsing)
void ft_expand_cmds(t_cmd *cmd_list, t_env *env)
{
    char *expanded_value;
    t_token *arg;
    t_redir *redir;

    while (cmd_list)
    {
        arg = cmd_list->args;
        while (arg)
        {
            if (arg->type == WORD && arg->value)
            {
                expanded_value = ft_expand_string(arg->value, env); // Expand the string
                free(arg->value);
                arg->value = expanded_value;
            }
            arg = arg->next;
        }
        redir = cmd_list->redir;
        while (redir)
        {
            if (redir->value)
            {
                expanded_value = ft_expand_string(redir->value, env); // Expand the string for redirection values
                free(redir->value);
                redir->value = expanded_value;
            }
            redir = redir->next;
        }
        cmd_list = cmd_list->next;
    }
}
