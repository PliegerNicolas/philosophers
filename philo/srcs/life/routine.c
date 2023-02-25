/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:34:19 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/25 13:11:15 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

t_bool	try_ending(t_philosopher *philosopher, t_rules *rules)
{
	pthread_mutex_lock(&rules->end_mutex);
	pthread_mutex_lock(&philosopher->last_meal_mutex);
	if (philosopher->meals == rules->max_meals_per_philo)
	{
		philosopher->status = finished_eating;
		philosopher->meals++;
		rules->all_ate_count++;
		if (rules->all_ate_count == rules->created_philos)
		{
			put_philosopher_action(philosopher, finished_eating);
			rules->end = TRUE;
		}
		philosopher->end = TRUE;
	}
	else if (get_time() >= philosopher->last_meal + rules->time_to_die)
	{
		if (!rules->end)
			put_philosopher_action(philosopher, dead);
		philosopher->status = dead;
		philosopher->end = TRUE;
		rules->end = TRUE;
	}
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
	pthread_mutex_unlock(&rules->end_mutex);
	return (philosopher->end | rules->end);
}

void	try_thinking(t_philosopher *philosopher, t_rules *rules)
{
	if (philosopher->status != sleeping || try_ending(philosopher, rules))
		return ;
	put_philosopher_action(philosopher, thinking);
	philosopher->status = thinking;
}

void	*philosopher_routine(void *ptr)
{
	t_philosopher	*philosopher;
	t_rules			*rules;

	philosopher = (t_philosopher *)ptr;
	rules = philosopher->rules;
	philosopher->last_meal = get_time();
	while (!try_ending(philosopher, rules))
	{
		try_thinking(philosopher, rules);
	}
	return (NULL);
}
