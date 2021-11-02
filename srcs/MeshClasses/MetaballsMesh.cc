/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MetaballsMesh.cc                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:13:55 by gperez            #+#    #+#             */
/*   Updated: 2021/11/02 11:06:28 by maiwenn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MetaballsMesh.hpp"
#include "Receiver.hpp"

MetaballsMesh::MetaballsMesh()
{
	Mesh();
	this->type = E_METABALLS;
	// irrklang:
	// start the sound engine with default parameters
	this->engine = createIrrKlangDevice();
	if (!this->engine)
		return ; // error starting up the engine
	// play some sound stream, looped
	this->vol = this->engine->play2D("libs/irrklang/media/getout.ogg", true, false, true);
	this->vol->setVolume((ik_f32)(0));
	this->engine->setMixedDataOutputReceiver(&this->receiver);
	this->translate(Vec3(0., 2., -20.));
}

bool	MetaballsMesh::loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment)
{
	if (Mesh::loadMesh(pathMesh, pathVertex, pathFragment))
		return (true);
	
	glGenTextures(1, &this->songText);
	glBindTexture(GL_TEXTURE_1D, this->songText);
	return (false);
}

	void	MetaballsMesh::render(Camera &cam, float timeS, std::vector<Mesh*> &lights, Vec2 resolution)
{
	Vec3	camPos;
	Vec3	modelPos;
	float	farNear[2] = {FAR_Z, NEAR_Z};
	float	fov = FOV;
	Vec3	lightPos = lights[this->type]->getPosition();

	if (this->distance(cam.getPosition()) > 10 - PREC)
		this->vol->setVolume((ik_f32)0.);
	else
		this->vol->setVolume((ik_f32)((10 - this->distance(cam.getPosition()))) / 20);
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

		camPos = cam.getPosition();
		modelPos = mat.getPosition();
		glUniformMatrix4fv(glGetUniformLocation(this->shader.getProgram(),
			"model"), 1, GL_FALSE, &(mat.getMatrix(false).inverse()[0][0]));
		glUniformMatrix4fv(glGetUniformLocation(this->shader.getProgram(),
			"view"), 1, GL_FALSE, &(cam.getMatrix(false)[0][0]));
		glUniformMatrix4fv(glGetUniformLocation(this->shader.getProgram(),
			"projection"), 1, GL_FALSE, &(cam.getProjMatrix()[0][0]));
		glUniformMatrix4fv(glGetUniformLocation(this->shader.getProgram(),
			"inverseView"), 1, GL_FALSE, &(cam.getInverseMat()[0][0]));
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
		glUniform3fv(glGetUniformLocation(this->shader.getProgram(),
			"modelPos"), 1, (const GLfloat*)&modelPos);
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