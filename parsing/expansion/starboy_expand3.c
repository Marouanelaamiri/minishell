/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starboy_expand3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:02:56 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/23 21:11:12 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	replace_all_dollars_heredoc(char **line, t_env *env)
{
	int		index;
	char	*new_line;

	index = find_dollar_heredoc(*line);
	while (index != -1)
	{
		new_line = replace_dollar_heredoc(*line, index, env);
		*line = new_line;
		index = find_dollar_heredoc(*line);
	}
}

static void	replace_all_questions_heredoc(char **line)
{
	int		index;
	char	*new_line;

	index = find_question_heredoc(*line);
	while (index != -1)
	{
		new_line = replace_question_heredoc(*line, index);
		*line = new_line;
		index = find_question_heredoc(*line);
	}
}

static void	replace_all_numbers_heredoc(char **line)
{
	int		index;
	char	*new_line;

	index = find_number_heredoc(*line);
	while (index != -1)
	{
		new_line = replace_number_heredoc(*line, index);
		*line = new_line;
		index = find_number_heredoc(*line);
	}
}

void	starboy_expand_heredoc(char **line, t_env *env)
{
	if (!line || !*line)
		return ;
	replace_all_dollars_heredoc(line, env);
	replace_all_questions_heredoc(line);
	replace_all_numbers_heredoc(line);
}
