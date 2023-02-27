/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:15:39 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/27 11:48:17 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

static void	exit_child(t_philosopher *philosophers,
	t_philosopher *philosopher, t_rules *rules)
{
	while (1)
	{
		sem_wait(rules->end_sem);
		if (rules->end)
		{
			if (philosopher->status == finished_eating)
			{
				sem_post(rules->end_sem);
				clear_and_free(rules, philosophers);
				exit(2);
			}
			if (!rules->dead_sem->__align)
			{
				put_philosopher_action(philosopher, dead);
				sem_post(rules->write_sem);
				sem_post(rules->dead_sem);
			}
			sem_post(rules->end_sem);
			clear_and_free(rules, philosophers);
			exit(1);
		}
		sem_post(rules->end_sem);
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
