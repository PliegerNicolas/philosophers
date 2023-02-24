/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:35:17 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/24 12:58:38 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

t_bool	clear_and_free(t_rules *rules, t_philosopher *philosophers)
{
	int			i;

	pthread_mutex_destroy(&rules->forks_mutex);
	pthread_mutex_destroy(&rules->end_mutex);
	if (philosophers)
	{
		i = 0;
		while (i < rules->created_philos)
			pthread_mutex_destroy(&philosophers[i++].last_meal_mutex);
		free(philosophers);
	}
	return (TRUE);
}
