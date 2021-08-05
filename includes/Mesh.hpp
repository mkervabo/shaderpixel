/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:01:05 by gperez            #+#    #+#             */
/*   Updated: 2021/08/05 00:53:14 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MESH_HPP__
# define __MESH_HPP__

# include <iostream>
# include <string>
# include <assimp/Importer.hpp>		// C++ importer interface
# include <assimp/scene.h>				// Output data structure
# include <assimp/postprocess.h>		// Post processing flags

# include "Camera.hpp"
# include "Shader.hpp"

# define NEAR_Z 0.1f
# define FAR_Z 100.f
# define WIDTH 1024.
# define HEIGHT 768.

class Mesh
{
	private:
		std::vector<MeshEntry>	m_Entries;
		std::vector<Material>	m_Materials;
		// unsigned int	id;
		Shader					shader;
		Mat						mat;
		bool					initFromScene(const aiScene* pScene, const t_objPath& path);
		void					initMesh(unsigned int Index, const aiMesh* paiMesh);
		bool					initMaterials(const aiScene* pScene, const t_objPath& path);
		void					clearTextures(void);
	public:
		Mesh();
		bool			loadMesh(t_objPath pathMesh);
		bool			loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment);
		void			render(Camera &cam, float timeS, Vec3 &lightPos, Mat &modelMat);
		void			clear(void);
		void			translate(Vec3 t);
		void			setPosition(Vec3 p);
		unsigned int	getShaderProgram(void);
		~Mesh();
};

#endif