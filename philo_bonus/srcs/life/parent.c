/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:30:58 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/27 11:34:08 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

static void	kill_processes_on_death(t_philosopher *philosopher, t_rules *rules)
{
	int		i;

	i = 0;
	while (i < rules->total_philos)
	{
		if ((i + 1) != philosopher->id)
			kill(philosopher->philosophers[i].pid, SIGKILL);
		i++;
	}
}

static void	*exit_thread_routine(void *ptr)
{
	t_philosopher	*philosopher;
	t_rules			*rules;
	int				status;

	philosopher = (t_philosopher *)ptr;
	rules = philosopher->rules;
	status = 0;
	waitpid(philosopher->pid, &status, WEXITSTATUS(status));
	sem_wait(rules->end_sem);
	if (WEXITSTATUS(status) == 1)
		kill_processes_on_death(philosopher, rules);
	else if (WEXITSTATUS(status) == 2)
	{
		if (++rules->all_ate_count >= rules->total_philos)
			put_philosopher_action(philosopher, finished_eating);
	}
	sem_post(rules->end_sem);
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
