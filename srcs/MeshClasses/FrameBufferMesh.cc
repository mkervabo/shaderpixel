#include "FrameBufferMesh.hpp"

FrameBufferMesh::FrameBufferMesh()
{
	Mesh();
	this->type = E_FRAMEBUFFER;
}

bool	FrameBufferMesh::loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment)
{
	if (Mesh::loadMesh(pathMesh, pathVertex, pathFragment))
		return (true);
	if (this->bufferA.loadMesh(g_objPath[E_PPLANE], PATH_FRAMEBUFFER_VERTEX_BUFFER_A, PATH_FRAMEBUFFER_BUFFER_A))
		return (true);

	this->texture.newTexture();
	if (this->texture.load(GL_TEXTURE_2D, (char*)PATH_FRAMEBUFFER_TEXTURE))
		return (true);

	glGenFramebuffers(1, &this->frame);
	glBindFramebuffer(GL_FRAMEBUFFER, this->frame);
	
	glGenTextures(1, &this->frameTexture);
	glBindTexture(GL_TEXTURE_2D, this->frameTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenRenderbuffers(1, &this->renderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, this->renderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB, WIDTH, HEIGHT);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, this->frameTexture, 0);
	// glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_RENDERBUFFER, this->renderBuffer);

	GLenum i;
	if((i = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Error load renderBuffer: " << i << "\n";
 		return true;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return (false);
}

void	FrameBufferMesh::render(Camera &cam, float timeS, Vec3 &lightPos, Vec2 resolution)
{
	(void)lightPos;
	
	if (this->distance(cam.getPosition()) > RENDER_DIST_SHADER - PREC)
		return;
	for (unsigned int i = 0 ; i < this->m_Entries.size() ; i++)
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->frame);
		glClearColor(1, 0, 0, 0.5);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(this->bufferA.getShaderProgram());
		glBindVertexArray(this->m_Entries[i].getVao());
		glUniform1fv(glGetUniformLocation(this->bufferA.getShaderProgram(),
			"time"), 1, (const GLfloat*)&timeS);
		glUniform2fv(glGetUniformLocation(this->bufferA.getShaderProgram(),
			"u_resolution"), 1, (const GLfloat*)&resolution);
		glUniformMatrix4fv(glGetUniformLocation(this->bufferA.getShaderProgram(),
			"model"), 1, GL_FALSE, &(mat.getMatrix(false).inverse()[0][0]));
		glUniformMatrix4fv(glGetUniformLocation(this->bufferA.getShaderProgram(),
			"view"), 1, GL_FALSE, &(cam.getMatrix(false)[0][0]));
		glUniformMatrix4fv(glGetUniformLocation(this->bufferA.getShaderProgram(),
			"projection"), 1, GL_FALSE, &(cam.getProjMatrix()[0][0]));
		glDrawElements(GL_TRIANGLES, this->m_Entries[i].getNumIndices(), GL_UNSIGNED_INT, NULL);
		
		
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBindVertexArray(this->m_Entries[i].getVao());
 		glUseProgram(this->shader.getProgram());

		glUniform1i(glGetUniformLocation(this->shader.getProgram(), "bufferA"), 0);
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, this->frameTexture);
		
		glUniform1i(glGetUniformLocation(this->shader.getProgram(), "img"), 1);
		this->texture.bind(GL_TEXTURE0 + 1);

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

FrameBufferMesh::~FrameBufferMesh()
{
	glDeleteTextures(1, &this->frameTexture);
	glDeleteRenderbuffers(1, &this->renderBuffer);
	glDeleteFramebuffers(1, &this->frame);
}