/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 16:46:56 by satkins           #+#    #+#             */
/*   Updated: 2018/02/18 19:04:05 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		count_live(t_arena *arena)
{
	t_node		*node;
	t_node		*prev;
	t_process	*proc;
	int			live_count;

	live_count = 0;
	node = arena->proc_queue->first;
	prev = NULL;
	while (node)
	{
		proc = node->content;
		live_count += proc->num_live;
		if (!proc->num_live)
		{
			del_node(node, prev);
			arena->players[proc->player_num].num_of_process--;
			free(proc);
		}
		prev = node;
		node = node->next;
	}
	return (count_live);
}

static void		die_check(t_arena *arena)
{
	static		checkups = 0;

	if (count_live(arena) >= NBR_LIVE || ++checkups == MAX_CHECKS)
	{
		checkups = 0;
		arena->cycle_to_die -= CYCLE_DELTA;
	}
}

static int		check_multiple_players(t_player *players, int num_players)
{
	int			i;
	int			first_flag;

	first_flag = 0;
	i = -1;
	while (++i < num_players)
		if (players[i].num_of_process > 0)
		{
			if (first_flag)
				return (1);
			else
				first_flag = 1;
		}
	return (0);
}

void			start_game(t_arena *arena)
{
	t_process	*process;

	arena->cycle = 0;
	arena->cycle_to_die = CYCLE_TO_DIE;
	while (check_multiple_players(arena->players, arena->num_players))
	{
		process = arena->proc_queue->first->content;
		while (process->execute_cycle == arena->cycle)
		{
			ft_depqueue(arena->proc_queue);
			process_execution(arena, process);
			process = arena->proc_queue->first->content; 
		}
		++arena->cycle;
		if (arena->cycle % CYCLE_TO_DIE == 0)
			die_check(arena);
	}
}