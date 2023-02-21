/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_rules.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:27:35 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/15 09:47:34 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

/* Initializes the rules. */
/* start_time is set as null. it fill trigger start of every */
/* thread when assigned a value. */
void	initialize_rules(t_rules *rules, int argc, char **argv)
{
	rules->end = FALSE;
	pthread_mutex_init(&rules->end_mutex, NULL);
	rules->total_philos = (int)ft_atolli(argv[0]);
	rules->time_to_die = (int)ft_atolli(argv[1]);
	rules->time_to_eat = (int)ft_atolli(argv[2]);
	rules->time_to_sleep = (int)ft_atolli(argv[3]);
	if (argc == 5)
		rules->max_meals_per_philo = (int)ft_atolli(argv[4]);
	else
		rules->max_meals_per_philo = -1;
	rules->start_time = 0;
	rules->all_ate_count = 0;
}
