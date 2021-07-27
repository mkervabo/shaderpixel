/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Material.cc                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 14:26:47 by gperez            #+#    #+#             */
/*   Updated: 2021/07/27 15:13:00 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Material.hpp"

Material::Material()
{
	this->text = NULL;
	this->colorD = Vec3(0., 1., 1.);
	this->isText = true;
}

void	Material::setTexture(Texture *t)
{
	this->text = t;
}

Texture	*Material::getTexture(void)
{
	return (this->text);
}

void	Material::setIsText(bool isT)
{
	this->isText = isT;
}

bool	Material::getIsText(void)
{
	return (this->isText);
}

void	Material::setColor(Vec3 color)
{
	this->colorD = color;
}

Vec3	Material::getColor(void)
{
	return (this->colorD);
}

void	Material::newTexture(void)
{
	this->text = new Texture;
}

void	Material::deleteTexture(void)
{
	if (this->text)
		delete this->text;
	this->text = NULL;
}

void	Material::clearMaterial(void)
{
	this->deleteTexture();
	this->colorD = Vec3(1., 1., 1.);
	this->isText = true;
}

Material::~Material()
{
	this->clearMaterial();
}