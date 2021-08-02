/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:01:05 by gperez            #+#    #+#             */
/*   Updated: 2021/08/02 14:02:09 by gperez           ###   ########.fr       */
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

class Mesh
{
	private:
		std::vector<MeshEntry>	m_Entries;
		std::vector<Material>	m_Materials;
		// unsigned int	id;
		Shader			shader;
		Mat				mat;
		bool			initFromScene(const aiScene* pScene, const t_objPath& path);
		void			initMesh(unsigned int Index, const aiMesh* paiMesh);
		bool			initMaterials(const aiScene* pScene, const t_objPath& path);
		void			clearTextures(void);
	public:
		Mesh();
		bool			loadMesh(t_objPath pathMesh);
		bool			loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment);
		void			render(Camera &cam, float timeS);
		void			clear(void);
		void			translate(Vec3 t);
		unsigned int	getShaderProgram(void);
		~Mesh();
};

#endif