	#include "MetaballsMesh.hpp"

	MetaballsMesh::MetaballsMesh()
	{
		Mesh();
		this->type = E_METABALLS;
		this->size = 1.0;
		this->velocity = 1.2;
		this->max_size = 0.5;
		this->min_size = 0.1;
		this->nb_balls = 9;
	}

	void	MetaballsMesh::setSize(float new_size)
	{
		this->size = new_size;
	}

	void	MetaballsMesh::setVelocity(float new_velocity)
	{
		this->velocity = new_velocity;
	}

	void	MetaballsMesh::setMaxSize(float new_max_size)
	{
		this->max_size = new_max_size;
	}

	void   MetaballsMesh::setMinize(float new_min_size)
	{
		this->min_size = new_min_size;
	}

	void	MetaballsMesh::setNbBalls(unsigned int new_nb_balls)
	{
		this->nb_balls = new_nb_balls;
	}

	void	MetaballsMesh::addSize(float new_size)
	{
		this->size += new_size;
	}

	void	MetaballsMesh::addVelocity(float new_velocity)
	{
		this->velocity += new_velocity;
	}

	void	MetaballsMesh::addMaxSize(float new_max_size)
	{
		this->max_size += new_max_size;
	}

	void   MetaballsMesh::addMinize(float new_min_size)
	{
		this->min_size += new_min_size;
	}

	void	MetaballsMesh::addNbBalls(int new_nb_balls)
	{
		this->nb_balls += new_nb_balls;
	}

	void	MetaballsMesh::render(Camera &cam, float timeS, Vec3 &lightPos)
{
	Vec3	camPos;
	float	farNear[2] = {FAR_Z, NEAR_Z};
	float	fov = FOV;
	Vec2	resolution = Vec2(WIDTH, HEIGHT);

	if (this->distance(cam.getPosition()) > RENDER_DIST_SHADER - PREC)
		return;
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

		//METABALLS SHADER
		//irrklang:
		// Receiver* receiver = NULL;
		// engine->setMixedDataOutputReceiver(receiver);
		float offset = this->size;
		glUniform1fv(glGetUniformLocation(this->shader.getProgram(),
			"metaSize"), 1, (const GLfloat*)&offset);
		offset = this->velocity;
		glUniform1fv(glGetUniformLocation(this->shader.getProgram(),
			"metaVelocity"), 1, (const GLfloat*)&offset);
		offset = this->max_size;
		glUniform1fv(glGetUniformLocation(this->shader.getProgram(),
			"metaMaxSize"), 1, (const GLfloat*)&offset);
		offset = this->min_size;
		glUniform1fv(glGetUniformLocation(this->shader.getProgram(),
			"metaMinSize"), 1, (const GLfloat*)&offset);
		unsigned int nbBalls = this->nb_balls;
		glUniform1i(glGetUniformLocation(this->shader.getProgram(),
			"metaNbBalls"), (GLuint)nbBalls);
		glDrawElements(GL_TRIANGLES, this->m_Entries[i].getNumIndices(), GL_UNSIGNED_INT, NULL);
	}
}

	MetaballsMesh::~MetaballsMesh()
	{
	}