/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Material.cc                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 14:26:47 by gperez            #+#    #+#             */
/*   Updated: 2021/10/06 13:17:25 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Material.hpp"

Material::Material()
{
	this->text = NULL;
	this->colorD = Vec3(0., 1., 1.);
	this->isText = true;
}

bool	Material::asTexture(void)
{
	return (this->text ? true : false);
}

void	Material::setTexture(Texture *t)
{
	this->text = t;
}

bool	Material::load(GLenum target, char *txt)
{
	if (this->text)
		return (this->text->load(target, txt));
	return (true);
}

void	Material::bind(GLenum textureUnit)
{
	if (this->text)
		this->text->bind(textureUnit);
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