/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RenderBufferMesh.cc                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:11:30 by gperez            #+#    #+#             */
/*   Updated: 2021/10/28 15:13:08 by maiwenn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RenderBufferMesh.hpp"

RenderBufferMesh::RenderBufferMesh()
{
	Mesh();
	this->type = E_RENDERBUFFER;
	this->mat.translate(Vec3(8.8, 2, 0.));
	this->bufferA.translate(Vec3(-0.5,-0.5, -10.));
}

bool	RenderBufferMesh::loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment)
{
	if (Mesh::loadMesh(pathMesh, pathVertex, pathFragment))
		return (true);
	if (this->bufferA.loadMesh(g_objPath[E_PBALL], PATH_RENDERBUFFER_VERTEX_BUFFER_A, FRAGMENT))
		return (true);

	glGenFramebuffers(1, &this->frameBufferInput);
	glBindFramebuffer(GL_FRAMEBUFFER, this->frameBufferInput);

	int	msaa = 1;
	glGenRenderbuffers(1, &this->renderBufferInput);
	glBindRenderbuffer(GL_RENDERBUFFER, this->renderBufferInput);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, msaa, GL_RGB, WIDTH, HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, this->renderBufferInput);

	GLenum i;
	if ((i = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Error load renderBuffer: " << i << "\n";
 		return true;
	}

	glGenFramebuffers(1, &this->frameBufferOutput);
	glBindFramebuffer(GL_FRAMEBUFFER, this->frameBufferOutput);

	glGenTextures(1, &this->bufferTexture);
	glBindTexture(GL_TEXTURE_2D, this->bufferTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, this->bufferTexture, 0);

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
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->frameBufferInput);
		glClearColor(0., 0., 0., 1.);
		glClear(GL_COLOR_BUFFER_BIT);
		this->bufferA.render(cam, timeS, lights, resolution);
		// for (unsigned int iBuffer = 0; iBuffer < this->bufferA.getEntriesSize(); iBuffer++)
		// {
		// 	glUseProgram(this->bufferA.getShaderProgram());
		// 	glBindVertexArray(this->bufferA.getVao(iBuffer));
		// 	glUniform1fv(glGetUniformLocation(this->bufferA.getShaderProgram(),
		// 		"time"), 1, (const GLfloat*)&timeS);
		// 	glUniform2fv(glGetUniformLocation(this->bufferA.getShaderProgram(),
		// 		"u_resolution"), 1, (const GLfloat*)&resolution);
		// 	glUniformMatrix4fv(glGetUniformLocation(this->bufferA.getShaderProgram(),
		// 		"model"), 1, GL_FALSE, &(this->bufferA.getMat().getMatrix(false)[0][0]));
		// 	glUniformMatrix4fv(glGetUniformLocation(this->bufferA.getShaderProgram(),
		// 		"view"), 1, GL_FALSE, &(cam.getMatrix(false).inverse()[0][0]));
		// 	glUniformMatrix4fv(glGetUniformLocation(this->bufferA.getShaderProgram(),
		// 		"projection"), 1, GL_FALSE, &(cam.getProjMatrix()[0][0]));
		// 	glDrawElements(GL_TRIANGLES, this->bufferA.getNumIndices(iBuffer), GL_UNSIGNED_INT, NULL);
		// }

		glBindFramebuffer(GL_READ_FRAMEBUFFER, this->frameBufferInput); // src FBO (multi-sample)
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->frameBufferOutput);     // dst FBO (single-sample)
		glBlitFramebuffer(0, 0, WIDTH, HEIGHT,             // src rect
						0, 0, WIDTH, HEIGHT,             // dst rect
						GL_COLOR_BUFFER_BIT,             // buffer mask
						GL_LINEAR); 

		glBindFramebuffer(GL_FRAMEBUFFER, 0.);
 		glUseProgram(this->shader.getProgram());
		glBindVertexArray(this->m_Entries[i].getVao());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->bufferTexture);

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
	}
}

RenderBufferMesh::~RenderBufferMesh()
{
	glDeleteTextures(1, &this->bufferTexture);
	glDeleteRenderbuffers(1, &this->renderBufferInput);
	glDeleteFramebuffers(1, &this->frameBufferInput);
	glDeleteFramebuffers(1, &this->frameBufferOutput);
}