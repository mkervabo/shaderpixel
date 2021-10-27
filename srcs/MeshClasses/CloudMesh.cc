/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CloudMesh.cc                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:45:19 by gperez            #+#    #+#             */
/*   Updated: 2021/10/26 13:43:25 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "CloudMesh.hpp"

CloudMesh::CloudMesh()
{
	Mesh();
	this->type = E_CLOUD;
	this->translate(Vec3(7., 2., -45.));
}
bool	CloudMesh::loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment)
{
	if (Mesh::loadMesh(pathMesh, pathVertex, pathFragment))
		return (true);
	this->textureCloud.newTexture();
	if (this->textureCloud.load(GL_TEXTURE_2D, (char*)CLOUD_TEXTURE_PATH))
		return (true);
	return (false);
}

void	CloudMesh::render(Camera &cam, float timeS, std::vector<Mesh*> &lights, Vec2 resolution) // On parcours tous les mesh de notre objet et on l'affiche avec la texture qui lui est lier
{
	Vec3	camPos;
	Vec3	modelPos;
	Vec3	lightPos = lights[this->type]->getPosition();
	float	farNear[2] = {FAR_Z, NEAR_Z};
	float	fov = FOV;

	for (unsigned int i = 0 ; i < this->m_Entries.size() ; i++)
	{
		glBindVertexArray(this->m_Entries[i].getVao());
 		glUseProgram(this->shader.getProgram());
		this->textureCloud.bind(GL_TEXTURE0);

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

CloudMesh::~CloudMesh()
{
}