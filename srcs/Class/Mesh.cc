/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 16:57:27 by gperez            #+#    #+#             */
/*   Updated: 2021/07/15 13:47:31 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mesh.hpp"

Mesh::Mesh()
{
	this->mat.rotate(Vec3(-90., 0., 0.));
}

void	Mesh::initMesh(unsigned int Index, const aiMesh* paiMesh)
{
	m_Entries[Index].setMatIdx(paiMesh->mMaterialIndex);

	std::vector<t_vertex>		vertices;
	std::vector<unsigned int>	indices;
	
	const aiVector3D			Zero3D(0.0f, 0.0f, 0.0f);


	for (unsigned int i = 0 ; i < paiMesh->mNumVertices ; i++)
	{
		const aiVector3D *pPos = &(paiMesh->mVertices[i]);
		const aiVector3D *pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D *pTexCoord = paiMesh->HasTextureCoords(0)
			? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

		t_vertex v;
		v.pos = Vec3(pPos->x, pPos->y, pPos->z);
		v.text = Vec2(pTexCoord->x, pTexCoord->y);
		v.norm = Vec3(pNormal->x, pNormal->y, pNormal->z);
		vertices.push_back(v);
	}
	for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++)
	{
		const aiFace& face = paiMesh->mFaces[i];
		assert(face.mNumIndices == 3);
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}
	m_Entries[Index].init(vertices, indices);
}

bool Mesh::initMaterials(const aiScene* pScene, const std::string& filename)
{
	bool	ret = false;
	(void)pScene;
	(void)filename;

	// for (unsigned int i = 0 ; i < pScene->mNumMaterials ; i++)
	// {
	// 	const aiMaterial* pMaterial = pScene->mMaterials[i];
	// 	m_Textures[i] = NULL;
	// 	if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
	// 	{
	// 		aiString Path;
	// 		if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path,
	// 			NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
	// 		{
	// 			std::string Dir = PATH_TREE_TXT1;
	// 			std::string FullPath = Dir + "/" + Path.data;
	// 			m_Textures[i] = new Texture(GL_TEXTURE_2D, FullPath.c_str());

	// 			if (!m_Textures[i]->Load())
	// 			{
	// 				printf("Error loading texture '%s'\n", FullPath.c_str());
	// 				delete m_Textures[i];
	// 				m_Textures[i] = NULL;
	// 				ret = false;
	// 			}
	// 		}
	// 	}
	// 	if (!m_Textures[i])
	// 	{
	// 		m_Textures[i] = new Texture(GL_TEXTURE_2D, "../Content/white.png");
	// 		ret = m_Textures[i]->Load();
	// 	}
	// }
	return (ret);
}

bool	Mesh::initFromScene(const aiScene* pScene, const std::string& filename)
{
	(void)filename;
	this->m_Entries.resize(pScene->mNumMeshes);
	this->m_Textures.resize(pScene->mNumMaterials);

	// Initialise les maillages de la scène, un par un
	for (unsigned int i = 0 ; i < m_Entries.size() ; i++)
	{
		const aiMesh* paiMesh = pScene->mMeshes[i];
		initMesh(i, paiMesh);
	}

	return (initMaterials(pScene, filename));
}

bool	Mesh::loadMesh(std::string pathMesh, std::string pathVertex, std::string pathFragment)
{
	bool				ret = false;
	Assimp::Importer	importer;

	this->clear();
	if (this->shader.loadShader(pathVertex, pathFragment))
		return (true);
	const aiScene* pScene = importer.ReadFile(pathMesh.c_str(),
		aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
	if (pScene)
		ret = initFromScene(pScene, pathMesh);
	else
	{
		printf("Error parsing '%s': '%s'\n", pathMesh.c_str(), importer.GetErrorString());
		return (true);
	}
	return (ret);
}

bool	Mesh::loadMesh(std::string pathMesh)
{
	bool			ret = this->loadMesh(pathMesh, VERTEX, FRAGMENT);
	return (ret);
}

void	Mesh::render(Camera &cam)
{
	// glEnableVertexAttribArray(0);
	// glEnableVertexAttribArray(1);
	// glEnableVertexAttribArray(2);
	for (unsigned int i = 0 ; i < this->m_Entries.size() ; i++)
	{
		glBindVertexArray(this->m_Entries[i].getVao());
 		glUseProgram(this->shader.getProgram());

		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_Entries[i].getEbo());
		// const unsigned int materialIndex = this->m_Entries[i].MaterialIndex;
		// if (materialIndex < m_Textures.size() && m_Textures[materialIndex])
		// 	m_Textures[materialIndex]->Bind(GL_TEXTURE0);

		glUniformMatrix4fv(glGetUniformLocation(this->shader.getProgram(),
			"model"), 1, GL_FALSE, &(this->mat.getMatrix(true)[0][0]));
		glUniformMatrix4fv(glGetUniformLocation(this->shader.getProgram(),
			"view"), 1, GL_FALSE, &(cam.getMatrix(true)[0][0]));
		glUniformMatrix4fv(glGetUniformLocation(this->shader.getProgram(),
			"projection"), 1, GL_FALSE, &(cam.getProjMatrix()[0][0]));

		glDrawElements(GL_TRIANGLES, this->m_Entries[i].getNumIndices(), GL_UNSIGNED_INT, NULL);
	}
	// glDisableVertexAttribArray(0);
	// glDisableVertexAttribArray(1);
	// glDisableVertexAttribArray(2);
}

void	Mesh::clear(void)
{
	this->shader.freeProgram();
	this->m_Entries.clear();
	this->m_Textures.clear();
	// Rajouter le reste
}

Mesh::~Mesh()
{
	this->clear();
}