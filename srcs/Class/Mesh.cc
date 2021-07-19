/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 16:57:27 by gperez            #+#    #+#             */
/*   Updated: 2021/07/19 11:08:30 by maiwenn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mesh.hpp"

Mesh::Mesh()
{
	this->mat.rotate(Vec3(-90., 0., 0.));
}

void	Mesh::initMesh(unsigned int Index, const aiMesh* paiMesh) // Remplit un MeshEntry avec des vertices et des faces et l'ajoute au vector m_Entries
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

bool Mesh::initMaterials(const aiScene* pScene, const t_objPath& path) // Genere les textures de l'objet et les ajoutes au vector m_Textures
{
	bool	ret = false;
	(void)pScene;

	std::cout << "Number Materials " << pScene->mNumMaterials << "\n";
	for (unsigned int i = 0 ; i < pScene->mNumMaterials ; i++)
	{
		const aiMaterial* pMaterial = pScene->mMaterials[i];
		m_Textures[i] = NULL;
		// for (int i = 0; i < 18; i++)
		// 	std::cout << i << " materials " << pMaterial->GetTextureCount((aiTextureType)i) << "\n";
		// std::cout << "\n";
		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			aiString pathFromAssimp;
			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &pathFromAssimp, // On recupere le chemin relatif de la texture
				NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				std::string Dir = path.textPath;
				std::string fullPath = Dir + pathFromAssimp.data; // On ajoute le chemin relatif afin de le transformer en chemin absolue
				m_Textures[i] = new Texture();
				std::cout << fullPath << "\n";
				if (m_Textures[i]->load(GL_TEXTURE_2D, (char*)fullPath.c_str())) // On charge la texture et la genere pour openGL
				{
					printf("Error loading texture '%s'\n", fullPath.c_str());
					delete m_Textures[i];
					m_Textures[i] = NULL;
					ret = true;
				}
			}
		}
		if (!m_Textures[i])
		{
			m_Textures[i] = new Texture();
			ret = m_Textures[i]->load(GL_TEXTURE_2D, (char*)PATH_DEFAULT_TEXTURE);
		}
	}
	return (ret);
}

bool	Mesh::initFromScene(const aiScene* pScene, const t_objPath& path) // Remplit notre classe Mesh
{
	this->m_Entries.resize(pScene->mNumMeshes); // Les differents mesh qui composent l'objet
	this->m_Textures.resize(pScene->mNumMaterials);

	// Initialise les maillages de la scène, un par un
	for (unsigned int i = 0 ; i < m_Entries.size() ; i++)
	{
		const aiMesh* paiMesh = pScene->mMeshes[i];
		initMesh(i, paiMesh);
	}

	return (initMaterials(pScene, path));
}

bool	Mesh::loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment)
{
	bool				ret = false;
	Assimp::Importer	importer;

	this->clear();
	if (this->shader.loadShader(pathVertex, pathFragment))
		return (true);
	const aiScene* pScene = importer.ReadFile(pathMesh.path.c_str(), // On lit le fichier et on le stock dans une scene avec les faces triangulé.
		aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
	if (pScene)
		ret = initFromScene(pScene, pathMesh);
	else
	{
		printf("Error parsing '%s': '%s'\n", pathMesh.path.c_str(), importer.GetErrorString());
		return (true);
	}
	return (ret);
}

bool	Mesh::loadMesh(t_objPath pathMesh)
{
	return (this->loadMesh(pathMesh, VERTEX, FRAGMENT));
}

void	Mesh::render(Camera &cam) // On parcours tous les mesh de notre objet et on l'affiche avec la texture qui lui est lier
{
	// glEnableVertexAttribArray(0);
	// glEnableVertexAttribArray(1);
	// glEnableVertexAttribArray(2);
	for (unsigned int i = 0 ; i < this->m_Entries.size() ; i++)
	{
		glBindVertexArray(this->m_Entries[i].getVao());
 		glUseProgram(this->shader.getProgram());

		const unsigned int materialIndex = this->m_Entries[i].getMatIdx();
		if (materialIndex < this->m_Textures.size() && this->m_Textures[materialIndex])
			this->m_Textures[materialIndex]->bind(GL_TEXTURE0);

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

void	Mesh::clearTextures(void)
{
	for (unsigned int i = 0; i < this->m_Textures.size(); i++)
	{
		if (this->m_Textures[i])
		{
			delete this->m_Textures[i];
			this->m_Textures[i] = NULL;
		}
	}
}

void	Mesh::clear(void)
{
	this->shader.freeProgram();
	this->m_Entries.clear();
	this->clearTextures();
	this->m_Textures.clear();
	// Rajouter le reste
}

Mesh::~Mesh()
{
	this->clear();
}