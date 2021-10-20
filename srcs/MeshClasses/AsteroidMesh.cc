/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AsteroidMesh.cc                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 09:05:56 by gperez            #+#    #+#             */
/*   Updated: 2021/10/20 14:52:40 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AsteroidMesh.hpp"

AsteroidMesh::AsteroidMesh()
{
	Mesh();
	this->type = E_ASTEROID;
}

void	AsteroidMesh::render(Camera &cam, float timeS, Vec3 &lightPos, Vec2 resolution)
{
	Vec3	camPos;
	Vec3	modelPos;
	float	farNear[2] = {FAR_Z, NEAR_Z};
	float	fov = FOV;

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
		modelPos = mat.getPosition();
		glUniform3fv(glGetUniformLocation(this->shader.getProgram(),
			"modelPos"), 1, (const GLfloat*)&modelPos);
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

AsteroidMesh::~AsteroidMesh()
{
}