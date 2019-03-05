/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krutten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 02:17:53 by krutten           #+#    #+#             */
/*   Updated: 2019/01/26 21:19:31 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector	vector_matrix_multiply(t_vector one, t_mat matrix)
{
	t_vector	output;

	output.x = matrix.m[0][0] * one.x + matrix.m[0][1] * one.y +
	matrix.m[0][2] * one.z;
	output.y = matrix.m[1][0] * one.x + matrix.m[1][1] * one.y +
	matrix.m[1][2] * one.z;
	output.z = matrix.m[2][0] * one.x + matrix.m[2][1] * one.y +
	matrix.m[2][2] * one.z;
	return (output);
}

t_mat		matrix_matrix_multiply(t_mat a, t_mat b)
{
	t_mat	output;

	output.m[0][0] = a.m[0][0] * b.m[0][0] + a.m[0][1] *
	b.m[1][0] + a.m[0][2] * b.m[2][0];
	output.m[0][1] = a.m[0][0] * b.m[0][1] + a.m[0][1] *
	b.m[1][1] + a.m[0][2] * b.m[2][1];
	output.m[0][2] = a.m[0][0] * b.m[0][2] + a.m[0][1] *
	b.m[1][2] + a.m[0][2] * b.m[2][2];
	output.m[1][0] = a.m[1][0] * b.m[0][0] + a.m[1][1] *
	b.m[1][0] + a.m[1][2] * b.m[2][0];
	output.m[1][1] = a.m[1][0] * b.m[0][1] + a.m[1][1] *
	b.m[1][1] + a.m[1][2] * b.m[2][1];
	output.m[1][2] = a.m[1][0] * b.m[0][2] + a.m[1][1] *
	b.m[1][2] + a.m[1][2] * b.m[2][2];
	output.m[2][0] = a.m[2][0] * b.m[0][0] + a.m[2][1] *
	b.m[1][0] + a.m[2][2] * b.m[2][0];
	output.m[2][1] = a.m[2][0] * b.m[0][1] + a.m[2][1] *
	b.m[1][1] + a.m[2][2] * b.m[2][1];
	output.m[2][2] = a.m[2][0] * b.m[0][2] + a.m[2][1] *
	b.m[1][2] + a.m[2][2] * b.m[2][2];
	return (output);
}

t_mat		rotation_matrix_x(float angle)
{
	t_mat	output;

	output.m[0][0] = 1;
	output.m[0][1] = 0;
	output.m[0][2] = 0;
	output.m[1][0] = 0;
	output.m[1][1] = cos(PI * angle / 180);
	output.m[1][2] = -sin(PI * angle / 180);
	output.m[2][0] = 0;
	output.m[2][1] = sin(PI * angle / 180);
	output.m[2][2] = cos(PI * angle / 180);
	return (output);
}

t_mat		rotation_matrix_y(float angle)
{
	t_mat	output;

	output.m[0][0] = cos(PI * angle / 180);
	output.m[0][1] = 0;
	output.m[0][2] = sin(PI * angle / 180);
	output.m[1][0] = 0;
	output.m[1][1] = 1;
	output.m[1][2] = 0;
	output.m[2][0] = -sin(PI * angle / 180);
	output.m[2][1] = 0;
	output.m[2][2] = cos(PI * angle / 180);
	return (output);
}

t_mat		rotation_matrix_z(float angle)
{
	t_mat	output;

	output.m[0][0] = cos(PI * angle / 180);
	output.m[0][1] = -sin(PI * angle / 180);
	output.m[0][2] = 0;
	output.m[1][0] = sin(PI * angle / 180);
	output.m[1][1] = cos(PI * angle / 180);
	output.m[1][2] = 0;
	output.m[2][0] = 0;
	output.m[2][1] = 0;
	output.m[2][2] = 1;
	return (output);
}
