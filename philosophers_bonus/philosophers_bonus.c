/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferny <bferny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:09:25 by bferny            #+#    #+#             */
/*   Updated: 2021/12/18 20:34:32 by bferny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	create_sem(t_data **data)
{
	sem_unlink("process");
	(*data)->process = sem_open("process", O_CREAT | O_EXCL, 0644, 1);
	if ((*data)->process == SEM_FAILED)
		return (-1);
	sem_wait((*data)->process);
	sem_unlink("end");
	(*data)->end = sem_open("end", O_CREAT | O_EXCL, 0644, 1);
	if ((*data)->end == SEM_FAILED)
		return (-1);
	sem_wait((*data)->end);
	sem_unlink("forks");
	(*data)->forks = sem_open("forks", O_CREAT | O_EXCL, 0644,
			(*data)->nbr_of_philo);
	if ((*data)->forks == SEM_FAILED)
		return (-1);
	sem_unlink("message");
	(*data)->message = sem_open("message", O_CREAT | O_EXCL, 0644, 1);
	if ((*data)->message == SEM_FAILED)
		return (-1);
	sem_unlink("finish_eat");
	(*data)->finish_eat = sem_open("finish_eat", O_CREAT | O_EXCL, 0644, 1);
	if ((*data)->finish_eat == SEM_FAILED)
		return (-1);
	return (1);
}

void	init_philo_params_bonus(t_data **data, int id)
{
	(*data)->ph[id] = malloc(sizeof(t_philo));
	(*data)->ph[id]->data = *data;
	(*data)->ph[id]->id = id + 1;
	(*data)->ph[id]->last_time_eat = get_time() - (*data)->start_time;
	if ((*data)->nmbr_of_eat == -1)
		(*data)->ph[id]->eat_count = -2;
	else
		(*data)->ph[id]->eat_count = 0;
}

int	new_philo_bonus(t_data *data)
{
	unsigned int	id;

	id = 0;
	data->ph = malloc(sizeof(t_philo *) * data->nbr_of_philo);
	if (data->ph == NULL)
		return (-1);
	while (id < data->nbr_of_philo)
	{
		init_philo_params_bonus(&data, id);
		id++;
	}
	return (1);
}

int	create_pr(t_data **data)
{
	unsigned int	i;

	i = 0;
	while (i < (*data)->nbr_of_philo)
	{
		(*data)->ph[i]->pid = fork();
		if ((*data)->ph[i]->pid == -1)
			return (finish_pr(data));
		else if ((*data)->ph[i]->pid == 0)
			child(data, &(*data)->ph[i]);
		else
			i++;
	}
	increment_sem((*data)->process, (*data)->nbr_of_philo);
	if ((*data)->nmbr_of_eat > 0)
	{
		sem_wait((*data)->finish_eat);
		decrement_sem((*data)->finish_eat, (*data)->nbr_of_philo);
		sem_wait((*data)->message);
	}
	else
		sem_wait((*data)->end);
	finish_pr(data);
	return (1);
}

t_data	*new_data_bonus(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	if (read_args_bonus(argc, argv, &data) == -1)
	{	
		free(data);
		return (NULL);
	}
	data->forks = NULL;
	data->message = NULL;
	data->end = NULL;
	data->process = NULL;
	if (data->nmbr_of_eat == 0)
	{	
		free(data);
		return (NULL);
	}
	if (create_sem(&data) == -1)
	{	
		free(data);
		return (NULL);
	}
	return (data);
}
