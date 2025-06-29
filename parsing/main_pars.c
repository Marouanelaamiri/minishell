/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:39:48 by sojammal          #+#    #+#             */
/*   Updated: 2025/06/20 01:24:27 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	validate_and_tokenize(char *input, t_token **tokens)
{
	if (!ft_check_quotes(input))
	{
		ft_update_exit_status(258, 63);
		return (0);
	}
	mask_quoted_chars(input);
	*tokens = ft_tokeniz(input);
	if (!*tokens)
	{
		ft_update_exit_status(0, 63);
		return (0);
	}
	unmask_quoted_chars(*tokens);
	if (!syntax_check(*tokens))
	{
		ft_update_exit_status(258, 63);
		return (0);
	}
	return (1);
}

static int	expand_and_check_redirs(t_token *tokens, t_env *env)
{
	escape_from_dollars(tokens);
	delim_of_heredoc(tokens);
	starboy_expansion(tokens, env);
	return (1);
}

static int	sanitize_tokens(t_token **tokens)
{
	remove_empty_tokens(tokens);
	nodes_join(*tokens);
	nodes_join_part2(*tokens);
	clean_hidden_dollars(*tokens);
	field_split_tokens(tokens);
	if (ambiguous_redirection(*tokens))
	{
		ft_update_exit_status(1, 63);
		return (0);
	}
	if (!*tokens)
	{
		ft_update_exit_status(0, 63);
		return (0);
	}
	return (1);
}

t_cmd	*ft_build_pipeline(char *input, t_env *env)
{
	t_token	*tokens;
	t_cmd	*cmd_list;

	if (!input || !*input)
		return (NULL);
	if (!validate_and_tokenize(input, &tokens))
		return (NULL);
	if (!expand_and_check_redirs(tokens, env))
		return (NULL);
	if (!sanitize_tokens(&tokens))
		return (NULL);
	cmd_list = ft_parse_commands(tokens);
	return (cmd_list);
}
