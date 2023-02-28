/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:47:21 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/28 23:16:44 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

t_bool	try_ending(t_philosopher *philosopher, t_rules *rules)
{
	if (*philosopher->ate_enough)
		return (FALSE);
	sem_wait(rules->eating_sem);
	sem_wait(rules->finish_sem);
	if ((get_time() > *philosopher->last_meal + rules->time_to_die)
		|| *philosopher->ate_enough)
	{
		sem_post(rules->eating_sem);
		if (!*rules->end && !*philosopher->ate_enough)
		{
			sem_post(rules->finish_sem);
			*rules->end = TRUE;
			put_philosopher_action(philosopher, dead);
		}
		sem_post(rules->finish_sem);
		return (FALSE);
	}
	sem_post(rules->eating_sem);
	sem_post(rules->finish_sem);
	return (TRUE);
}

void	try_thinking(t_philosopher *philosopher, t_rules *rules)
{
	if (philosopher->status != sleeping || !try_ending(philosopher, rules))
		return ;
	put_philosopher_action(philosopher, thinking);
	philosopher->status = thinking;
}

void	try_grabbing_forks(t_philosopher *philosopher, t_rules *rules)
{
	if (philosopher->status != thinking || !try_ending(philosopher, rules))
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
	{
		usleep(rules->time_to_die * 1000 + 5);
		return ;
	}
	philosopher->status = grabbing_fork;
	sem_post(rules->grabbing_forks_sem);
}

void	try_eating(t_philosopher *philosopher, t_rules *rules)
{
	if (philosopher->status != grabbing_fork || !try_ending(philosopher, rules))
		return ;
	sem_wait(rules->eating_sem);
	put_philosopher_action(philosopher, eating);
	philosopher->status = eating;
	sem_post(rules->eating_sem);
	usleep(rules->time_to_eat * 1000);
	sem_post(rules->forks_sem);
	sem_post(rules->forks_sem);
	sem_wait(rules->eating_sem);
	*philosopher->last_meal = get_time();
	philosopher->meals++;
	if (rules->max_meals_per_philo > 0
		&& philosopher->meals >= rules->max_meals_per_philo)
	{
		put_philosopher_action(philosopher, thinking);
		*philosopher->ate_enough = TRUE;
	}
	sem_post(rules->eating_sem);
	if (try_ending(philosopher, rules))
		return ;
}

void	try_sleeping(t_philosopher *philosopher, t_rules *rules)
{
	if (philosopher->status != eating || !try_ending(philosopher, rules))
		return ;
	put_philosopher_action(philosopher, sleeping);
	philosopher->status = sleeping;
	usleep(rules->time_to_sleep * 1000);
}
