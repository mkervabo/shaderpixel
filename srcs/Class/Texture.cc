/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.cc                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:54:04 by gperez            #+#    #+#             */
/*   Updated: 2021/10/06 13:24:27 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture()
{
	this->width = 0;
	this->height = 0;
	this->nrChannels = 0;
	this->txt = 0;
	this->txtData = 0;
	this->txtData = NULL;
}

bool			Texture::load(GLenum target, char *txtPath)
{
	this->txtTarget = target;
	stbi_set_flip_vertically_on_load(true);
	this->txtData = stbi_load(txtPath, &width, &height, &nrChannels, 0);
	if (!txtData)
		return (1);
	glGenTextures(1, &this->txt);
	glBindTexture(target, this->txt);
	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

	if (this->nrChannels == 3)
		glTexImage2D(target, 0, GL_RGB, this->width, this->height, 0,
			GL_RGB, GL_UNSIGNED_BYTE, this->txtData);
	else
		glTexImage2D(target, 0, GL_RGBA, this->width, this->height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, this->txtData);
	glGenerateMipmap(target);
	stbi_image_free(this->txtData);
	return (0);
}

void			Texture::bind(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(this->txtTarget, this->txt);
}

int				Texture::getWidth(void)
{
	return (this->width);
}

int				Texture::getHeight(void)
{
	return (this->height);
}

unsigned int	Texture::getTxt(void)
{
	return (this->txt);
}

unsigned char	*Texture::getTxtData(void)
{
	return (this->txtData);
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->txt);
}