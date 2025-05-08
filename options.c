/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohidalg <rohidalg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:25:54 by rohidalg          #+#    #+#             */
/*   Updated: 2025/05/08 13:41:02 by rohidalg         ###   ########.fr       */
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
    //time_to_sleep
}

void eat(t_philo *philo)
{
    
}
