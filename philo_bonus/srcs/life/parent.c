/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:30:58 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/27 03:31:15 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

static void	*exit_thread_routine(void *ptr)
{
	t_philosopher	*philo;
	int				status;
	int				i;

	philo = (t_philosopher *)ptr;
	status = 0;
	waitpid(philo->pid, &status, WEXITSTATUS(status));
	sem_wait(philo->rules->end_sem);
	if (WEXITSTATUS(status) == 1)
	{
		i = 0;
		while (i < philo->rules->total_philos)
		{
			if ((i + 1) != philo->id)
				kill(philo->philosophers[i].pid, SIGKILL);
			i++;
		}
	}
	else if (WEXITSTATUS(status) == 2)
	{
		if (++philo->rules->all_ate_count >= philo->rules->total_philos)
			put_philosopher_action(philo, finished_eating);
	}
	sem_post(philo->rules->end_sem);
	return (NULL);
}

static void	join_threads(t_philosopher *philosophers, t_rules *rules)
{
	t_philosopher	*philosopher;
	int				i;

	i = 0;
	while (i < rules->total_philos)
	{
		philosopher = &philosophers[i];
		if (pthread_join(philosopher->exit_thread, NULL))
			printf("error in pthread join.\n");
		i++;
	}
}

t_bool	wait_for_childs(t_philosopher *philosophers, t_rules *rules)
{
	t_philosopher	*philosopher;
	int				i;

	i = 0;
	while (i < rules->total_philos)
	{
		philosopher = &philosophers[i];
		philosopher->philosophers = philosophers;
		if (pthread_create(&philosopher->exit_thread, NULL,
				&exit_thread_routine, philosopher))
		{
			clear_and_free(rules, philosophers);
			exit (0);
		}
		i++;
	}
	join_threads(philosophers, rules);
	return (TRUE);
}

t_bool	create_childs(t_philosopher *philosophers, t_rules *rules)
{
	t_philosopher	*philosopher;
	int				i;

	if (rules->created_philos != rules->total_philos)
		return (FALSE);
	i = 0;
	rules->start_time = get_time();
	while (i < rules->total_philos)
	{
		philosopher = &philosophers[i];
		create_child(philosophers, philosopher, rules);
		i++;
	}
	return (TRUE);
}
