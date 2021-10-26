/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RenderBufferMesh.cc                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:11:30 by gperez            #+#    #+#             */
/*   Updated: 2021/10/26 13:44:29 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RenderBufferMesh.hpp"

RenderBufferMesh::RenderBufferMesh()
{
	Mesh();
	this->type = E_RENDERBUFFER;
	this->mat.rotate(Vec3(90., 0., 0.));
}

bool	RenderBufferMesh::loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment)
{
	if (Mesh::loadMesh(pathMesh, pathVertex, pathFragment))
		return (true);
	if (this->bufferA.loadMesh(g_objPath[E_PDRAGON], PATH_RENDERBUFFER_VERTEX_BUFFER_A, PATH_RENDERBUFFER_BUFFER_A))
		return (true);

	// this->bufferA.translate(Vec3(0., 10., 50.));

	glGenFramebuffers(1, &this->frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, this->frameBuffer);
	
	glGenTextures(1, &this->frameBufferTexture);
	glBindTexture(GL_TEXTURE_2D, this->frameBufferTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenRenderbuffers(1, &this->renderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, this->renderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WIDTH, HEIGHT);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, this->frameBufferTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->renderBuffer);

	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, DrawBuffers);

	GLenum i;
	if ((i = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Error load renderBuffer: " << i << "\n";
 		return true;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return (false);
}

void	RenderBufferMesh::render(Camera &cam, float timeS, std::vector<Mesh*> &lights, Vec2 resolution)
{
	Vec3	lightPos = lights[this->type]->getPosition();

	for (unsigned int i = 0 ; i < this->m_Entries.size() ; i++)
	{
		for (unsigned int iBuffer = 0; iBuffer < this->bufferA.getEntriesSize(); iBuffer++)
		{
			// glEnable(GL_DEPTH_TEST);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->frameBuffer);
			glClearColor(0., 0., 0., 1.);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glUseProgram(this->bufferA.getShaderProgram());
			glBindVertexArray(this->bufferA.getVao(iBuffer));
			glUniform1fv(glGetUniformLocation(this->bufferA.getShaderProgram(),
				"time"), 1, (const GLfloat*)&timeS);
			glUniform2fv(glGetUniformLocation(this->bufferA.getShaderProgram(),
				"u_resolution"), 1, (const GLfloat*)&resolution);
			glUniformMatrix4fv(glGetUniformLocation(this->bufferA.getShaderProgram(),
				"model"), 1, GL_FALSE, &(mat.getMatrix(false)[0][0]));
			glUniformMatrix4fv(glGetUniformLocation(this->bufferA.getShaderProgram(),
				"view"), 1, GL_FALSE, &(cam.getMatrix(false).inverse()[0][0]));
			glUniformMatrix4fv(glGetUniformLocation(this->bufferA.getShaderProgram(),
				"projection"), 1, GL_FALSE, &(cam.getProjMatrix()[0][0]));
			glDrawElements(GL_TRIANGLES, this->bufferA.getNumIndices(iBuffer), GL_UNSIGNED_INT, NULL);
		}
		
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

		// glDisable(GL_DEPTH_TEST);
 		glUseProgram(this->shader.getProgram());
		glBindVertexArray(this->m_Entries[i].getVao());

		glBindTexture(GL_TEXTURE_2D, this->frameBufferTexture);

		glUniformMatrix4fv(glGetUniformLocation(this->shader.getProgram(),
			"model"), 1, GL_FALSE, &(mat.getMatrix(false).inverse()[0][0]));
		glUniformMatrix4fv(glGetUniformLocation(this->shader.getProgram(),
			"view"), 1, GL_FALSE, &(cam.getMatrix(false)[0][0]));
		glUniformMatrix4fv(glGetUniformLocation(this->shader.getProgram(),
			"projection"), 1, GL_FALSE, &(cam.getProjMatrix()[0][0]));
		glUniform1fv(glGetUniformLocation(this->shader.getProgram(),
			"time"), 1, (const GLfloat*)&timeS);
		glUniform2fv(glGetUniformLocation(this->shader.getProgram(),
			"u_resolution"), 1, (const GLfloat*)&resolution);
		glUniform3fv(glGetUniformLocation(this->shader.getProgram(),
			"u_lightPos"), 1, (const GLfloat*)&lightPos);
		glDrawElements(GL_TRIANGLES, this->m_Entries[i].getNumIndices(), GL_UNSIGNED_INT, NULL);
		// glEnable(GL_DEPTH_TEST);
	}
}

RenderBufferMesh::~RenderBufferMesh()
{
	glDeleteTextures(1, &this->frameBufferTexture);
	glDeleteRenderbuffers(1, &this->renderBuffer);
	glDeleteFramebuffers(1, &this->frameBuffer);
}