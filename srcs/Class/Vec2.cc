/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec2.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 09:08:17 by gperez            #+#    #+#             */
/*   Updated: 2021/06/17 09:08:18 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vec2.hpp"

void	Vec2::setX(float x)
{
	this->x = x;
}

void	Vec2::setY(float y)
{
	this->y = y;
}

void	Vec2::setVec2(float x, float y)
{
	this->x = x;
	this->y = y;
}

float   Vec2::getX() const
{
	return(this->x);
}

float   Vec2::getY() const
{
	return(this->y);
}

Vec2	Vec2::operator*(float v)
{
	return(Vec2(
		this->x * v,
		this->y * v
	));
}