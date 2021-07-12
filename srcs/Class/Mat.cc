/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mat.cc                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 23:19:34 by gperez            #+#    #+#             */
/*   Updated: 2021/06/17 16:41:51 by maiwenn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mat.hpp"

Mat::Mat(Vec3 p, Vec3 r, Vec3 s)
{
	this->mat = Mat4();
	this->pos = p;
	this->rot = r;
	this->sca = s;
	this->vecUp = Vec3(0.0, 1.0, 0.0);
	this->vecFront = Vec3(0.0, 0, -1.0);
}

Mat4	Mat::getMatrix(bool calculate)
{
	if (calculate)
		this->calc();
	return (mat);
}

void	Mat::setMatrix(Mat4 m)
{
	this->mat = m;
}

Vec3	Mat::getFront(void)
{
	return (this->vecFront);
}

void	Mat::setFront(Vec3 front)
{
	this->vecFront = front;
}

Vec3	Mat::getPosition(void)
{
	return (this->pos);
}

void	Mat::setPosition(Vec3 p)
{
	this->pos = p;
}

Vec3	Mat::getScale(void)
{
	return (this->sca);
}

void	Mat::setScale(Vec3 s)
{
	this->sca = s;
}

void	Mat::reset(void)
{
	Mat		m;
	*this = m;
}

void	Mat::calc()
{
	this->setFront(
	Vec3(cos(radians(this->getEuler(YAW))) * cos(radians(this->getEuler(PITCH))),
		sin(radians(this->getEuler(PITCH))),
			sin(radians(this->getEuler(YAW))) * cos(radians(this->getEuler(PITCH)))).norm());
	this->lookAt(this->getPosition() - this->vecFront);
}

Vec3	Mat::getRotation(void)
{
	return (this->rot);
}

void	Mat::setRotation(Vec3 r)
{
	this->rot = r;
}

float	Mat::getEuler(e_rot euler)
{
	if (euler == PITCH)
		return (this->rot.getX());
	else if (euler == YAW)
		return (this->rot.getY());
	else
		return (this->rot.getZ());
}

void	Mat::lookAt(Vec3 look)
{
	Vec3	camera_forward = (this->getPosition() - look).norm();
	Vec3	camera_right = this->vecUp.cross(camera_forward).norm();
	Vec3	camera_up = camera_forward.cross(camera_right);
	Mat4	m;

	m[0][0] = camera_right.getX();
	m[1][0] = camera_right.getY();
	m[2][0] = camera_right.getZ();

	m[0][1] = camera_up.getX();
	m[1][1] = camera_up.getY();
	m[2][1] = camera_up.getZ();
	
	m[0][2] = camera_forward.getX();
	m[1][2] = camera_forward.getY();
	m[2][2] = camera_forward.getZ();
	
	m[3][0] = -this->pos.dot(camera_right);
	m[3][1] = -this->pos.dot(camera_up);
	m[3][2] = -this->pos.dot(camera_forward);

	this->setMatrix(m);
}

void	Mat::lookAt(void)
{
	this->lookAt(this->vecFront);
}

void	Mat::translate(e_axes axe, float speed)
{
	if (axe == E_RIGHT)
		this->setPosition(this->getPosition() + (this->vecFront.cross(this->vecUp)).norm() * speed);
	else if (axe == E_UP)
		this->setPosition(this->getPosition() + this->vecUp * speed);
	else
		this->setPosition(this->getPosition() + this->vecFront * speed);
}

void	Mat::translate(Vec3 t)
{
	this->setPosition(this->getPosition() + t);
}

void	Mat::translate(float x, float y, float z)
{
	this->translate(Vec3(x, y, z));
}

void	Mat::rotate(Vec3 rotEuler)
{
	this->rot = this->rot + rotEuler;
	if (this->rot.getX() > 89.9)
		this->setRotation(Vec3(89.9, this->rot.getY(), this->rot.getZ()));
	else if (this->rot.getX() < -89.9)
		this->setRotation(Vec3(-89.9, this->rot.getY(), this->rot.getZ()));
}

void	Mat::scale(Vec3 s)
{
	(void)s;
}

void	Mat::printMatrix(Mat4 mat)
{
	std::cout << "\n";
	for (size_t column = 0; column < 4; column++)
	{
		std::cout << "[";
		for (size_t raw = 0; raw < 4; raw++)
		{
			std::cout << mat[column][raw];
			if (raw != 3)
				std::cout << ", ";
		}
		std::cout << "]\n";
	}
	std::cout << "\n";
}

void	Mat::printMatrix(bool calculate)
{
	if (calculate)
		this->calc();
	this->printMatrix(this->mat);
}

Mat::~Mat()
{
}