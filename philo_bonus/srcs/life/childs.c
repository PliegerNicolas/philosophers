/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:15:39 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/28 22:09:01 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

static void	exit_child(t_philosopher *philosophers,
	t_philosopher *philosopher, t_rules *rules)
{
	while (1)
	{
		sem_wait(rules->eating_sem);
		if (*philosopher->ate_enough)
		{
			sem_post(rules->eating_sem);
			clear_and_free(rules, philosophers);
			exit(2);
		}
		sem_post(rules->eating_sem);
		sem_wait(rules->finish_sem);
		if (get_time() > *philosopher->last_meal + rules->time_to_die)
		{
			if (!rules->end)
				put_philosopher_action(philosopher, dead);
			clear_and_free(rules, philosophers);
			exit (1);
		}
		sem_post(rules->finish_sem);
	}
}

void	create_child(t_philosopher *philosophers, t_philosopher *philosopher,
	t_rules *rules)
{
	philosopher->pid = fork();
	if (philosopher->pid == 0)
	{
		*philosopher->last_meal = get_time();
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
