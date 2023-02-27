/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_action.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:40:44 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/27 15:28:24 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

void	put_philosopher_action(t_philosopher *philo, enum e_status action)
{
	size_t		time;

	pthread_mutex_lock(&philo->rules->write_mutex);
	pthread_mutex_lock(&philo->rules->last_write_mutex);
	time = get_time() - philo->rules->start_time;
	if (action == dead)
		printf("%s%06ld %s%d%s died%s\n", LIGHT_GRAY, time,
			LIGHT_CYAN, philo->id, RED, DEFAULT_COLOR);
	else if (action == finished_eating)
		printf("%s%06ld %sAll finished eating%s\n",
			LIGHT_GRAY, time, GREEN, DEFAULT_COLOR);
	else if (action == eating && !(philo->end | philo->rules->end))
		printf("%s%06ld %s%d%s is eating%s\n", LIGHT_GRAY, time,
			LIGHT_CYAN, philo->id, LIGHT_GRAY, DEFAULT_COLOR);
	else if (action == sleeping && !(philo->end | philo->rules->end))
		printf("%s%06ld %s%d%s is sleeping%s\n", LIGHT_GRAY, time,
			LIGHT_CYAN, philo->id, LIGHT_GRAY, DEFAULT_COLOR);
	else if (action == thinking && !(philo->end | philo->rules->end))
		printf("%s%06ld %s%d%s is thinking%s\n", LIGHT_GRAY, time,
			LIGHT_CYAN, philo->id, LIGHT_GRAY, DEFAULT_COLOR);
	else if (action == grabbing_fork && !(philo->end | philo->rules->end))
		printf("%s%06ld %s%d%s has taken a fork%s\n", LIGHT_GRAY,
			time, LIGHT_CYAN, philo->id, LIGHT_GRAY, DEFAULT_COLOR);
	pthread_mutex_unlock(&philo->rules->last_write_mutex);
	pthread_mutex_unlock(&philo->rules->write_mutex);
}
