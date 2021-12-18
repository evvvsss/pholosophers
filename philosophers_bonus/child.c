/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferny <bferny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:32:21 by bferny            #+#    #+#             */
/*   Updated: 2021/12/18 20:36:19 by bferny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	increment_sem(sem_t *sem, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		sem_post(sem);
		i++;
	}
}

void	decrement_sem(sem_t *sem, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		sem_wait(sem);
		i++;
	}
}

void	*check_time_bonus(void *p_ph)
{
	t_data			*data;
	t_philo			*ph;

	ph = (t_philo *)p_ph;
	data = ph->data;
	while (1)
	{
		usleep(20);
		if (ph->eat_count >= data->nmbr_of_eat && data->nmbr_of_eat > 0)
			return (NULL);
		else if (get_time() - data->start_time - ph->last_time_eat
			> data->time_to_die + 5)
		{
			sem_wait(data->message);
			increment_sem(data->finish_eat, data->nbr_of_philo);
			printf("%ld %d %s\n", get_time() - data->start_time, ph->id, DIE);
			sem_post(data->end);
			return (NULL);
		}
	}
}

int	check_death(t_philo **ph, t_data **data)
{
	pthread_t	th;

	th = NULL;
	(*data)->start_time = get_time();
	(*ph)->last_time_eat = get_time() - (*data)->start_time;
	if (pthread_create(&th, NULL, check_time_bonus, (void *)(*ph)) > 0)
	{
		printf("threads creation error\n");
		return (-1);
	}
	if (pthread_detach(th) > 0)
	{
		printf("threads detach error\n");
		return (-1);
	}
	return (1);
}

void	child(t_data **data, t_philo **ph)
{
	sem_wait((*data)->process);
	check_death(ph, data);
	if ((*ph)->id % 2 == 0)
		usleep(60000);
	(*ph)->last_time_eat = get_time() - (*data)->start_time;
	while (1)
	{
		eating_bonus(ph, data);
		if ((*ph)->eat_count >= (*data)->nmbr_of_eat)
			break ;
		sleeping_bonus((*ph), data);
		thinking_bonus((*ph), data);
	}
	exit(0);
}
