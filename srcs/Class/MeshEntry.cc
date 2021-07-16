/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MeshEntry.cc                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:23:21 by gperez            #+#    #+#             */
/*   Updated: 2021/07/15 17:00:10 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MeshEntry.hpp"

MeshEntry::MeshEntry()
{
	this->vbo = 0;
	this->ebo = 0;
	this->vao = 0;
}

bool			MeshEntry::init(std::vector<t_vertex>& vertices, std::vector<unsigned int>& indices)
{
	this->numIndices = indices.size();
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_vertex) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);

	glGenBuffers(1, &this->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(t_vertex), (void*)sizeof(Vec3));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex), (void*)(sizeof(Vec3) + sizeof(Vec2)));
	
	glBindVertexArray(0);
	return (0);
}

void			MeshEntry::setMatIdx(unsigned int matIdx)
{
	this->materialIndex = matIdx;
}

void			MeshEntry::setNumIndices(unsigned int numInd)
{
	this->numIndices = numInd;
}

GLuint			MeshEntry::getVao(void)
{
	return (this->vao);
}

GLuint			MeshEntry::getVbo(void)
{
	return (this->vbo);
}

GLuint			MeshEntry::getEbo(void)
{
	return (this->ebo);
}

unsigned int	MeshEntry::getNumIndices(void)
{
	return (this->numIndices);
}

unsigned int	MeshEntry::getMatIdx(void)
{
	return (this->materialIndex);
}

MeshEntry::~MeshEntry()
{
	if (this->vbo)
		glDeleteBuffers(1, &this->vbo);
	if (this->ebo)
		glDeleteBuffers(1, &this->ebo);
	if (this->vbo)
		glDeleteVertexArrays(1, &this->vao);
}