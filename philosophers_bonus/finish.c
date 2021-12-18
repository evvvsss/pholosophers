/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferny <bferny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:32:25 by bferny            #+#    #+#             */
/*   Updated: 2021/12/17 22:21:58 by bferny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	finish_pr(t_data **data)
{
	unsigned int	i;

	i = 0;
	while (i < (*data)->nbr_of_philo && (*data)->ph[i]->pid != -1)
	{
		kill((*data)->ph[i]->pid, SIGKILL);
		i++;
	}
	return (-1);
}
