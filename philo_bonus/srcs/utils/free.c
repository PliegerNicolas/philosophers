/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:35:17 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/28 23:13:05 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

static void	clear_rules(t_rules *rules)
{
	if (rules->forks_sem)
		sem_close(rules->forks_sem);
	if (rules->write_sem)
		sem_close(rules->write_sem);
	if (rules->grabbing_forks_sem)
		sem_close(rules->grabbing_forks_sem);
	if (rules->end_sem)
		sem_close(rules->end_sem);
	if (rules->eating_sem)
		sem_close(rules->eating_sem);
	if (rules->finish_sem)
		sem_close(rules->finish_sem);
	if (rules->end)
		free(rules->end);
}

static void	clear_philosophers(t_rules *rules, t_philosopher *philosophers)
{
	int		i;

	i = 0;
	if (philosophers)
	{
		while (i < rules->created_philos)
		{
			if (philosophers[i].last_meal)
				free(philosophers[i].last_meal);
			if (philosophers[i].ate_enough)
				free(philosophers[i].ate_enough);
			i++;
		}
		free(philosophers);
	}
}

t_bool	clear_and_free(t_rules *rules, t_philosopher *philosophers)
{
	clear_rules(rules);
	clear_philosophers(rules, philosophers);
	return (TRUE);
}
