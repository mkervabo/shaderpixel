/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 23:48:55 by gperez            #+#    #+#             */
/*   Updated: 2021/10/18 11:03:14 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"

Camera::Camera(Vec3 p, Vec3 r, Mat4 proj)
{
	Mat(p, r);
	this->projection = proj;
}

void	Camera::resetCam(float dist)
{
	Camera	cam(Vec3(0.0, 0.0, dist), Vec3(), this->projection);
	*this = cam;
}

Mat4	Camera::getProjMatrix(void)
{
	return (this->projection);
}

void	Camera::setProjMatrix(Mat4 mat)
{
	this->projection = mat;
}

Vec3	Camera::createRay(Vec2 pos, float width, float height)
{
	pos.setX(pos.getX() / (width * 0.5) - 1.0f);
	pos.setY(2 - (pos.getY() / (height * 0.5)) - 1.0f);
	Vec3 screenPos = Vec3(pos.getX(), pos.getY(), 1.0);
	(void)screenPos;
	this->calc();
	Mat4 invVP = (this->getProjMatrix() * this->getMatrix()).inverse();
	
	return ((screenPos * invVP).norm());
}

void	Camera::rotate(Vec3 rotEuler)
{
	this->rot = this->rot + rotEuler;
	if (this->rot.getX() > 89.9)
		this->setRotation(Vec3(89.9, this->rot.getY(), this->rot.getZ()));
	else if (this->rot.getX() < -89.9)
		this->setRotation(Vec3(-89.9, this->rot.getY(), this->rot.getZ()));
	this->calc();
}

Camera::~Camera()
{
}