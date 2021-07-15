/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:01:05 by gperez            #+#    #+#             */
/*   Updated: 2021/07/15 13:44:49 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MESH_HPP__
# define __MESH_HPP__

# include <iostream>
# include <string>
# include <Importer.hpp>		// C++ importer interface
# include <scene.h>				// Output data structure
# include <postprocess.h>		// Post processing flags

# include "Camera.hpp"
# include "Shader.hpp"
# include "Mat.hpp"

# define PATH_DEFAULT_TEXTURE "objToLoad/white.png"
# define PATH_TREE "objToLoad/tree/tree.3ds"
# define PATH_TREE_TXT1 "objToLoad/tree/"

class Mesh
{
	public:
		Mesh();
		bool			loadMesh(std::string pathMesh);
		bool			loadMesh(std::string pathMesh, std::string pathVertex, std::string pathFragment);
		void			render(Camera &cam);
		void			clear(void);
		~Mesh();
	private:
		// unsigned int	id;
		Shader			shader;
		Mat				mat;
		bool			initFromScene(const aiScene* pScene, const std::string& filename);
		void			initMesh(unsigned int Index, const aiMesh* paiMesh);
		bool			initMaterials(const aiScene* pScene, const std::string& filename);

		std::vector<MeshEntry> m_Entries;
		std::vector<MeshEntry> m_Textures;
};

#endif