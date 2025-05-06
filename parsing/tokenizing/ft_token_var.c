/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:33:12 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/03 16:27:58 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_handle_var(t_data *data, char *input)
{
	int		start;
	int		j;
	char	*value;

	start = data->i;
	data->i++;
	j = data->i;

	if (input[data->i] == '?')
	{
		data->i++;
		value = ft_strdup("$?");
	}
	else if (ft_isdigit(input[data->i]))
	{
		data->i++;
		value = ft_substr(input, start, 2);
	}
	else if (input[data->i] == '\"') // handle $""
	{
		value = ft_strdup(""); // we store it as empty string
	}
	else
	{
		while (ft_isalnum(input[data->i]) || input[data->i] == '_' || (input[data->i] && input[data->i + 1] && input[data->i + 1] == '$') || (input[data->i] && input[data->i - 1] && input[data->i - 1] == '$'))
			data->i++;
		if (data->i == j)
			value = ft_strdup("$");
		else
			value = ft_substr(input, start, data->i - start);
		// printf("input[%d] = %s\n", data->i, value);
	}

	if (!value)
	{
		data->error = 1;
		return (0);
	}
	lst_add_back_token(data, lst_new_token(VAR, value));
	// free(value);
	return (0);
}

// int	ft_handle_var(t_data *data, char *input)
// {
// 	int		start;
// 	char	*value;
// 	int		j;

// 	start = data->i;
// 	data->i++;
// 	j = data->i;
// 	if (input[data->i] == '?')
// 	{
// 		value = ft_substr(input, start, 2);
// 		data->i++;
// 	}
// 	else if (ft_isdigit(input[data->i]))
// 	{
// 		value = ft_substr(input, start, 2);
// 		data->i++;
// 	}
// 	else
// 	{
// 		while (ft_isalnum(input[data->i]) || input[data->i] == '_' || (input[data->i] && input[data->i + 1] && input[data->i + 1] == '$') || (input[data->i] && input[data->i - 1] && input[data->i - 1] == '$'))
// 		{
// 			// if (input[data->i] != '\"' || input[data->i] != '\'') 
// 			// {
// 			// 	// puts("break");
// 			// 	break;
// 			// }
// 			// else
// 			data->i++;
// 		}
// 		if (data->i == j)
// 		{
// 			value = ft_substr(input, start, 1);
// 		}
// 		else
// 			value = ft_substr(input, start, data->i - start);
// 		printf("value = %s\n", value);
// 	}
// 	if (!value)
// 	{
// 		data->error = 1;
// 		return (0);
// 	}
// 	lst_add_back_token(data, lst_new_token(VAR, value));
// 	return (0);
// }
// int ft_handle_var(t_data *data, char *input)
// {
//     int start;
//     char *value;
//     int j;

//     start = data->i;
//     data->i++; // Move past the first '$'
//     j = data->i;

//     // Handle the case where multiple '$' are together (e.g., $$$$$$)
//     while (input[data->i] == '$') {
//         data->i++; // Skip over additional '$' signs.
//     }

//     // If we have more than one '$', collapse them into one token (just '$')
//     if (data->i > j) {
//         value = ft_substr(input, start, 1); // Only keep the first '$'
//     }
//     // Handle the $? case (exit status)
//     else if (input[data->i] == '?') {
//         value = ft_substr(input, start, 2); // Just "$?"
//         data->i++; // Skip the '?'
//     }
//     // Handle the case where there's a number after '$'
//     else if (ft_isdigit(input[data->i])) {
//         value = ft_substr(input, start, 2); // Just "$<digit>"
//         data->i++; // Skip the digit
//     }
//     // Handle general variable names.
//     else if (input[data->i] == '"' || input[data->i] == '\'') {
//         // If we encounter quotes after $, we need to process this specially.
//         char quote = input[data->i];
//         data->i++; // Skip the quote character.
        
//         // Handle the content between the quotes.
//         while (input[data->i] != quote && input[data->i] != '\0') {
//             data->i++;
//         }

//         // If the quote wasn't closed, treat as an error (optional).
//         if (input[data->i] == quote) {
//             value = ft_substr(input, start, data->i - start + 1); // Include the '$' and the quote
//         } else {
//             value = ft_substr(input, start, data->i - start); // Just the '$' and content
//         }
//     }
//     // Handle normal environment variable names (e.g., $USER)
//     else {
//         while (ft_isalnum(input[data->i]) || input[data->i] == '_') {
//             data->i++; // Continue as long as we're in a valid variable name.
//         }

//         // If we didn't find any valid variable name, return just '$'
//         if (data->i == j) {
//             value = ft_substr(input, start, 1); // Just the '$' character.
//         }
//         else {
//             value = ft_substr(input, start, data->i - start); // The variable name (e.g., $USER)
//         }
//     }

//     // Error handling in case malloc fails or no valid variable is found.
//     if (!value) {
//         data->error = 1;
//         return (0);
//     }

//     // Add the token to the list of tokens.
//     lst_add_back_token(data, lst_new_token(VAR, value));
//     return (0);
// }

