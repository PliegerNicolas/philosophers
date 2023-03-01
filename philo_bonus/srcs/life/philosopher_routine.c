/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:41:24 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/01 12:49:01 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

t_bool	try_ending(t_philosopher *philosopher, t_rules *rules)
{
	sem_wait(rules->eating_sem);
	sem_wait(rules->finish_sem);
	if ((get_time() > *philosopher->last_meal + rules->time_to_die)
		|| *philosopher->ate_enough || *rules->end)
	{
		sem_post(rules->eating_sem);
		if (!*rules->end && !*philosopher->ate_enough)
			*rules->end = TRUE;
		sem_post(rules->finish_sem);
		return (FALSE);
	}
	sem_post(rules->eating_sem);
	sem_post(rules->finish_sem);
	return (TRUE);
}

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
