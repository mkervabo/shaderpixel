/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:01:05 by gperez            #+#    #+#             */
/*   Updated: 2021/07/19 11:09:18 by maiwenn          ###   ########.fr       */
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
# include "Mat.hpp"

class Mesh
{
	public:
		Mesh();
		bool			loadMesh(t_objPath pathMesh);
		bool			loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment);
		void			render(Camera &cam);
		void			clear(void);
		~Mesh();
	private:
		// unsigned int	id;
		Shader			shader;
		Mat				mat;
		bool			initFromScene(const aiScene* pScene, const t_objPath& path);
		void			initMesh(unsigned int Index, const aiMesh* paiMesh);
		bool			initMaterials(const aiScene* pScene, const t_objPath& path);
		void			clearTextures(void);

		std::vector<MeshEntry>	m_Entries;
		std::vector<Texture*>	m_Textures;
};

#endif