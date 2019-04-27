/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:02:57 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/27 11:49:45 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "corewar.h"
#include "graph.h"

pthread_cond_t condition = PTHREAD_COND_INITIALIZER; /* Création de la condition */
pthread_cond_t condition2 = PTHREAD_COND_INITIALIZER; /* Création de la condition */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* Création du mutex */

void	*func_thread_game(void *arg)
{
	t_core *c;

	c = (t_core*)arg;
	the_game(c);
	pthread_exit(NULL);
}

void	*func_thread_ctrl(void *arg)
{
	t_core *c;

	c = (t_core*)arg;
	while (1)
	{
		if (controls(c))
			pthread_exit(NULL);
	}
	pthread_exit(NULL);
}

int		init_thread(t_core *c)
{
	pthread_t thread_ctrl;
	pthread_t thread_game;

	if (pthread_create(&thread_ctrl, NULL, func_thread_ctrl, c))
		return (badthread);
	if (pthread_create(&thread_game, NULL, func_thread_game, c))
		return (badthread);
	if (pthread_join(thread_ctrl, NULL))
		return (badthread);
	return (0);
}
