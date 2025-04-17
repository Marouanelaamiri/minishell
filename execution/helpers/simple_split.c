/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaamir <malaamir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:37:14 by malaamir          #+#    #+#             */
/*   Updated: 2025/04/16 14:41:54 by malaamir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **simple_split(char *input)
{
	char **args;
	int i = 0;

	args = malloc(sizeof(char *) * 100); // adjust as needed
	if (!args)
		return (NULL);
	args[i] = strtok(input, " ");
	while (args[i])
		args[++i] = strtok(NULL, " ");
	return (args);
}
