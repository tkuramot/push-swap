/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:12:32 by tkuramot          #+#    #+#             */
/*   Updated: 2023/07/18 16:57:49 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

static long long	my_abs(long long nbr)
{
	if (nbr < 0)
		return nbr * -1;
	return nbr;
}

// Positive ops refers to how many of rotateing is needed and
// negative ops refers to that of reverse rotating
// Negative ops needs extra one op to push it to another stack
static void		simulate_all_ops(t_stacks *stacks)
{
	long long	idx_b;
	long long	idx_a;
	long long	ele;
	long long	ops;

	idx_b = 0;
	while (idx_b < stacks->b.sz)
	{
		if (idx_b < stacks->b.sz / 2)
			ops = idx_b;
		else
			ops = -(stacks->b.sz - idx_b + 1);
		stacks->beta[ele] = ops;
		idx_a = 0;
		ops = 0;
		ele = stack_get_at(stacks, 'b', idx_b);
		while (stack_get_at(stacks, 'a', idx_a++) > ele)
			ops++;
		if (idx_a < stacks->a.sz / 2)
			ops = idx_a;
		else
			ops = -(stacks->a.sz - ops + 1);
		stacks->alpha[ele] = ops;
	}
}

// Get the minimum operation to push one of stack B elements to stack A
static void	get_ops(t_stacks *stacks, long long *a_ops, long long *b_ops)
{
	long long	ops;
	long long	min_ops;
	long long	idx_b;
	long long	min_idx_b;

	simulate_all_ops(stacks);
	min_ops = LLONG_MAX;
	min_idx_b = 0;
	idx_b = 0;
	while (idx_b < stacks->a.sz)
	{
		ops = my_abs(stacks->alpha[stack_get_at(stacks, 'b', idx_b)])
			+ my_abs(stacks->beta[stack_get_at(stacks, 'b', idx_b)]);
		if (ops < min_ops)
		{
			min_ops = ops;
			min_idx_b = idx_b;
		}
		idx_b++;
	}
	*a_ops = stacks->alpha[min_idx_b];
	*b_ops = stacks->beta[min_idx_b];
}

static void		execute_ops(t_stacks *stacks, long long ops, char cur_sta)
{
	while (ops)
	{
		if (ops > 0)
		{
			stack_rotate(stacks, cur_sta);
			ops--;
		}
		if (ops < 0)
		{
			stack_rrotate(stacks, cur_sta);
			ops++;
		}
	}
}

void		push_a_back(t_stacks *stacks)
{
	long long	a_ops;
	long long	b_ops;

	while (stacks->b.sz)
	{
		get_ops(stacks, &a_ops, &b_ops);
		execute_ops(stacks, a_ops, 'a');
		execute_ops(stacks, b_ops, 'b');
		stack_push(stacks, 'a');
		while (a_ops)
		{
			if (a_ops > 0)
			{
				stack_rrotate(stacks, 'a');
				a_ops--;
			}
			if (a_ops < 0)
			{
				stack_rotate(stacks, 'a');
				a_ops++;
			}
		}
	}
}