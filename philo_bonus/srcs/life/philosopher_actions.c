/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:47:21 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/23 00:22:00 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

t_bool	try_ending(t_philosopher *philosopher, t_rules *rules)
{
	sem_wait(rules->end_sem);
	if (rules->end)
	{
		sem_post(rules->end_sem);
		return (rules->end);
	}
	sem_wait(philosopher->last_meal_sem);
	if (get_time() >= rules->time_to_die + philosopher->last_meal)
	{
		philosopher->status = dead;
		rules->end = TRUE;
	}
	else if (rules->max_meals_per_philo >= 0
		&& philosopher->meals >= rules->max_meals_per_philo)
	{
		philosopher->status = finished_eating;
		rules->end = TRUE;
	}
	sem_post(philosopher->last_meal_sem);
	sem_post(rules->end_sem);
	return (rules->end);
}

t_bool	try_thinking(t_philosopher *philosopher, t_rules *rules)
{
	if (philosopher->status != sleeping || try_ending(philosopher, rules))
		return (rules->end);
	philosopher->status = thinking;
	put_philosopher_action(philosopher, thinking);
	return (rules->end);
}

t_bool	try_grabbing_forks(t_philosopher *philosopher, t_rules *rules)
{
	if (philosopher->status != thinking || try_ending(philosopher, rules))
		return (rules->end);
	sem_wait(rules->grabbing_forks_sem);
	sem_wait(rules->forks_sem);
	sem_wait(rules->forks_sem);
	put_philosopher_action(philosopher, grabbing_fork);
	put_philosopher_action(philosopher, grabbing_fork);
	philosopher->status = grabbing_fork;
	sem_post(rules->grabbing_forks_sem);
	return (rules->end);
}

t_bool	try_eating(t_philosopher *philosopher, t_rules *rules)
{
	if (philosopher->status != grabbing_fork || try_ending(philosopher, rules))
	{
		sem_post(rules->forks_sem);
		sem_post(rules->forks_sem);
		return (rules->end);
	}
	philosopher->status = eating;
	put_philosopher_action(philosopher, eating);
	usleep(rules->time_to_eat * 1000);
	if (try_ending(philosopher, rules))
		return (rules->end);
	sem_post(rules->forks_sem);
	sem_post(rules->forks_sem);
	sem_wait(philosopher->last_meal_sem);
	philosopher->last_meal = get_time();
	sem_post(philosopher->last_meal_sem);
	return (rules->end);
}

t_bool	try_sleeping(t_philosopher *philosopher, t_rules *rules)
{
	if (philosopher->status != eating || try_ending(philosopher, rules))
		return (rules->end);
	philosopher->status = sleeping;
	put_philosopher_action(philosopher, sleeping);
	usleep(rules->time_to_sleep * 1000);
	if (try_ending(philosopher, rules))
		return (rules->end);
	philosopher->meals++;
	return (rules->end);
}
