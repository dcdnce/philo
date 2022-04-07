/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 10:59:32 by pforesti          #+#    #+#             */
/*   Updated: 2022/04/06 10:51:57 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	display(t_sopher *v, char *act, long tv_n, bool died)
{
	if ((*v->philo_died) == 1)
		return (0);
	pthread_mutex_lock(v->mutex_display);
	printf("%lu %zu %s\n", tv_n - v->tv_b, v->n, act);
	if (died == true)
	{
		(*v->philo_died) = 1;
		return (0);
	}
	pthread_mutex_unlock(v->mutex_display);
	return (1);
}
