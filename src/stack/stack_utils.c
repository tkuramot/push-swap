/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 09:49:47 by tkuramot          #+#    #+#             */
/*   Updated: 2023/07/25 19:13:18 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_save_instr(t_stacks *stacks, char *instruction)
{
	char	*new_instructions;

	new_instructions = ft_strjoin(stacks->instructions, instruction);
	if (!new_instructions)
		my_exit(STDERR_FILENO, "Error\n", stacks, 1);
	free(stacks->instructions);
	stacks->instructions = new_instructions;
}
