/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smikayel <smikayel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 12:28:13 by ergrigor          #+#    #+#             */
/*   Updated: 2022/07/20 21:32:26 by smikayel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sorted(t_list *a)
{
	while (a->next)
	{
		if(a->n < a->next->n)
			a = a->next;
		else
			return (-1);
	}
	return (0);
		
}

void	sort_3(t_stack *stack)
{
	if ((stack->a->n < stack->a->next->n) && (stack->a->next->n >
	 stack->a->next->next->n))
	{
		rr_all(stack, A);
		if(sorted(stack->a) < 0)
			s_all(stack, A);
	}
	else if (stack->a->n > stack->a->next->n && stack->a->next->n <
	stack->a->next->next->n)
	{
		rr_all(stack, A);
		if (sorted(stack->a) < 0)
			sort_3(stack);
	}
	else if (stack->a->n > stack->a->next->n &&
	stack->a->next->n > stack->a->next->next->n)
	{
		r_all(stack, A);
		s_all(stack, A);
	}
} 


void sort_push(t_stack *stack, int num, int *min, int *max)
{
	int tmp;
	int changed;
	
	tmp = 0;
	changed = 0;
	while (stack->b->next != NULL)
	{
		if (num < *min)
		{
			rr_all(stack, B);
			p_all(stack, B);
			r_all(stack, B);
			r_all(stack, B);
			changed = 1;
			break;
		}
		else if (num < stack->b->n)
		{
			r_all(stack, B);
			tmp++;
		} 
		else
			break;
	}
	if (!changed)
		p_all(stack, B);
	while (tmp != 0)
	{
		rr_all(stack, B);
		tmp--;
	}
	if (num < *min)
		*min = num;
	else if (num > *max)
	{
		rr_all(stack, B);
		s_all(stack, B);
		r_all(stack,B);
		*max = num;
	}
}

void sort_ab_push(t_stack *stack, int num, int *min, int *max)
{
	int n;

	n = 0;
	if (num < *min)
	{
		p_all(stack, A);
		*min = num;
	}
	else if (num > *max)
	{
		p_all(stack, A);
		r_all(stack, A);
		*max = num;
	}
	else 
	{
		while (num > stack->a->n)
		{
			r_all(stack, A);
			n++;
		}
		p_all(stack, A);
		while (n > 0 && stack->b->n < stack->a->n)
		{
			n--;
			rr_all(stack, A);
		}
		// ^^^^^^^^^^^^^^^^^^^^^^^
		r_all(stack, A);
		n++;
		p_all(stack, A);
		while (n > 0)
		{
			rr_all(stack, A);
			n--;
		}
	}
}

void marge(t_stack *stack)
{
	int min;
	int max;

	min = stack->a->n;
	max = stack->a->next->next->n;
	while (stack->b->next != NULL)
		sort_ab_push(stack,  stack->b->n, &min, &max);
	p_all(stack, A);
}

void	push_swap(t_stack *stack)
{
	int max;
	int min;
	
	p_all(stack, B);
	p_all(stack, B);
	if (stack->b->n > stack->b->next->n)
		s_all(stack, B);
	min = stack->b->n;
	max = stack->b->next->n;
	while(stack->a->next->next->next != NULL)
		sort_push(stack, stack->a->n, &min, &max);		
	rr_all(stack, B);
	sort_3(stack);
	marge(stack);
	print_stack(stack->a);


	return ;	
}
