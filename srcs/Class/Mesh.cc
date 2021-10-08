/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 16:57:27 by gperez            #+#    #+#             */
/*   Updated: 2021/10/08 10:31:08 by maiwenn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mesh.hpp"
#include "Receiver.hpp"

Mesh::Mesh()
{
	// this->mat.rotate(Vec3(-90., 0., 0.));
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
	this->meta = Metaballs();
}

bool Mesh::initMaterials(const aiScene* pScene, const t_objPath& path) // Genere les textures de l'objet et les ajoutes au vector m_Textures
{
	bool	ret = false;
	(void)pScene;

	std::cout << "Number Materials " << pScene->mNumMaterials << "\n";
	for (unsigned int i = 0 ; i < pScene->mNumMaterials ; i++)
	{
		const aiMaterial* pMaterial = pScene->mMaterials[i];

		// for (int i = 0; i < 19; i++)
		// 	std::cout << i << " materials " << pMaterial->GetTextureCount((aiTextureType)i) << "\n";
		// std::cout << "\n";

		bool isTexture = false;

		for (int i = 0; i < 19 && !isTexture; i++)
			if (pMaterial->GetTextureCount((aiTextureType)i))
				isTexture = true;

		if (!isTexture) // Si le materiaux ne contient pas de texture mais une couleur de base
		{
			aiColor4D	color;

			aiGetMaterialColor(pMaterial, AI_MATKEY_COLOR_DIFFUSE, &color);
			// std::cout << color.r << " " << color.g << " " << color.b << "\n";
			this->m_Materials[i].setIsText(false);
			this->m_Materials[i].setColor(Vec3(color.r, color.g, color.b));
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
					if (this->m_Materials[i].getTexture()->load(GL_TEXTURE_2D, (char*)fullPath.c_str())) // On charge la texture et la genere pour openGL
					{
						printf("Error loading texture '%s'\n", fullPath.c_str());
						this->m_Materials[i].deleteTexture();
						ret = true;
					}
				}
			}
			else if (!this->m_Materials[i].getTexture())
			{
				this->m_Materials[i].newTexture();
				ret = this->m_Materials[i].getTexture()->load(GL_TEXTURE_2D, (char*)PATH_DEFAULT_TEXTURE);
			}
		}
	}
	return (ret);
}

bool	Mesh::initFromScene(const aiScene* pScene, const t_objPath& path) // Remplit notre classe Mesh
{
	this->m_Entries.resize(pScene->mNumMeshes); // Les differents mesh qui composent l'objet
	this->m_Materials.resize(pScene->mNumMaterials);

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

bool	Mesh::loadMesh(t_objPath pathMesh)
{
	return (this->loadMesh(pathMesh, VERTEX, FRAGMENT));
}


// #include <iostream>
// #include <irrKlang.h>
// #include <ik_ISoundMixedOutputReceiver.h>
// using namespace irrklang;


void	Mesh::render(Camera &cam, float timeS, Vec3 &lightPos, Mat &modelMat) // On parcours tous les mesh de notre objet et on l'affiche avec la texture qui lui est lier
{
	int		boolValue = 1;
	Vec3	camPos;
	Vec3	color;
	float	farNear[2] = {FAR_Z, NEAR_Z};
	float	fov = FOV;
	Vec2	resolution = Vec2(WIDTH, HEIGHT);

	// glEnableVertexAttribArray(0);
	// glEnableVertexAttribArray(1);
	// glEnableVertexAttribArray(2);

	#include <iostream>
	#include <irrKlang.h>
	#include <ik_ISoundMixedOutputReceiver.h>
	using namespace irrklang;
	
	for (unsigned int i = 0 ; i < this->m_Entries.size() ; i++)
	{
		glBindVertexArray(this->m_Entries[i].getVao());
 		glUseProgram(this->shader.getProgram());
		// On check si le materiaux est une texture ou non
		const unsigned int materialIndex = this->m_Entries[i].getMatIdx();
		if (materialIndex < this->m_Materials.size() && this->m_Materials[materialIndex].getTexture())
			this->m_Materials[materialIndex].getTexture()->bind(GL_TEXTURE0);
		else
			boolValue = 0;
		color = this->m_Materials[materialIndex].getColor();

		glUniformMatrix4fv(glGetUniformLocation(this->shader.getProgram(),
			"modelMat"), 1, GL_FALSE, &(modelMat.getInverseMat()[0][0]));
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

		glUniform1i(glGetUniformLocation(this->shader.getProgram(), // BASIC_SHADER
			"isText"), (GLuint)boolValue);
		glUniform3fv(glGetUniformLocation(this->shader.getProgram(),
			"colorMat"), 1, (const GLfloat*)&color);

		//METABALLS SHADER
		//irrklang:
		// Receiver* receiver = NULL;
		// engine->setMixedDataOutputReceiver(receiver);
		float offset = this->meta.getSize();
		glUniform1fv(glGetUniformLocation(this->shader.getProgram(),
			"metaSize"), 1, (const GLfloat*)&offset);
		offset = this->meta.getVelocity();
		glUniform1fv(glGetUniformLocation(this->shader.getProgram(),
			"metaVelocity"), 1, (const GLfloat*)&offset);
		offset = this->meta.getMaxSize();
		glUniform1fv(glGetUniformLocation(this->shader.getProgram(),
			"metaMaxSize"), 1, (const GLfloat*)&offset);
		offset = this->meta.getMinSize();
		glUniform1fv(glGetUniformLocation(this->shader.getProgram(),
			"metaMinSize"), 1, (const GLfloat*)&offset);
		unsigned int nbBalls = this->meta.getNbBalls();
		glUniform1i(glGetUniformLocation(this->shader.getProgram(),
			"metaNbBalls"), (GLuint)nbBalls);

		glDrawElements(GL_TRIANGLES, this->m_Entries[i].getNumIndices(), GL_UNSIGNED_INT, NULL);
	}
	// glDisableVertexAttribArray(0);
	// glDisableVertexAttribArray(1);
	// glDisableVertexAttribArray(2);
}

void	Mesh::clearTextures(void)
{
	for (unsigned int i = 0; i < this->m_Materials.size(); i++)
		this->m_Materials[i].clearMaterial();
}

void	Mesh::clear(void)
{
	this->shader.freeProgram();
	this->m_Entries.clear();
	this->clearTextures();
	this->m_Materials.clear();
	// Rajouter le reste
}

void	Mesh::translate(Vec3 t)
{
	this->mat.translate(t);
}

void	Mesh::setPosition(Vec3 p)
{
	this->mat.setPosition(p);
}

unsigned int	Mesh::getShaderProgram(void)
{
	return (this->shader.getProgram());
}

Mesh::~Mesh()
{
	this->clear();
}