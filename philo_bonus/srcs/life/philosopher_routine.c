/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:41:24 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/28 23:16:04 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

void	*philosopher_routine(void *ptr)
{
	t_philosopher	*philosopher;
	t_rules			*rules;

	philosopher = (t_philosopher *)ptr;
	rules = philosopher->rules;
	while (!*rules->end && !*philosopher->ate_enough)
	{
		try_thinking(philosopher, rules);
		try_grabbing_forks(philosopher, rules);
		try_eating(philosopher, rules);
		try_sleeping(philosopher, rules);
	}
	return (NULL);
}
