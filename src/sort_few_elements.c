/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_few_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 18:06:27 by tkuramot          #+#    #+#             */
/*   Updated: 2023/07/23 12:40:52 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

static void	sort_2_reverse(t_deque *deq, bool to_a)
{
	long long	sta[2];

	sta[0] = deque_get_at(deq, 0);
	sta[1] = deque_get_at(deq, 1);
	if (sta[0] < sta[1])
		stack_swap(deq);
}

void	sort_2(t_stacks *stacks, char cur_sta)
{
	long long	sta[2];

	sta[0] = stack_get_at(stacks, cur_sta, 0);
	sta[1] = stack_get_at(stacks, cur_sta, 1);
	if (sta[0] > sta[1])
		stack_swap(stacks, cur_sta);
}

void	sort_3(t_stacks *stacks, char cur_sta)
{
	long long	sta[3];
	long long	idx;

	idx = 0;
	while (idx < 3)
	{
		sta[idx] = stack_get_at(stacks, cur_sta, idx);
		idx++;
	}
	if (sta[0] < sta[1] && sta[1] > sta[2] && sta[2] > sta[0])
	{
		stack_rrotate(stacks, cur_sta);
		stack_swap(stacks, cur_sta);
	}
	else if (sta[0] > sta[1] && sta[1] < sta[2] && sta[2] > sta[0])
		stack_swap(stacks, cur_sta);
	else if (sta[0] < sta[1] && sta[1] > sta[2] && sta[2] < sta[0])
		stack_rrotate(stacks, cur_sta);
	else if (sta[0] > sta[1] && sta[1] < sta[2] && sta[2] < sta[0])
		stack_rotate(stacks, cur_sta);
	else if (sta[0] > sta[1] && sta[1] > sta[2] && sta[2] < sta[0])
	{
		stack_rotate(stacks, cur_sta);
		stack_swap(stacks, cur_sta);
	}
}

void	sort_4(t_stacks *stacks, char cur_sta)
{
	char		another_sta;
	long long	pivot;
	long long	idx;

	another_sta = 'a' + (cur_sta == 'a');
	pivot = stack_get_min_value(stacks, cur_sta, 4) + 1;
	idx = 0;
	while (idx < 4)
	{
		if (stack_get_at(stacks, cur_sta, 0) > pivot)
			stack_rotate(stacks, cur_sta);
		else
			stack_push(stacks, another_sta);
		idx++;
	}
	sort_2(stacks, cur_sta);
	sort_2_reverse(stacks, another_sta);
	idx = 0;
	while (idx++ < 2)
		stack_push(stacks, cur_sta);
}

void	sort_5(t_stacks *stacks, char cur_sta)
{
	char		another_sta;
	long long	pivot;
	long long	idx;

	another_sta = 'a' + (cur_sta == 'a');
	pivot = stack_get_min_value(stacks, cur_sta, 5) + 1;
	idx = 0;
	while (idx < 5)
	{
		if (stack_get_at(stacks, cur_sta, 0) > pivot)
			stack_rotate(stacks, cur_sta);
		else
			stack_push(stacks, another_sta);
		idx++;
	}
	sort_3(stacks, cur_sta);
	sort_2_reverse(stacks, another_sta);
	idx = 0;
	while (idx++ < 2)
		stack_push(stacks, cur_sta);
}
