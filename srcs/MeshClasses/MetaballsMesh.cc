	#include "MetaballsMesh.hpp"
	#include "Receiver.hpp"

MetaballsMesh::MetaballsMesh()
{
	Mesh();
	this->type = E_METABALLS;
	this->size = 0.2;
	this->velocity = 0.5;
	this->max_size = 0.3;
	this->min_size = 0.1;
	this->nb_balls = 5;
	// irrklang:
	// start the sound engine with default parameters
	this->engine = createIrrKlangDevice();
	if (!this->engine)
		return ; // error starting up the engine
	// play some sound stream, looped
	this->vol = this->engine->play2D("libs/irrklang/media/getout.ogg", true, false, true);
	this->engine->setMixedDataOutputReceiver(&this->receiver);
}

bool	MetaballsMesh::loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment)
{
	if (Mesh::loadMesh(pathMesh, pathVertex, pathFragment))
		return (true);
	
	glGenTextures(1, &this->songText);
	glBindTexture(GL_TEXTURE_1D, this->songText);
	return (false);
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

	void	MetaballsMesh::render(Camera &cam, float timeS, Vec3 &lightPos, Vec2 resolution)
{
	Vec3	camPos;
	float	farNear[2] = {FAR_Z, NEAR_Z};
	float	fov = FOV;

	// if (this->distance(cam.getPosition()) > RENDER_DIST_SHADER - PREC)
	// {
	// 	vol->setVolume((ik_f32)0.);
	// 	return;
	// }
	// vol->setVolume((ik_f32)((RENDER_DIST_SHADER - this->distance(cam.getPosition()))) / 10);
	vol->setVolume((ik_f32)(0));
	for (unsigned int i = 0 ; i < this->m_Entries.size() ; i++)
	{	
		glBindTexture(GL_TEXTURE_1D, this->songText);
		glTexImage1D(GL_TEXTURE_1D, 0, GL_RED, this->receiver.getSize(), 0, GL_RED, GL_FLOAT, this->receiver.getOut());
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		
		glBindVertexArray(this->m_Entries[i].getVao());
 		glUseProgram(this->shader.getProgram());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_1D, this->songText);

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
		Vec3 modelPos = mat.getPosition();
		glUniform3fv(glGetUniformLocation(this->shader.getProgram(),
			"modelPos"), 1, (const GLfloat*)&modelPos);

		// this->songData = this->receiver->getFrequency();
		// glActiveTexture(GL_TEXTURE0);
		// glBindTexture(GL_TEXTURE_2D, this->songText);

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
	if (this->vol)
	{
		this->vol->drop(); // don't forget to release the pointer once it is no longer needed by you
		this->vol = 0;
	}
	this->engine->drop();
}