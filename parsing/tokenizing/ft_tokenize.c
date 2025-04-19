/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:53:17 by sojammal          #+#    #+#             */
/*   Updated: 2025/04/19 17:31:02 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

static int	ft_is_ope_start(const char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '|')
		return (1);
	if (*str == '>' && *(str + 1) == '>')
		return (1);
	if (*str == '>')
		return (1);
	if (*str == '<' && *(str + 1) == '<')
		return (1);
	if (*str == '<')
		return (1);
	return (0);
}

static t_token	*ft_parse_operator(const char *input, int *i)
{
	t_token *token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		token->type = APPEND;
		token->value = ft_strdup(">>");
		*i += 2;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		token->type = HEREDOC;
		token->value = ft_strdup("<<");
		*i += 2;
	}
	else if (input[*i] == '>')
	{
		token->type = REDIR_OUT;
		token->value = ft_strdup(">");
		*i += 1;
	}
	else if (input[*i] == '<')
	{
		token->type = REDIR_IN;
		token->value = ft_strdup("<");
		*i += 1;
	}
	else if (input[*i] == '|')
	{
		token->type = PIPE;
		token->value = ft_strdup("|");
	}
	else
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	return (token);
}

static t_token *ft_pars_word(const char *input, int *i)
{
	int start = *i;
	char quote = 0;
	char	*extracted_word;
	t_token *token = NULL;

	while (input[*i])
	{
		if (!quote && (input[*i] == '\'' || input[*i] == '"'))
		{
			quote = input[*i];
			(*i)++;
			while (input[*i] && input[*i] != quote)
				(*i)++;
			if (input[*i])
				(*i)++;
			quote = 0;
		}
		else if (!quote && (ft_isspace(input[*i]) || ft_is_ope_start(input + *i)))
			break;
		else
			(*i)++;
	}
	extracted_word = ft_substr(input, start, *i - start);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = WORD;
	token->value = extracted_word;
	token->next = NULL;

	return (token);
}

static void	ft_add_token(t_token **head, t_token **last, t_token *new)
{
	if (!new)
		return;
	if (!*head)
	{
		*head = new;
		*last = new;
	}
	else
	{
		(*last)->next = new;
		*last = new;
	}
}

t_token	*ft_tokenize(const char	*input)
{
	t_token	*head = NULL;
	t_token *last = NULL;
	t_token *op = NULL;
	t_token *word = NULL;
	int i = 0;

	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (is_ope_start(input + i))
		{
			op = ft_parse_operator(input, &i);
			ft_add_token(&head, &last, op);		
		}
		else
		{
			word = ft_parse_word(input, &i);
			ft_add_token(&head, &last, word);
		}
	}
	return head;
}
