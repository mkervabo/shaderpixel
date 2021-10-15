/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RefractMesh.cc                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:42:37 by gperez            #+#    #+#             */
/*   Updated: 2021/10/15 09:16:54 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "RefractMesh.hpp"

RefractMesh::RefractMesh()
{
	Mesh();
	this->type = E_REFRACT;
	this->isDiffuse = true;
	this->isSpecular = true;
}

void	RefractMesh::render(Camera &cam, float timeS, Vec3 &lightPos)
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
		glUniform1i(glGetUniformLocation(this->shader.getProgram(),
			"u_isSpecular"), (GLuint)this->isSpecular);
		glUniform1i(glGetUniformLocation(this->shader.getProgram(),
			"u_isDiffuse"), (GLuint)this->isDiffuse);
		glDrawElements(GL_TRIANGLES, this->m_Entries[i].getNumIndices(), GL_UNSIGNED_INT, NULL);
	}
}

RefractMesh::~RefractMesh()
{
}