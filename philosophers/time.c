/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferny <bferny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:48:16 by bferny            #+#    #+#             */
/*   Updated: 2021/12/17 22:13:43 by bferny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec) * 1000 + (current_time.tv_usec) / 1000);
}

int	check_time(t_philo **ph)
{
	usleep(10);
	if (get_time() - (*ph)->data->start_time - (*ph)->last_time_eat
		> (*ph)->data->time_to_die + 5)
	{
		message(**ph, DIE, &(*ph)->data);
		pthread_mutex_lock(&(*ph)->data->message);
		(*ph)->death = -1;
		return (-1);
	}
	return (1);
}

int	check_death(t_philo **ph)
{
	unsigned int	i;
	unsigned int	n;

	while ((*ph)->data->nbr_th != (*ph)->data->nbr_of_philo)
		;
	(*ph)->data->start_time = get_time();
	while (1)
	{
		i = 0;
		n = 0;
		while (i < (*ph)->data->nbr_of_philo)
		{
			if ((*ph)[i].eat_count >= (*ph)->data->nmbr_of_eat)
				n++;
			if (n == (*ph)->data->nbr_of_philo)
			{
				pthread_mutex_lock(&(*ph)->data->message);
				return (1);
			}
			if (check_time(&ph[i]) == -1)
				return (-1);
		}
	}
}
