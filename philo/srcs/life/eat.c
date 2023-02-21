/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:08:44 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/15 16:18:22 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

/* Lock fork mutexes. */
static void	lock_forks(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->left_fork_mutex);
	pthread_mutex_lock(philosopher->right_fork_mutex);
}

/* Unlock fork mutexes. */
static void	unlock_forks(t_philosopher *philosopher)
{
	pthread_mutex_unlock(philosopher->right_fork_mutex);
	pthread_mutex_unlock(philosopher->left_fork_mutex);
}

/* If wrong status or end, exit with end status */
/* = >FALSE means go to next action. TRUE means exit loop. */
/* Locks fork mutexes and puts actions. */
t_bool	try_grabbing_forks(t_philosopher *philosopher, t_rules *rules)
{
	if (philosopher->status != thinking || try_ending(philosopher, rules)
		|| !philosopher->right_fork_mutex)
		return (rules->end);
	lock_forks(philosopher);
	philosopher->status = grabbing_fork;
	put_philosopher_action(philosopher, grabbing_fork);
	put_philosopher_action(philosopher, grabbing_fork);
	return (FALSE);
}

/* If wrong status or end, exit with end status. */
/* = >FALSE means go to next action. TRUE means exit loop. */
/* Releases mutexes closed in try_grabbing_forks in every case. */
/* Puts action and waits time_to_eat. Verifies if not dead while eating. */
/* Updates last meal time and number of consumed meals. */
/* usleep is in microseconds. Our values are in milliseconds. Thus nbr x 1000 */
t_bool	try_eating(t_philosopher *philosopher, t_rules *rules)
{
	if (philosopher->status != grabbing_fork || try_ending(philosopher, rules))
	{
		unlock_forks(philosopher);
		return (rules->end);
	}
	philosopher->status = eating;
	put_philosopher_action(philosopher, eating);
	usleep(rules->time_to_eat * 1000);
	unlock_forks(philosopher);
	if (try_ending(philosopher, rules))
		return (rules->end);
	pthread_mutex_lock(&philosopher->last_meal_mutex);
	philosopher->last_meal = get_time();
	philosopher->meals++;
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
	return (rules->end);
}
