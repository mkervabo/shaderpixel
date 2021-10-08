/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:01:05 by gperez            #+#    #+#             */
/*   Updated: 2021/09/29 15:37:30 by maiwenn          ###   ########.fr       */
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
# include "Metaballs.hpp"

enum e_meshType {E_DEFAULT_MESH, E_FRACTAL, E_REFRACT, E_CLOUD, E_FIELD, E_ASTEROID};

# define NEAR_Z 0.1f
# define FAR_Z 100.f
# define WIDTH 1024.
# define HEIGHT 768.

class Mesh
{
	protected:
		std::vector<MeshEntry>	m_Entries;
		std::vector<Material>	m_Materials;
		e_meshType				type;
		Shader					shader;
		Mat						mat;
		Metaballs				meta;
		bool					initFromScene(const aiScene* pScene, const t_objPath& path);
		void					initMesh(unsigned int Index, const aiMesh* paiMesh);
		bool					initMaterials(const aiScene* pScene, const t_objPath& path);
		void					clearTextures(void);
	public:
		Mesh();
		bool			loadMesh(t_objPath pathMesh);
		virtual bool	loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment);
		virtual void	render(Camera &cam, float timeS, Vec3 &lightPos);
		void			clear(void);
		void			translate(Vec3 t);
		virtual void	translate(e_axes axe, float speed);
		void			setPosition(Vec3 p);
		unsigned int	getShaderProgram(void);
		e_meshType		getType(void);
		virtual ~Mesh();
};

#endif