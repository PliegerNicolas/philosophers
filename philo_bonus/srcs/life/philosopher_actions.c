/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:47:21 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/28 14:33:43 by nplieger         ###   ########.fr       */
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
	if (rules->max_meals_per_philo >= 0
		&& philosopher->meals == rules->max_meals_per_philo)
	{
		philosopher->meals++;
		put_philosopher_action(philosopher, thinking);
		philosopher->status = finished_eating;
		rules->end = TRUE;
	}
	else if (get_time() >= rules->time_to_die + philosopher->last_meal)
	{
		philosopher->status = dead;
		rules->end = TRUE;
	}
	sem_post(rules->end_sem);
	return (rules->end);
}

void	try_thinking(t_philosopher *philosopher, t_rules *rules)
{
	if (philosopher->status != sleeping || try_ending(philosopher, rules))
		return ;
	put_philosopher_action(philosopher, thinking);
	philosopher->status = thinking;
}

void	try_grabbing_forks(t_philosopher *philosopher, t_rules *rules)
{
	if (philosopher->status != thinking || try_ending(philosopher, rules))
		return ;
	sem_wait(rules->grabbing_forks_sem);
	sem_wait(rules->forks_sem);
	put_philosopher_action(philosopher, grabbing_fork);
	if (rules->total_philos > 1)
	{
		sem_wait(rules->forks_sem);
		put_philosopher_action(philosopher, grabbing_fork);
	}
	else
		usleep(rules->time_to_die * 1000);
	philosopher->status = grabbing_fork;
	sem_post(rules->grabbing_forks_sem);
}

void	try_eating(t_philosopher *philosopher, t_rules *rules)
{
	if (philosopher->status != grabbing_fork || try_ending(philosopher, rules))
		return ;
	put_philosopher_action(philosopher, eating);
	philosopher->status = eating;
	usleep(rules->time_to_eat * 1000);
	if (try_ending(philosopher, rules))
		return ;
	sem_post(rules->forks_sem);
	sem_post(rules->forks_sem);
	sem_wait(philosopher->last_meal_sem);
	philosopher->last_meal = get_time();
	philosopher->meals++;
	sem_post(philosopher->last_meal_sem);
}

void	try_sleeping(t_philosopher *philosopher, t_rules *rules)
{
	if (philosopher->status != eating || try_ending(philosopher, rules))
		return ;
	put_philosopher_action(philosopher, sleeping);
	philosopher->status = sleeping;
	usleep(rules->time_to_sleep * 1000);
	(void)try_ending(philosopher, rules);
}
