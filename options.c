/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:25:54 by rohidalg          #+#    #+#             */
/*   Updated: 2025/05/09 11:55:48 by rohidalg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_write(TAKE_FORKS, philo);
	pthread_mutex_lock(philo->left_fork);
	ft_write(TAKE_FORKS, philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	ft_write(SLEEPING, philo);
	ft_usleep(philo->data->time_to_sleep);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = ft_get_time() + philo->data->time_to_die;
	ft_write(EATING, philo);
	philo->meals_eaten++;
	ft_usleep(philo->data->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}

void	waiter(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
}

void	actions(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	philo->time_to_die = philo->data->time_to_die + ft_get_time();
}

int	i_dinner(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = ft_get_time();
	while (i < data->n_philos)
	{
		if (pthread_create(data->tid[i], 0, ))
		{
		}
		ft_usleep();
	}
}
