/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:55:46 by nplieger          #+#    #+#             */
/*   Updated: 2023/02/24 15:25:13 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

t_bool	try_ending(t_philosopher *philosopher, t_rules *rules)
{
	if (rules->end)
		return (rules->end);
	pthread_mutex_lock(&rules->end_mutex);
	pthread_mutex_lock(&philosopher->last_meal_mutex);
	if (rules->max_meals_per_philo >= 0
		&& philosopher->meals == rules->max_meals_per_philo)
	{
		philosopher->meals++;
		rules->all_ate_count++;
		if(rules->all_ate_count == rules->total_philos)
		{
			put_philosopher_action(philosopher, thinking);
			rules->end = TRUE;
		}
		philosopher->status = finished_eating;
	}
	else if (get_time() >= rules->time_to_die + philosopher->last_meal && philosopher->status != finished_eating)
	{
		philosopher->status = dead;
		if (!rules->end)
			put_philosopher_action(philosopher, dead);
		rules->end = TRUE;
	}
	pthread_mutex_unlock(&rules->end_mutex);
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
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
	pthread_mutex_lock(&philosopher->left_fork_mutex);
	pthread_mutex_lock(philosopher->right_fork_mutex);
	put_philosopher_action(philosopher, grabbing_fork);
	put_philosopher_action(philosopher, grabbing_fork);
	philosopher->status = grabbing_fork;
}

void	try_eating(t_philosopher *philosopher, t_rules *rules)
{
	if (philosopher->status != grabbing_fork || try_ending(philosopher, rules))
	{
		pthread_mutex_unlock(&philosopher->left_fork_mutex);
		pthread_mutex_unlock(philosopher->right_fork_mutex);
		return ;
	}
	put_philosopher_action(philosopher, eating);
	philosopher->status = eating;
	usleep(rules->time_to_eat * 1000);
	if (try_ending(philosopher, rules))
		return ;
	pthread_mutex_unlock(&philosopher->left_fork_mutex);
	pthread_mutex_unlock(philosopher->right_fork_mutex);
	pthread_mutex_lock(&philosopher->last_meal_mutex);
	philosopher->last_meal = get_time();
	philosopher->meals++;
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
}

void	try_sleeping(t_philosopher *philosopher, t_rules *rules)
{
	if (philosopher->status != eating || try_ending(philosopher, rules))
		return ;
	put_philosopher_action(philosopher, sleeping);
	philosopher->status = sleeping;
	usleep(rules->time_to_sleep * 1000);
	try_ending(philosopher, rules);
}
