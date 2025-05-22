/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:58:23 by malaamir          #+#    #+#             */
/*   Updated: 2025/05/22 10:48:38 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*skip_n_flag(t_token *token, int *newline)
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
		*newline = 0;
		token = token->next;
	}
	return (token);
}

int	ft_echo(t_cmd *cmd, t_env **env)
{
	t_token	*token;
	int		newline;

	(void)env;
	token = cmd->args->next;
	newline = 1;
	token = skip_n_flag(token, &newline);
	while (token)
	{
		if (token->type == WORD)
			printf("%s", token->value);
		token = token->next;
		if (token)
			printf(" ");
	}
	if (newline)
		printf("\n");
	return (0);
}
