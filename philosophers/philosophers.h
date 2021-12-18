/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bferny <bferny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:12:15 by bferny            #+#    #+#             */
/*   Updated: 2021/12/17 22:07:23 by bferny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# define MAX 922337203685477580
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

typedef struct s_philo
{
	pthread_t			th;
	unsigned int		id;
	unsigned long		last_time_eat;
	int					eat_count;
	int					death;
	struct s_data		*data;
}				t_philo;

typedef struct s_data
{
	unsigned int		nbr_of_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	int					nmbr_of_eat;
	pthread_mutex_t		*forks;
	pthread_mutex_t		message;
	unsigned int		nbr_th;
	unsigned long		start_time;
	t_philo				*ph;
}				t_data;

unsigned long	get_time(void);
int				check_time(t_philo **ph);
void			message(t_philo ph, char *message, t_data **data);
int				check_args(int argc, char **argv);
int				read_args(int argc, char **argv, t_data *data);
t_data			*new_data(int argc, char **argv);
void			new_forks(t_data **data);
void			init_eating(t_philo *ph, t_data **data);
void			init_philo_params(t_philo *ph, int id, t_data **data);
int				new_philo(t_data **data);
void			destroy_forks(pthread_mutex_t *forks, t_data **data);
void			destroy_philo(t_data **data);
void			eating(t_philo *ph);
void			thinking(t_philo *ph);
void			sleeping(t_philo *ph);
void			*life(void *p_philo);
int				check_death(t_philo **ph);
int				create_th(t_data **data);
void			destroy_all(t_data **data);
size_t			ft_strlen(const char *s);
int				ft_atoi(const char *str);

#endif
