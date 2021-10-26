/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RenderBufferMesh.cc                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:11:30 by gperez            #+#    #+#             */
/*   Updated: 2021/10/26 17:49:42 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RenderBufferMesh.hpp"

RenderBufferMesh::RenderBufferMesh()
{
	Mesh();
	this->type = E_RENDERBUFFER;
	// this->mat.rotate(Vec3(90., 0., 0.));
	// this->bufferA.rotate(Vec3(90., 0., 0.));
	this->bufferA.translate(Vec3(0.,0.,18));
}

bool	RenderBufferMesh::loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment)
{
	if (Mesh::loadMesh(pathMesh, pathVertex, pathFragment))
		return (true);
	if (this->bufferA.loadMesh(g_objPath[E_PBALL], PATH_RENDERBUFFER_VERTEX_BUFFER_A, PATH_RENDERBUFFER_BUFFER_A))
		return (true);

	// this->bufferA.translate(Vec3(0., 10., 50.));

	glGenFramebuffers(1, &this->frameBufferInput);
	glBindFramebuffer(GL_FRAMEBUFFER, this->frameBufferInput);

	int	msaa = 4;
	glGenRenderbuffers(1, &this->renderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, this->renderBuffer);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, msaa, GL_RGB8, WIDTH, HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, this->renderBuffer);

	GLenum i;
	if ((i = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Error load renderBuffer: " << i << "\n";
 		return true;
	}

	glGenFramebuffers(1, &this->frameBufferOutPut);
	glBindFramebuffer(GL_FRAMEBUFFER, this->frameBufferOutPut);

	glGenTextures(1, &this->frameBufferTexture);
	glBindTexture(GL_TEXTURE_2D, this->frameBufferTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, this->frameBufferTexture, 0);

	if ((i = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Error load renderBuffer: " << i << "\n";
 		return true;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return (false);
}

void	RenderBufferMesh::render(Camera &cam, float timeS, Vec3 &lightPos, Vec2 resolution)
{
	(void)lightPos;
	
	if (this->distance(cam.getPosition()) > RENDER_DIST_SHADER - PREC)
		return;
	for (unsigned int i = 0 ; i < this->m_Entries.size() ; i++)
	{
		for (unsigned int iBuffer = 0; iBuffer < this->bufferA.getEntriesSize(); iBuffer++)
		{
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->frameBufferInput);
			glClearColor(0., 0., 0., 1.);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glUseProgram(this->bufferA.getShaderProgram());
			glBindVertexArray(this->bufferA.getVao(iBuffer));
			glUniform1fv(glGetUniformLocation(this->bufferA.getShaderProgram(),
				"time"), 1, (const GLfloat*)&timeS);
			glUniform2fv(glGetUniformLocation(this->bufferA.getShaderProgram(),
				"u_resolution"), 1, (const GLfloat*)&resolution);
			glUniformMatrix4fv(glGetUniformLocation(this->bufferA.getShaderProgram(),
				"model"), 1, GL_FALSE, &(this->bufferA.getMat().getMatrix(false)[0][0]));
			glUniformMatrix4fv(glGetUniformLocation(this->bufferA.getShaderProgram(),
				"view"), 1, GL_FALSE, &(cam.getMatrix(false).inverse()[0][0]));
			glUniformMatrix4fv(glGetUniformLocation(this->bufferA.getShaderProgram(),
				"projection"), 1, GL_FALSE, &(cam.getProjMatrix()[0][0]));
			glDrawElements(GL_TRIANGLES, this->bufferA.getNumIndices(iBuffer), GL_UNSIGNED_INT, NULL);
		}

		glBindFramebuffer(GL_READ_FRAMEBUFFER, this->frameBufferInput); // src FBO (multi-sample)
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->frameBufferOutPut);     // dst FBO (single-sample)
		glBlitFramebuffer(0, 0, WIDTH, HEIGHT,             // src rect
						0, 0, WIDTH, HEIGHT,             // dst rect
						GL_COLOR_BUFFER_BIT,             // buffer mask
						GL_LINEAR); 

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
		glBindFramebuffer(GL_FRAMEBUFFER, 0.);
	}
}

RenderBufferMesh::~RenderBufferMesh()
{
	glDeleteTextures(1, &this->frameBufferTexture);
	glDeleteRenderbuffers(1, &this->renderBuffer);
	glDeleteFramebuffers(1, &this->frameBufferInput);
	glDeleteFramebuffers(1, &this->frameBufferOutPut);
}