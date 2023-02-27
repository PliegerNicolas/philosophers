/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:17:02 by nplieger          #+#    #+#             */
/*   Updated: 2023/02/27 03:46:32 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

static void	initialize_rules(t_rules *rules, int argc, char **argv)
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
	rules->start_time = get_time();
	pthread_mutex_init(&rules->end_mutex, NULL);
	pthread_mutex_init(&rules->write_mutex, NULL);
}

static t_philosopher	*initialize_philosophers(t_rules *rules)
{
	t_philosopher	*phls;
	int				i;

	phls = malloc(rules->total_philos * sizeof(*phls));
	if (!phls)
		return (NULL);
	i = 0;
	while (i < rules->total_philos)
	{
		phls[i].rules = rules;
		phls[i].id = i + 1;
		phls[i].end = FALSE;
		phls[i].status = sleeping;
		phls[i].last_meal = get_time();
		phls[i].meals = 0;
		pthread_mutex_init(&phls[i].last_meal_mutex, NULL);
		pthread_mutex_init(&phls[i].left_fork, NULL);
		if (i > 0)
			phls[i - 1].right_fork = &phls[i].left_fork;
		if (rules->total_philos > 1 && i == rules->total_philos - 1)
			phls[i].right_fork = &phls[i - rules->total_philos + 1].left_fork;
		rules->created_philos++;
		i++;
	}
	return (phls);
}

t_bool	initialize(t_rules *rules, t_philosopher **philosophers,
	int argc, char **argv)
{
	initialize_rules(rules, argc, argv);
	*philosophers = initialize_philosophers(rules);
	if (!*philosophers)
		return (FALSE);
	return (TRUE);
}
