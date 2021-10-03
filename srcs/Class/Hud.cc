/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hud.cc                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 20:12:28 by gperez            #+#    #+#             */
/*   Updated: 2021/10/03 21:31:17 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Hud.hpp"

Hud::Hud()
{
	this->isInit = false;
	this->cursorColor = WHITE_CURSOR;
}

void		Hud::setCursorColor(char color)
{
	this->cursorColor = color;
}

char		Hud::getCursorColor(void)
{
	return (this->cursorColor);
}

int			Hud::init(void)
{
	if (isInit)
		return (0);
	this->texture.newTexture();
	this->texture.getTexture()->load(GL_TEXTURE_2D, (char*)HUD_TEXTURE_PATH);
	if (this->shader.loadShader((char*)VERTEX_HUD, (char*)FRAGMENT_HUD))
		return (1);
	this->isInit = true;
	newElement();
	this->hudElements[0]->setOffsetTxt(11);
	this->hudElements[0]->setScale((Vec3){0.02, 0.05, 0.0});
	return (0);
}

void		Hud::fillElements(std::vector<char> unitsValue, unsigned int units)
{
	unsigned int iValue = 0;

	for (unsigned int i = 1; i < units + 1 && iValue < unitsValue.size(); i++)
		this->hudElements[i]->setOffsetTxt(unitsValue[iValue++]);
}

void		Hud::syncFpsToElements(int fps)
{
	unsigned int		units;
	std::vector<char>	unitsValue;

	for (units = 0; fps > 0; units++)
	{
		unitsValue.push_back(fps % 10);
		fps /= 10;
	}
	while (hudElements.size() < units + 1)
		newElement();
	while (hudElements.size() > units + 1)
		deleteElement(hudElements.size() - 1);
	fillElements(unitsValue, units);
}

void		Hud::newElement(void)
{
	HudElement			*element;
	unsigned int	vbo;
	unsigned int	vao;

	element = new HudElement;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * SQUARE_PTS * 2, &square_pt, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glEnableVertexAttribArray(0);
	element->setVbo(vbo);
	element->setVao(vao);
	element->setScale(Vec3(0.02, 0.05, 0.0));
	element->translate(Vec3(1 - (element->getScale().getX() + 0.01)
		- (element->getScale().getX() + 0.05) * ((float)this->hudElements.size() - 1),
		1 - (element->getScale().getY() + 0.01), 0.0));
	this->hudElements.push_back(element);
	glBindVertexArray(0);
}

void		Hud::display(int fps)
{
	unsigned int txt = this->texture.getTexture()->getTxt();
	syncFpsToElements(fps);
	glDepthMask(false);
	for (unsigned int i = 0; i < this->hudElements.size(); i++)
	{
		glUseProgram(this->shader.getProgram());
		glBindVertexArray(this->hudElements[i]->getVao());
		glUniformMatrix4fv(glGetUniformLocation(this->shader.getProgram(),
			"view"), 1, GL_FALSE, &(this->hudElements[i]->getMatrix(false)[0][0]));
		glUniform1i(glGetUniformLocation(this->shader.getProgram(),
			"number"), this->hudElements[i]->getOffsetTxt());
		glUniform1i(glGetUniformLocation(this->shader.getProgram(),
			"cursorColor"), this->cursorColor);
		glUniform1i(glGetUniformLocation(this->shader.getProgram(),
			"basicTexture"), txt);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, SQUARE_PTS);
		glBindVertexArray(0);
	}
	glDepthMask(true);
}

void		Hud::deleteElement(unsigned int i)
{
	if (i >= this->hudElements.size())
		return ;
	delete this->hudElements[i];
	this->hudElements.erase(this->hudElements.begin() + i);
}

Hud::~Hud()
{
	for (int i = this->hudElements.size() - 1; i >= 0; i--)
		this->deleteElement(i);
	if (this->shader.getProgram())
		this->shader.freeProgram();
}