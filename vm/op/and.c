/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 20:16:59 by satkins           #+#    #+#             */
/*   Updated: 2018/03/04 21:32:27 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "parameters.h"

void	and(t_arena *arena, t_process *process)
{
	int	*params;
	int	reg
	


	params = read_param(process, arena);
	if (process->pc == process->instruct.coding_byte)
	{
		free(params);
		return ;
	}
	process->carry = (params[0] & params[1]) ? 0 : 1;
	process->instruct.param[2]
}