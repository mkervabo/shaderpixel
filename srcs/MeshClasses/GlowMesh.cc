#include "GlowMesh.hpp"

GlowMesh::GlowMesh()
{
	Mesh();
	this->type = E_GLOW;
}

void	GlowMesh::render(Camera &cam, float timeS, Vec3 &lightPos)
{
	Vec3	camPos;
	Vec2	resolution = Vec2(WIDTH, HEIGHT);
	lightPos = Vec3();
	timeS = 0;

	for (unsigned int i = 0 ; i < this->m_Entries.size() ; i++)
	{
		glBindVertexArray(this->m_Entries[i].getVao());
 		glUseProgram(this->shader.getProgram());

		glUniformMatrix4fv(glGetUniformLocation(this->shader.getProgram(),
			"model"), 1, GL_FALSE, &(mat.getMatrix(false).inverse()[0][0]));
		glUniformMatrix4fv(glGetUniformLocation(this->shader.getProgram(),
			"view"), 1, GL_FALSE, &(cam.getMatrix(false)[0][0]));
		glUniformMatrix4fv(glGetUniformLocation(this->shader.getProgram(),
			"projection"), 1, GL_FALSE, &(cam.getProjMatrix()[0][0]));
		camPos = cam.getPosition();
		glUniform3fv(glGetUniformLocation(this->shader.getProgram(),
			"eye"), 1, (const GLfloat*)&camPos);
		glUniform2fv(glGetUniformLocation(this->shader.getProgram(),
			"u_resolution"), 1, (const GLfloat*)&resolution);
		glDrawElements(GL_TRIANGLES, this->m_Entries[i].getNumIndices(), GL_UNSIGNED_INT, NULL);
	}
}

GlowMesh::~GlowMesh()
{
}