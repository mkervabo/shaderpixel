#include "RenderBufferMesh.hpp"

RenderBufferMesh::RenderBufferMesh()
{
	Mesh();
	this->type = E_RENDER_BUFFER;
}

GLuint quad_VertexArrayID;

bool	RenderBufferMesh::loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment)
{
	if (Mesh::loadMesh(pathMesh, pathVertex, pathFragment))
		return (true);
	this->bufferA.loadMesh(g_objPath[E_PPLANE], PATH_RENDER_BUFFER_VERTEX_BUFFER_A, PATH_RENDER_BUFFER_BUFFER_A);

	this->texture.newTexture();
	if (this->texture.load(GL_TEXTURE_2D, (char*)PATH_RENDER_BUFFER_TEXTURE))
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

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
 		return true;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return (false);
}

void	RenderBufferMesh::render(Camera &cam, float timeS, Vec3 &lightPos)
{
	Vec3	camPos;
	float	farNear[2] = {FAR_Z, NEAR_Z};
	float	fov = FOV;
	Vec2	resolution = Vec2(WIDTH, HEIGHT);
	for (unsigned int i = 0 ; i < this->m_Entries.size() ; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, this->frame);
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
			"inverseView"), 1, GL_FALSE, &(cam.getInverseMat()[0][0]));
		glUniformMatrix4fv(glGetUniformLocation(this->bufferA.getShaderProgram(), 
			"view"), 1, GL_FALSE, &(cam.getMatrix(false)[0][0]));
		glUniformMatrix4fv(glGetUniformLocation(this->bufferA.getShaderProgram(),
			"projection"), 1, GL_FALSE, &(cam.getProjMatrix()[0][0]));
		glDrawElements(GL_TRIANGLES, this->m_Entries[i].getNumIndices(), GL_UNSIGNED_INT, NULL);
		
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
		glUniformMatrix4fv(glGetUniformLocation(this->shader.getProgram(),
			"inverseView"), 1, GL_FALSE, &(cam.getInverseMat()[0][0]));
		camPos = cam.getPosition();
		glUniform3fv(glGetUniformLocation(this->shader.getProgram(),
			"eye"), 1, (const GLfloat*)&camPos);
		glUniform1fv(glGetUniformLocation(this->shader.getProgram(),
			"time"), 1, (const GLfloat*)&timeS);
		glUniform1fv(glGetUniformLocation(this->shader.getProgram(),
			"farNear"), 2, (const GLfloat*)&farNear);
		glUniform1fv(glGetUniformLocation(this->shader.getProgram(),
			"u_fov"), 1, (const GLfloat*)&fov);
		glUniform2fv(glGetUniformLocation(this->shader.getProgram(),
			"u_resolution"), 1, (const GLfloat*)&resolution);
		glUniform3fv(glGetUniformLocation(this->shader.getProgram(),
			"u_lightPos"), 1, (const GLfloat*)&lightPos);
		glDrawElements(GL_TRIANGLES, this->m_Entries[i].getNumIndices(), GL_UNSIGNED_INT, NULL);
	}
}

RenderBufferMesh::~RenderBufferMesh()
{
	glDeleteTextures(1, &this->frameTexture);
	glDeleteRenderbuffers(1, &this->renderBuffer);
	glDeleteFramebuffers(1, &this->frame);
	
}