/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:01:05 by gperez            #+#    #+#             */
/*   Updated: 2021/10/20 16:16:15 by maiwenn          ###   ########.fr       */
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

enum e_meshType {E_DEFAULT_MESH, E_FRACTAL, E_REFRACT, E_CLOUD, E_FIELD, E_ASTEROID, E_METABALLS, E_GLOW, E_FRAMEBUFFER};

# define NEAR_Z 0.1f
# define FAR_Z 100.f
# define WIDTH 1024.
# define HEIGHT 768.
# define RENDER_DIST_SHADER 80.

class Mesh
{
	protected:
		std::vector<MeshEntry>	m_Entries;
		std::vector<Material>	m_Materials;
		e_meshType				type;
		Shader					shader;
		Mat						mat;
		bool					initFromScene(const aiScene* pScene, const t_objPath& path);
		bool					initMesh(unsigned int Index, const aiMesh* paiMesh);
		bool					initMaterials(const aiScene* pScene, const t_objPath& path);
		void					clearTextures(void);
	public:
		Mesh();
		float			distance(Mesh& toCompare);
		float			distance(Vec3 pToCompare);
		bool			loadMesh(t_objPath pathMesh);
		virtual bool	loadMesh(t_objPath pathMesh, std::string pathVertex, std::string pathFragment);
		virtual void	render(Camera &cam, float timeS, Vec3 &lightPos, Vec2 resolution);
		void			clear(void);
		void			translate(Vec3 t);
		void			rotate(Vec3 r);
		virtual void	translate(e_axes axe, float speed);
		void			setPosition(Vec3 p);
		unsigned int	getShaderProgram(void);
		e_meshType		getType(void);
		virtual ~Mesh();
};

#endif