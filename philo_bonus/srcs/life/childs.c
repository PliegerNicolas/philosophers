/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:15:39 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/01 12:42:36 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

static void	exit_child_on_death(t_philosopher *philosophers,
	t_philosopher *philosopher, t_rules *rules)
{
	if (!rules->end_sem->__align)
		put_philosopher_action(philosopher, dead);
	else if (philosopher->status != thinking)
		put_philosopher_action(philosopher, thinking);
	sem_post(rules->end_sem);
	*rules->end = TRUE;
	sem_post(rules->finish_sem);
	if (pthread_join(philosopher->thread, NULL))
		printf("error in pthread join1.\n");
	clear_and_free(rules, philosophers);
	exit (1);
}

static void	exit_child_on_filled_stomach(t_philosopher *philosophers,
	t_philosopher *philosopher, t_rules *rules)
{
	sem_post(rules->eating_sem);
	if (pthread_join(philosopher->thread, NULL))
		printf("error in pthread join1.\n");
	clear_and_free(rules, philosophers);
	exit(2);
}

static void	exit_child(t_philosopher *philosophers,
	t_philosopher *philosopher, t_rules *rules)
{
	while (1)
	{
		sem_wait(rules->eating_sem);
		if (*philosopher->ate_enough)
			exit_child_on_filled_stomach(philosophers, philosopher, rules);
		sem_post(rules->eating_sem);
		sem_wait(rules->finish_sem);
		if (get_time() > *philosopher->last_meal + rules->time_to_die)
			exit_child_on_death(philosophers, philosopher, rules);
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
		exit_child(philosophers, philosopher, rules);
	}
}
