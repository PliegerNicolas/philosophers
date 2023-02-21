/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:34:19 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/18 03:11:23 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

/* Routine is the first function called by every thread when created. */
/* Get data. Wait for start_time to be defined. */
/* To prevent deadlocks, odd philosophers start with a delay. */
/* In loop, makes philosophers "fight for there survival". */
void	*routine(void *ptr)
{
	t_philosopher	*philosopher;
	t_rules			*rules;

	philosopher = (t_philosopher *)ptr;
	rules = philosopher->rules;
	philosopher->last_meal = rules->start_time;
	while (!try_ending(philosopher, rules))
	{
		if (try_thinking(philosopher, rules))
			continue ;
		if (try_grabbing_forks(philosopher, rules))
			continue ;
		if (try_eating(philosopher, rules))
			continue ;
		if (try_sleeping(philosopher, rules))
			continue ;
	}
	return (NULL);
}
