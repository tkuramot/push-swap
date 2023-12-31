/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:12:32 by tkuramot          #+#    #+#             */
/*   Updated: 2023/07/24 18:00:27 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	execute_op(t_stacks *stacks, long long op, bool on_a)
{
	if (on_a)
	{
		if (op > 0)
			while (op--)
				stack_ra(stacks);
		else
			while (op++)
				stack_rra(stacks);
	}
	else
	{
		if (op > 0)
			while (op--)
				stack_rb(stacks);
		else
			while (op++)
				stack_rrb(stacks);
	}
}

static void	compress_ops(t_stacks *stacks, long long idx)
{
	long long	a_ops;
	long long	b_ops;
	long long	common_ops;

	a_ops = stacks->alpha[idx];
	b_ops = stacks->beta[idx];
	if (a_ops * b_ops < 0)
		return ;
	common_ops = my_min(my_abs(a_ops), my_abs(b_ops));
	if (stacks->alpha[idx] > 0)
	{
		stacks->alpha[idx] -= common_ops;
		stacks->beta[idx] -= common_ops;
		while (common_ops--)
			stack_rr(stacks);
	}
	else
	{
		stacks->alpha[idx] += common_ops;
		stacks->beta[idx] += common_ops;
		while (common_ops--)
			stack_rrr(stacks);
	}
}

static void	rotate_continuous(t_stacks *stacks)
{
	long long	a_front;
	long long	a_back;
	long long	should_rotate;

	a_front = deque_get_at(&stacks->a, 0);
	a_back = deque_get_at(&stacks->a, stacks->a.sz - 1);
	should_rotate = (deque_get_at(&stacks->a, 0) > stacks->a.capacity / 2);
	if (should_rotate)
	{
		while (a_front == a_back + 1)
		{
			stack_ra(stacks);
			a_front = deque_get_at(&stacks->a, 0);
			a_back = deque_get_at(&stacks->a, stacks->a.sz - 1);
		}
	}
	else
	{
		while (a_front == a_back + 1)
		{
			stack_rra(stacks);
			a_front = deque_get_at(&stacks->a, 0);
			a_back = deque_get_at(&stacks->a, stacks->a.sz - 1);
		}
	}
}

// Get stack B index of the least operations
static long long	get_min_ops_idx(t_stacks *stacks)
{
	long long	idx_b;
	long long	min_idx_b;
	long long	ops;
	long long	min_ops;

	idx_b = 0;
	min_ops = LLONG_MAX;
	while (idx_b < stacks->b.sz)
	{
		ops = my_abs(stacks->alpha[idx_b]) + my_abs(stacks->beta[idx_b]);
		if (ops < min_ops)
		{
			min_idx_b = idx_b;
			min_ops = ops;
		}
		idx_b++;
	}
	return (min_idx_b);
}

void	execute_ops(t_stacks *stacks)
{
	long long	min_idx_b;

	while (stacks->b.sz)
	{
		simulate_ops(stacks);
		min_idx_b = get_min_ops_idx(stacks);
		compress_ops(stacks, min_idx_b);
		execute_op(stacks, convert_idx_to_ops(stacks->alpha[min_idx_b],
				stacks->a.sz), true);
		execute_op(stacks, convert_idx_to_ops(stacks->beta[min_idx_b],
				stacks->b.sz), false);
		stack_pa(stacks);
	}
	rotate_continuous(stacks);
}
