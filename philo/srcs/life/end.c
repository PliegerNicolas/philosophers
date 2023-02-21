/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:49:31 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/15 16:15:11 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

/* This function is called if max_meals_per_philosopher is not negative. */
/* If negative, it means there is no max meals. */
/* For every philosopher that reaches there max meal, */
/* increment all_ate_count until all_ate_count = nbr of philosophers. */
static void	check_max_meals(t_philosopher *philosopher, t_rules *rules)
{
	if (philosopher->meals == rules->max_meals_per_philo)
	{
		rules->all_ate_count += 1;
		philosopher->meals++;
	}
	if (rules->all_ate_count >= rules->total_philos)
	{
		put_philosopher_action(philosopher, finished_eating);
		rules->end = TRUE;
	}
}

/* Verifies if philosopher hasn't spent time_to_die without eating. */
/* Exits loop if end is put to TRUE in every case. */
t_bool	try_ending(t_philosopher *philosopher, t_rules *rules)
{
	pthread_mutex_lock(&rules->end_mutex);
	if (rules->end)
	{
		pthread_mutex_unlock(&rules->end_mutex);
		return (rules->end);
	}
	pthread_mutex_lock(&philosopher->last_meal_mutex);
	if (get_time() >= (rules->time_to_die + philosopher->last_meal))
	{
		philosopher->status = dead;
		put_philosopher_action(philosopher, dead);
		rules->end = TRUE;
	}
	else if (rules->max_meals_per_philo >= 0)
		check_max_meals(philosopher, rules);
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
	pthread_mutex_unlock(&rules->end_mutex);
	return (rules->end);
}
