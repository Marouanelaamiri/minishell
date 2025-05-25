/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojammal <sojammal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:42:05 by sojammal          #+#    #+#             */
/*   Updated: 2025/05/23 17:00:25 by sojammal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_alloc	*create_track_node(void *ptr)
{
	t_alloc	*new_node;

	new_node = malloc(sizeof(t_alloc));
	if (!new_node)
		return (NULL);
	new_node->ptr = ptr;
	new_node->next = NULL;
	return (new_node);
}

static void	track_add_node(t_alloc **track, t_alloc *new_node)
{
	t_alloc	*current;

	if (!*track)
	{
		*track = new_node;
		return ;
	}
	current = *track;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

static void	relrease_all_trackers(t_alloc *track)
{
	t_alloc	*tmp_node;

	while (track)
	{
		tmp_node = track->next;
		free(track->ptr);
		free(track);
		track = tmp_node;
	}
}

void	*gc_malloc(size_t size, int mode)
{
	static t_alloc	*track = NULL;
	t_alloc			*new_node;
	t_alloc			*prev_node;
	void			*mem;

	if (mode == 63)
	{
		(void)prev_node;
		mem = malloc(size);
		if (!mem)
			exit(1);
		new_node = create_track_node(mem);
		if (!new_node)
			return (free(mem), exit(1), NULL);
		track_add_node(&track, new_node);
		return (mem);
	}
	else if (mode == 12)
	{
		prev_node = track;
		relrease_all_trackers(track);
		track = NULL;
		return (NULL);
	}
	return (NULL);
}
