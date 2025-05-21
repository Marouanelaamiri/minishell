/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:34:43 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/17 23:36:39 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_update_exit_status(int status, int x)
{
	static int exit_status;

	if (x == 63)
		exit_status = status;
	else if (x == 0)
		return (exit_status);
	return (0);
}

static char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*temp = ft_strjoin(s1, s2);
	char	*result = ft_strjoin(temp, s3);
	free(temp);
	return (result);
}

// static void	free_node(t_token *node)
// {
// 	if (node)
// 	{
// 		free(node->value);
// 		free(node);
// 		node = NULL;
// 	}
// }

int	not_redir(t_token *node)
{
	return (node->type != REDIR_IN && node->type != REDIR_OUT && node->type != HEREDOC && node->type != APPEND);
}

void	nodes_join(t_token *tokens)
{
	t_token *current = tokens;
	t_token *prev;
	t_token *next;
	char *joined;

	while (current)
	{
		if (current->type == VAR)
		{
			prev = current->prev;
			next = current->next;
			if (prev && next && (prev->type != SPCE && not_redir(prev)) && (next->type != SPCE && not_redir(next)))
			{
				joined = ft_strjoin3(prev->value, current->value, next->value);
				free(current->value);
				current->value = joined;
				if (prev->prev)
					prev->prev->next = current;
				current->prev = prev->prev;

				if (next->next)
					next->next->prev = current;
				current->next = next->next;
				// free_node(prev);
				// free_node(next);
				current->type = WORD;
				continue;
			}
			else if (prev && (prev->type != SPCE && not_redir(prev)))
			{
				joined = ft_strjoin(prev->value, current->value);
				free(current->value);
				current->value = joined;
				if (prev->prev)
					prev->prev->next = current;
				current->prev = prev->prev;
				// free_node(prev);
				current->type = WORD;
				continue;
			}
			else if (next && (next->type != SPCE && not_redir(next)))
			{
				joined = ft_strjoin(current->value, next->value);
				free(current->value);
				current->value = joined;
				if (next->next)
					next->next->prev = current;
				current->next = next->next;
				// free_node(next);
				current->type = WORD;
				continue;
			}
			else 
			{
				joined = ft_strdup(current->value);
				free(current->value);
				current->value = joined;
				current->type = WORD;
			}
		}
		current = current->next;
	}
}

static int	is_quote(char c)
{
	return (c == '\'');
}

static int	count_non_quotes(const char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (!is_quote(str[i]))
			count++;
		i++;
	}
	return (count);
}

char	*remove_squotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	int		size;

	if (!str)
		return (NULL);
	size = count_non_quotes(str);
	if (size == 0)
	{
		return (ft_strdup("\0"));
	}
	new_str = malloc(size + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!is_quote(str[i]))
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}


static void	remove_token(t_token **head, t_token *to_remove)
{
	if (!head || !*head || !to_remove)
		return;

	// If the token is the head of the list
	if (to_remove == *head)
		*head = to_remove->next;

	// Relink previous token
	if (to_remove->prev)
		to_remove->prev->next = to_remove->next;

	// Relink next token
	if (to_remove->next)
		to_remove->next->prev = to_remove->prev;

	// Free the token
	if (to_remove->value)
		free(to_remove->value);
	free(to_remove);
}

void	remove_empty_tokens(t_token **tokens)
{
	t_token *curr = *tokens;
	t_token *tmp;

	while (curr)
	{
		tmp = curr->next;
		if (curr->value && curr->value[0] == '\0' && curr->type != SPCE)
		{
			if (curr->prev && curr->prev->type == SPCE && curr->prev->prev && (curr->prev->prev->type !=HEREDOC && curr->prev->prev->type != WORD))
				remove_token(tokens, curr);
		}
		curr = tmp;
	}
}

static char	*remove_hidden_dollars(char *str)
{
	int	h = 0;
	int m = 0;
	int len = 0;
	char *clean;
	if (!str)
		return (NULL);
	
	len = ft_strlen(str);
	clean = malloc(len + 1);
	if (!clean)
		return (NULL);
	while (str[h])
	{
		if ((unsigned char)str[h] != (unsigned char)('$' * -1))
		{
			clean[m] = str[h];
			m++;
		}
		h++;
	}
	clean[m] = '\0';
	return (clean);
}

void	clean_hidden_dollars(t_token *tokens)
{
	t_token *hmstr= tokens;
	char *clean;
	
	while (hmstr)
	{
		clean = remove_hidden_dollars(hmstr->value);
		free(hmstr->value);
		hmstr->value = clean;
		hmstr = hmstr->next;
	}
}
