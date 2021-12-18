/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferny <bferny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:12:32 by bferny            #+#    #+#             */
/*   Updated: 2021/12/14 22:58:12 by bferny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		j = 0;
		if (ft_strlen(argv[i]) > 10)
		{
			write(2, "Too big argument\n", 17);
			return (-1);
		}
		while (argv[i][j] != '\0')
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
			{	
				write(2, "Wrong argument\n", 15);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	read_args(int argc, char **argv, t_data *data)
{
	if (argc < 5)
	{
		write(2, "Not enough information\n", 23);
		return (-1);
	}
	else if (argc > 6)
	{
		write(2, "Too much information\n", 21);
		return (-1);
	}
	else if (check_args(argc, argv) == 0 && ft_atoi(argv[1]) != 0)
	{
		data->start_time = get_time();
		data->nbr_of_philo = ft_atoi(argv[1]);
		data->time_to_die = ft_atoi(argv[2]);
		data->time_to_eat = ft_atoi(argv[3]);
		data->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			data->nmbr_of_eat = ft_atoi(argv[5]);
		else
			data->nmbr_of_eat = -1;
		return (1);
	}
	return (-1);
}
