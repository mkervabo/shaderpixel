/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:51:32 by gperez            #+#    #+#             */
/*   Updated: 2021/06/17 16:54:54 by maiwenn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vec3.hpp"

void	Vec3::setX(float x)
{
	this->x = x;
}

void Vec3::setY(float y)
{
	this->y = y;
}

void	Vec3::setZ(float z)
{ 
	this->z = z;
}

void	Vec3::setVec3(Vec3 v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

void	Vec3::setVec3(float x, float y, float z)
{ 
	this->x = x;
	this->y = y;
	this->z = z;
}

float   Vec3::getX() const
{ 
	return x;
}

float   Vec3::getY() const
{
	return y;
}
float   Vec3::getZ() const
{
	return z;
}

float   Vec3::getVec3Axis(e_axis axis)
{
	if (axis == E_X)
		return(this->z);
	else if (axis == E_Y)
		return(this->y);
	else
		return(this->z);
}

float   Vec3::lenght()
{
	return(sqrt(this->x * this->x + this->y * this->y + this->z * this->z));
};

float   Vec3::dot(Vec3 b)
{
	return(this->x * b.getX() + this->y * b.getY() + this->z * b.getZ()); 
};

Vec3	Vec3::cross(Vec3 b)
{
	return Vec3(
		this->y * b.getZ() - b.getY() * this->z,
		this->z * b.getX() - b.getZ() * this->x,
		this->x * b.getY() - b.getX() * this->y
	);
};

float	radians(float angle)
{
	return (angle * M_PI / 180.0);
}

Vec3	Vec3::toRadians(void) const
{
	return (Vec3(radians(this->x), radians(this->y), radians(this->z)));
}

Vec3	Vec3::operator+(Vec3 b) const
{
	return(Vec3(
		this->x + b.getX(),
		this->y + b.getY(),
		this->z + b.getZ()
	)); 
};

Vec3	Vec3::operator-(Vec3 b)
{
	return(Vec3(
		this->x - b.getX(),
		this->y - b.getY(),
		this->z - b.getZ()
	)); 
};

Vec3	Vec3::operator*(Vec3 b) const
{
	return(Vec3(
		this->x * b.getX(),
		this->y * b.getY(),
		this->z * b.getZ()
	)); 
};

Vec3	Vec3::operator*(Mat4 b)
{
	Vec3 res;

	res.x = b[0][0] * this->x + b[0][1] * this->y + b[0][2] * this->z + b[0][3];
	res.y = b[1][0] * this->x + b[1][1] * this->y + b[1][2] * this->z + b[1][3];
	res.z = b[2][0] * this->x + b[2][1] * this->y + b[2][2] * this->z + b[2][3];
	return(res);
}

Vec3	Vec3::operator*(float v)
{
	return(Vec3(
		this->x * v,
		this->y * v,
		this->z * v
	));
};

Vec3	Vec3::operator/(float v)
{
	return(Vec3(
		this->x / v,
		this->y / v, 
		this->z / v
	));
};

Vec3	Vec3::norm()
{
	return(*this / this->lenght());
};

Vec3	Vec3::oppose()
{
	return(Vec3(
		-this->x,
		-this->y,
		-this->z
	));
}