/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:15:39 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/23 00:42:46 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

static void	post_and_clear(t_rules *rules, t_philosopher *philo,
	t_philosopher *philos)
{
	sem_post(philo->last_meal_sem);
	clear_and_free(rules, philos);
}

static void	exit_child(t_philosopher *philosophers,
	t_philosopher *philosopher, t_rules *rules)
{
	while (1)
	{
		sem_wait(philosopher->last_meal_sem);
		if (rules->end)
		{
			if (philosopher->status == dead)
				put_philosopher_action(philosopher, dead);
			else if (philosopher->status == finished_eating)
			{
				post_and_clear(rules, philosopher, philosophers);
				exit(2);
			}
			post_and_clear(rules, philosopher, philosophers);
			exit (1);
		}
		if (get_time() >= rules->time_to_die + philosopher->last_meal)
		{
			put_philosopher_action(philosopher, dead);
			post_and_clear(rules, philosopher, philosophers);
			exit(1);
		}
		sem_post(philosopher->last_meal_sem);
	}
}

void	create_child(t_philosopher *philosophers, t_philosopher *philosopher,
	t_rules *rules)
{
	philosopher->pid = fork();
	if (philosopher->pid == 0)
	{
		philosopher->last_meal = get_time();
		if (pthread_create(&philosopher->thread, NULL,
				&philosopher_routine, philosopher))
		{
			clear_and_free(rules, philosophers);
			exit (0);
		}
		pthread_detach(philosopher->thread);
		exit_child(philosophers, philosopher, rules);
	}
}
