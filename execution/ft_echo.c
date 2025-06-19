/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:58:23 by malaamir          #+#    #+#             */
/*   Updated: 2025/06/18 14:30:17 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*skip_n(t_token *token, int *n)
{
	size_t	i;

	while (token
		&& token->type == WORD
		&& token->value[0] == '-'
		&& token->value[1] == 'n')
	{
		i = 1;
		while (token->value[i] == 'n')
			i++;
		if (token->value[i] != '\0')
			break ;
		*n = 0;
		token = token->next;
	}
	return (token);
}

int	ft_echo(t_cmd *cmd, t_env **env)
{
	t_token	*token;
	int		newline;
	size_t	len;

	(void)env;
	token = cmd->args->next;
	newline = 1;
	token = skip_n(token, &newline);
	while (token)
	{
		if (token->type == WORD)
		{
			len = ft_strlen(token->value);
			if (len > 0)
				write(STDOUT_FILENO, token->value, len);
		}
		token = token->next;
		if (token)
			write(STDOUT_FILENO, " ", 1);
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
