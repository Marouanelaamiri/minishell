/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starboy_expand3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:02:56 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/17 22:09:26 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	find_question_heredoc(char *str)
{
	int i = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			return (i);
		i++;
	}
	return (-1);
}
static char	*replace_question_heredoc(char *str, int index)
{
	char	*new_str;
	char	*exit_code;
	char	*prefix;
	char	*suffix;
	char	*temp;
	int		len;

	len = ft_strlen(str);
	exit_code = ft_itoa(ft_update_exit_status(0, 0));
	prefix = ft_substr(str, 0, index);
	suffix = ft_substr(str, index + 2, len - (index + 2));
	temp = ft_strjoin(prefix, exit_code);
	new_str = ft_strjoin(temp, suffix);
	free(prefix);
	free(suffix);
	free(temp);
	free(exit_code);
	return (new_str);
}
static int	find_number_heredoc(char *str)
{
	int i = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && ft_isdigit(str[i + 1]))
			return (i);
		i++;
	}
	return (-1);
}

static char	*replace_number_heredoc(char *str, int index)
{
	char	*new_str;
	char	*prefix;
	char	*suffix;
	int		len;

	len = ft_strlen(str);
	prefix = ft_substr(str, 0, index);
	suffix = ft_substr(str, index + 2, len - (index + 2)); 
	new_str = ft_strjoin(prefix, suffix);
	free(prefix);
	free(suffix);
	return (new_str); 
}

static	int	find_dollar_heredoc(char *str)
{
	int i = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && (ft_isalnum(str[i + 1])))
			return (i); 
		i++;
	}
	return (-1);
}

static char *get_variable_heredoc(char *str, int index)
{
	int	h = index + 1;
	int	m = 0;

	while (str[h + m] && ft_isalnum(str[h + m]))
		m++;
	return (ft_substr(str, h, m));
}

static char *get_value_heredoc(t_env *env, char *key_val)
{
	while (env)
	{
		if (ft_strcmp(env->name, key_val) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*replace_dollar_heredoc(char *str, int index, t_env *env)
{
	char	*new_str;
	char	*prefix;
	char	*suffix;
	char	*key_val;
	char	*val;
	char	*temp;
	int		len;

	key_val = get_variable_heredoc(str, index);
	len = ft_strlen(key_val);

	prefix = ft_substr(str, 0, index);
	suffix = ft_strdup(&str[index + len + 1]);
	val = get_value_heredoc(env, key_val);
	if (!val)
		val = ft_strdup("");
	else
		val = ft_strdup(val);
	temp = ft_strjoin(prefix, val);
	new_str = ft_strjoin(temp, suffix);
	free(prefix);
	free(suffix);
	free(temp);
	free(key_val);
	return (new_str);
}

void	starboy_expand_heredoc(char **line, t_env *env)
{
	int		x;
	char	*new_line;

	if (!line || !*line)
		return ;
	while ((x = find_question_heredoc(*line)) != -1)
	{
		new_line = replace_question_heredoc(*line, x);
		free(*line);
		*line = new_line;
	}
		while ((x = find_number_heredoc(*line)) != -1)
	{
		new_line = replace_number_heredoc(*line, x);
		free(*line);
		*line = new_line;
	}
	while ((x = find_dollar_heredoc(*line)) != -1)
	{
		new_line = replace_dollar_heredoc(*line, x, env);
		free(*line);
		*line = new_line;
	}
}