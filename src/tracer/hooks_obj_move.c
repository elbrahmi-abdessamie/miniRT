/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_obj_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:09:48 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/24 16:52:29 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minirt.h"
#include "library.h"
#include "vector.h"

void	cam_x(int key, t_data *data)
{
	data->camera.normalized.v_x += (key == 124) * 0.5 - (key == 123) * 0.5;
	normalize(&data->camera.normalized);
	lookat(&(data->camera));
	draw(*data, data->m_rt);
}

void	cam_y(int key, t_data *data)
{
	data->camera.normalized.v_y += (key == 126) * 0.4 - (key == 125) * 0.4;
	normalize(&data->camera.normalized);
	lookat(&(data->camera));
	draw(*data, data->m_rt);
}

static void	cylinders_rotate(t_cylender *c, int key)
{
	if (key == 38)
		c->normalized.v_x += 0.5;
	else if (key == 37)
		c->normalized.v_x -= 0.5;
	else if (key == 34)
		c->normalized.v_z += 0.5;
	else if (key == 40)
		c->normalized.v_z -= 0.5;
	normalize(&c->normalized);
	calculate_disk_plan(c, c->p_face, true);
	calculate_disk_plan(c, c->p_face->next, false);
}

static void	plane_rotate(t_plane *p, int key)
{
	if (key == 38)
		p->normalized.v_x += 0.1;
	else if (key == 37)
		p->normalized.v_x -= 0.1;
	else if (key == 34)
		p->normalized.v_y += 0.1;
	else if (key == 40)
		p->normalized.v_y -= 0.1;
	normalize(&p->normalized);
}

void	rotate(int key, t_data *data)
{
	t_objects	*obj;

	obj = data->objects;
	while (obj)
	{
		if (data->shape == CYLENDER && obj->type == CYLENDER)
			cylinders_rotate(obj->object, key);
		else if (data->shape == PLANE && obj->type == PLANE)
			plane_rotate(obj->object, key);
		obj = obj->next;
	}
	lookat(&(data->camera));
	draw(*data, data->m_rt);
}
