/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:40:00 by nplieger          #+#    #+#             */
/*   Updated: 2023/02/25 12:16:20 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

static t_bool	launch_philosophers(t_rules *rules, t_philosopher *philosophers)
{
	int		i;

	i = 0;
	while (i < rules->created_philos)
	{
		if (pthread_create(&philosophers[i].thread, NULL,
				&philosopher_routine, &philosophers[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static t_bool	join_threads(t_rules *rules, t_philosopher *philosophers)
{
	int		i;

	i = 0;
	while (i < rules->created_philos)
	{
		if (pthread_join(philosophers[i++].thread, NULL))
		{
			printf("%sError on pthread join.%s\n", RED, DEFAULT_COLOR);
			return (FALSE);
		}
	}
	return (TRUE);
}

t_bool	run_simulation(t_rules *rules, t_philosopher *philosophers)
{
	if (rules->total_philos < 1)
		return (FALSE);
	rules->start_time = get_time();
	if (!launch_philosophers(rules, philosophers))
		return (FALSE);
	if (!join_threads(rules, philosophers))
		return (FALSE);
	return (TRUE);
}
