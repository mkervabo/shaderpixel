/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FieldMesh.cc                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:35:15 by gperez            #+#    #+#             */
/*   Updated: 2021/10/21 12:20:06 by maiwenn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FieldMesh.hpp"

FieldMesh::FieldMesh()
{
	Mesh();
	this->type = E_FIELD;
	this->Mesh::translate(Vec3(0., 2., -10.));
}

void	FieldMesh::render(Camera &cam, float timeS, Vec3 &lightPos, Vec2 resolution)
{
	Vec3	camPos = cam.getPosition(); 
	float	farNear[2] = {FAR_Z, NEAR_Z};
	float	fov = FOV;
	Vec3	rotCam = cam.getRotation();
	matInField.setRotation(Vec3(0., rotCam.getY(), rotCam.getZ()));
	Vec3	eyeInField = matInField.getPosition();

	if (this->distance(cam.getPosition()) > RENDER_DIST_SHADER - PREC)
		return;
	for (unsigned int i = 0 ; i < this->m_Entries.size() ; i++)
	{
		glBindVertexArray(this->m_Entries[i].getVao());
 		glUseProgram(this->shader.getProgram());

		glUniform3fv(glGetUniformLocation(this->shader.getProgram(),
			"eyeInField"), 1, (const GLfloat*)&eyeInField);
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
		Vec3 modelPos = mat.getPosition();
		glUniform3fv(glGetUniformLocation(this->shader.getProgram(),
			"modelPos"), 1, (const GLfloat*)&modelPos);
		glDrawElements(GL_TRIANGLES, this->m_Entries[i].getNumIndices(), GL_UNSIGNED_INT, NULL);
	}
}

void	FieldMesh::translate(e_axes axe, float speed)
{
	this->matInField.translate(axe, speed);
}


FieldMesh::~FieldMesh()
{
}