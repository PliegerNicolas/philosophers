/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:42:39 by nplieger          #+#    #+#             */
/*   Updated: 2023/02/17 12:26:13 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

void	put_usage_indication(void)
{
	printf("%sExpected inputs, in order :\n", CYAN);
	printf("॰ Number_of_philosophers (int) [%sMAX = %d, MIN = 2%s].\n",
		GREEN, MAX_PHILOSOPHERS, CYAN);
	printf("॰ Time_to_die (ms).\n");
	printf("॰ Time_to_eat (ms).\n");
	printf("॰ Time_to_sleep (ms).\n");
	printf("॰ Maximal_meals_per_philosopher (int) [%soptional%s].%s\n",
		GREEN, CYAN, DEFAULT_COLOR);
}
