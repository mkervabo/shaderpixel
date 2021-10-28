/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 16:57:27 by gperez            #+#    #+#             */
/*   Updated: 2021/10/28 15:38:06 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mesh.hpp"
#include "Receiver.hpp"

Mesh::Mesh()
{
	this->type = E_DEFAULT_MESH;
}

bool			Mesh::initMesh(unsigned int Index, const aiMesh* paiMesh) // Remplit un MeshEntry avec des vertices et des faces et l'ajoute au vector m_Entries
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
		// if (face.mNumIndices < 3)
		// {
		// 	std::cout << "Here\n";
		// 	return (1);
		// }
		if (face.mNumIndices > 0)
			indices.push_back(face.mIndices[0]);
		if (face.mNumIndices > 1)
			indices.push_back(face.mIndices[1]);
		if (face.mNumIndices > 2)
			indices.push_back(face.mIndices[2]);
	}
	m_Entries[Index].init(vertices, indices);
	return (0);
}

bool			Mesh::initMaterials(const aiScene* pScene, const t_objPath& path) // Genere les textures de l'objet et les ajoutes au vector m_Textures
{
	bool	ret = false;
	(void)pScene;

	std::cout << "Number Materials " << pScene->mNumMaterials << "\n";
	for (unsigned int i = 0 ; i < pScene->mNumMaterials ; i++)
	{
		const aiMaterial* pMaterial = pScene->mMaterials[i];
		bool isTexture = false;

		for (int i = 0; i < 19 && !isTexture; i++)
			if (pMaterial->GetTextureCount((aiTextureType)i))
				isTexture = true;

		if (!isTexture) // Si le materiaux ne contient pas de texture mais une couleur de base
		{
			aiColor4D	color;
			float		shininess;

			aiGetMaterialColor(pMaterial, AI_MATKEY_COLOR_DIFFUSE, &color);
			if (AI_SUCCESS != aiGetMaterialFloat(pMaterial, AI_MATKEY_SHININESS, &shininess))
				shininess = 0.f;

			this->m_Materials[i].setIsText(false);
			this->m_Materials[i].setColor(Vec3(color.r, color.g, color.b));
			this->m_Materials[i].setSpecularCoef(shininess);
		}
		else
		{
			if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
			{
				aiString pathFromAssimp;
				if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &pathFromAssimp, // On recupere le chemin relatif de la texture
					NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
				{
					std::string Dir = path.textPath;
					std::string fullPath = Dir + pathFromAssimp.data; // On ajoute le chemin relatif afin de le transformer en chemin absolue
					this->m_Materials[i].newTexture();
					std::cout << fullPath << "\n";
					if (this->m_Materials[i].load(GL_TEXTURE_2D, (char*)fullPath.c_str())) // On charge la texture et la genere pour openGL
					{
						printf("Error loading texture '%s'\n", fullPath.c_str());
						this->m_Materials[i].deleteTexture();
						ret = true;
					}
				}
			}
			else if (!this->m_Materials[i].asTexture())
			{
				this->m_Materials[i].newTexture();
				ret = this->m_Materials[i].load(GL_TEXTURE_2D, (char*)PATH_DEFAULT_TEXTURE);
			}
		}
	}
	return (ret);
}

bool			Mesh::initFromScene(const aiScene* pScene, const t_objPath& path) // Remplit notre classe Mesh
{
	this->m_Entries.resize(pScene->mNumMeshes); // Les differents mesh qui composent l'objet
	this->m_Materials.resize(pScene->mNumMaterials);

	// Initialise les maillages de la scène, un par un
	for (unsigned int i = 0 ; i < m_Entries.size() ; i++)
	{
		const aiMesh* paiMesh = pScene->mMeshes[i];
		if (initMesh(i, paiMesh))
			return (1);
	}

	return (initMaterials(pScene, path));
}

float			Mesh::distance(Vec3 pToCompare)
{
	Vec3 pMesh = this->mat.getPosition();

	return (sqrt(
		((pToCompare.getX() - pMesh.getX()) * (pToCompare.getX() - pMesh.getX()))
		+ ((pToCompare.getY() - pMesh.getY()) * (pToCompare.getY() - pMesh.getY()))
		+ ((pToCompare.getZ() - pMesh.getZ()) * (pToCompare.getZ() - pMesh.getZ()))));
}

float			Mesh::distance(Mesh& toCompare)
{
	return (this->distance(toCompare.mat.getPosition()));
}

bool			Mesh::loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment)
{
	bool				ret = false;
	Assimp::Importer	importer;

	this->clear();
	if (this->shader.loadShader(pathVertex, pathFragment))
		return (true);
	std::cout << this->shader.getProgram() << "\n";
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

bool			Mesh::loadMesh(t_objPath pathMesh)
{
	return (this->loadMesh(pathMesh, VERTEX, FRAGMENT));
}

void			Mesh::render(Camera &cam, float timeS, std::vector<Mesh*> &lights, Vec2 resolution) // On parcours tous les mesh de notre objet et on l'affiche avec la texture qui lui est lier
{
	int		boolValue = 0;
	Vec3	color;
	Vec3	camPos;
	(void)resolution;
	float	specularCoef;
	Vec3	lightPos[12] = {
		lights[0]->getPosition(),
		lights[1]->getPosition(),
		lights[2]->getPosition(),
		lights[3]->getPosition(),
		lights[4]->getPosition(),
		lights[5]->getPosition(),
		lights[6]->getPosition(),
		lights[7]->getPosition(),
		lights[8]->getPosition(),
		lights[9]->getPosition(),
		lights[10]->getPosition(),
		lights[11]->getPosition()
	};

	camPos = cam.getPosition();
	for (unsigned int i = 0 ; i < this->m_Entries.size() ; i++)
	{
		glBindVertexArray(this->m_Entries[i].getVao());
 		glUseProgram(this->shader.getProgram());
		// On check si le materiaux est une texture ou non
		const unsigned int materialIndex = this->m_Entries[i].getMatIdx();
		if (materialIndex < this->m_Materials.size() && this->m_Materials[materialIndex].asTexture())
		{
			this->m_Materials[materialIndex].bind(GL_TEXTURE0);
			boolValue = 1;
		}
		color = this->m_Materials[materialIndex].getColor();
		specularCoef = this->m_Materials[materialIndex].getSpecularCoef();

		glUniform3fv(glGetUniformLocation(this->shader.getProgram(),
			"eye"), 1, (const GLfloat*)&camPos);
		glUniform1fv(glGetUniformLocation(this->shader.getProgram(),
			"K_S"), 1, (const GLfloat*)&specularCoef);

		glUniformMatrix4fv(glGetUniformLocation(this->shader.getProgram(),
			"model"), 1, GL_FALSE, &(mat.getMatrix(false).inverse()[0][0]));
		glUniformMatrix4fv(glGetUniformLocation(this->shader.getProgram(),
			"view"), 1, GL_FALSE, &(cam.getMatrix(false)[0][0]));
		glUniformMatrix4fv(glGetUniformLocation(this->shader.getProgram(),
			"projection"), 1, GL_FALSE, &(cam.getProjMatrix()[0][0]));
		glUniform1fv(glGetUniformLocation(this->shader.getProgram(),
			"time"), 1, (const GLfloat*)&timeS);
		glUniform3fv(glGetUniformLocation(this->shader.getProgram(),
			"colorMat"), 1, (const GLfloat*)&color);
		glUniform1i(glGetUniformLocation(this->shader.getProgram(),
			"isText"), (GLuint)boolValue);
		glUniform3fv(glGetUniformLocation(this->shader.getProgram(),
			"u_lightPos"), 12, (const GLfloat*)&lightPos);
		glDrawElements(GL_TRIANGLES, this->m_Entries[i].getNumIndices(), GL_UNSIGNED_INT, NULL);
	}
}

void			Mesh::clearTextures(void)
{
	for (unsigned int i = 0; i < this->m_Materials.size(); i++)
		this->m_Materials[i].clearMaterial();
}

void			Mesh::clear(void)
{
	this->shader.freeProgram();
	this->m_Entries.clear();
	this->clearTextures();
	this->m_Materials.clear();
	// Rajouter le reste
}

void			Mesh::rotate(Vec3 r)
{
	this->mat.rotate(r);
}

void			Mesh::translate(Vec3 t)
{
	this->mat.translate(t);
}

void			Mesh::translate(e_axes axe, float speed)
{
	this->mat.translate(axe, speed);
}

void			Mesh::setPosition(Vec3 p)
{
	this->mat.setPosition(p);
}

Vec3			Mesh::getPosition(void)
{
	return (this->mat.getPosition());
}

unsigned int	Mesh::getShaderProgram(void)
{
	return (this->shader.getProgram());
}

e_meshType		Mesh::getType(void)
{
	return (this->type);
}

unsigned int	Mesh::getEntriesSize(void)
{
	return (this->m_Entries.size());
}

unsigned int	Mesh::getVao(unsigned int i)
{
	if (i >= this->m_Entries.size())
		return (0);
	return (this->m_Entries[i].getVao());
}

unsigned int	Mesh::getNumIndices(unsigned int i)
{
	if (i >= this->m_Entries.size())
		return (0);
	return (this->m_Entries[i].getNumIndices());
}

Mat				Mesh::getMat()
{
	return(this->mat);
}

Mesh::~Mesh()
{
	this->clear();
}