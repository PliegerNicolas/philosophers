/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:30:49 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/28 17:20:15 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

static t_bool	initialize_rules(t_rules *rules, int argc, char **argv)
{
	rules->total_philos = (int)ft_atolli(argv[0]);
	rules->created_philos = 0;
	rules->time_to_die = (int)ft_atolli(argv[1]);
	rules->time_to_eat = (int)ft_atolli(argv[2]);
	rules->time_to_sleep = (int)ft_atolli(argv[3]);
	if (argc == 5)
		rules->max_meals_per_philo = (int)ft_atolli(argv[4]);
	else
		rules->max_meals_per_philo = -1;
	rules->end = FALSE;
	rules->all_ate_count = 0;
	rules->start_time = 0;
	rules->forks_sem = NULL;
	rules->write_sem = NULL;
	rules->grabbing_forks_sem = NULL;
	rules->end_sem = NULL;
	rules->eating_sem = NULL;
	rules->finish_sem = NULL;
	return (TRUE);
}

static void	set_pointer_for_last_meal(t_philosopher *philosopher)
{
	size_t	last_meal;

	last_meal = 0;
	philosopher->last_meal = &last_meal;
}

static void	set_pointer_for_ate_enough(t_philosopher *philosopher)
{
	t_bool	ate_enough;
	ate_enough = FALSE;
	philosopher->ate_enough = &ate_enough;
}

static t_philosopher	*initialize_philosophers(t_rules *rules)
{
	t_philosopher	*philosophers;
	int				i;

	philosophers = malloc(rules->total_philos * sizeof(*philosophers));
	if (!philosophers)
		return (NULL);
	i = 0;
	while (i < rules->total_philos)
	{
		philosophers[i].rules = rules;
		philosophers[i].id = i + 1;
		philosophers[i].pid = -1;
		philosophers[i].status = sleeping;
		philosophers[i].meals = 0;
		set_pointer_for_ate_enough(&philosophers[i]);
		set_pointer_for_last_meal(&philosophers[i]);
		philosophers[i].thread = 0;
		philosophers[i].exit_thread = 0;
		philosophers[i].philosophers = NULL;
		rules->created_philos++;
		i++;
	}
	return (philosophers);
}

static t_bool	initialize_semaphores(t_rules *rules)
{
	rules->forks_sem = sem_open_new("/forks", rules->total_philos);
	if (!rules->forks_sem)
		return (FALSE);
	rules->write_sem = sem_open_new("/write", 1);
	if (!rules->write_sem)
		return (FALSE);
	rules->grabbing_forks_sem = sem_open_new("/grabbing_forks", 1);
	if (!rules->grabbing_forks_sem)
		return (FALSE);
	rules->end_sem = sem_open_new("/end", 1);
	if (!rules->end_sem)
		return (FALSE);
	rules->eating_sem = sem_open_new("/eating", 1);
	if (!rules->eating_sem)
		return (FALSE);
	rules->finish_sem = sem_open_new("/finish", 1);
	if (!rules->finish_sem)
		return (FALSE);
	return (TRUE);
}

t_bool	initialize(t_rules *rules, t_philosopher **philosophers, int argc,
	char **argv)
{
	if (!initialize_rules(rules, argc, argv))
		return (FALSE);
	*philosophers = initialize_philosophers(rules);
	if (!*philosophers)
		return (FALSE);
	if (!initialize_semaphores(rules))
		return (FALSE);
	return (TRUE);
}
