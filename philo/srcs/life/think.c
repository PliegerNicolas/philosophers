/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:09:13 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/15 16:19:14 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

/* Force retry if right_fork_mutex isn't defined */
/* This only happens when there is only one philosopher. */
/* Else set thinking state and put action. */
t_bool	try_thinking(t_philosopher *philosopher, t_rules *rules)
{
	if (!philosopher->right_fork_mutex && philosopher->status == thinking)
		return (TRUE);
	if (philosopher->status != sleeping || try_ending(philosopher, rules))
		return (rules->end);
	philosopher->status = thinking;
	put_philosopher_action(philosopher, thinking);
	if (!philosopher->right_fork_mutex)
		return (TRUE);
	return (rules->end);
}
