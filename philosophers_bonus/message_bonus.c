/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferny <bferny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 20:22:25 by bferny            #+#    #+#             */
/*   Updated: 2021/12/18 20:03:18 by bferny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	message_bonus(t_data **data, int id, char *s)
{
	sem_wait((*data)->message);
	printf("%ld %d %s\n", get_time() - (*data)->start_time, id, s);
	sem_post((*data)->message);
}

void	destroy_all_bonus(t_data **data)
{
	unsigned int	i;

	i = 0;
	while (i < (*data)->nbr_of_philo)
	{
		free((*data)->ph[i]);
		i++;
	}
	if ((*data)->forks)
	{	
		increment_sem((*data)->forks, (*data)->nbr_of_philo);
		sem_close((*data)->forks);
	}
	if ((*data)->message)
	{
		sem_post((*data)->message);
		sem_close((*data)->message);
	}
	if ((*data)->finish_eat)
		sem_close((*data)->finish_eat);
	if ((*data)->process)
		sem_close((*data)->process);
	if ((*data)->end)
		sem_close((*data)->end);
	free(*data);
}
