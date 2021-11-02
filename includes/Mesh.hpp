/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:01:05 by gperez            #+#    #+#             */
/*   Updated: 2021/11/02 16:05:08 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MESH_HPP__
# define __MESH_HPP__

# include <iostream>
# include <string>
# include <assimp/Importer.hpp>			// C++ importer interface
# include <assimp/scene.h>				// Output data structure
# include <assimp/postprocess.h>		// Post processing flags

# include "Camera.hpp"
# include "Shader.hpp"

enum e_meshType {E_DEFAULT_MESH, E_MANDELBULB, E_TETRAHEDRON, E_MANDELBOX, E_REFRACT, E_CLOUD, E_FIELD,
	E_ASTEROID, E_METABALLS, E_GLOW, E_FRAMEBUFFER, E_RENDERBUFFER, E_LIGHT};

static Vec3		g_lightPos[]
{
	Vec3(9., 1.8, -26.),	// MANDELBOX
	Vec3(-11., 2., -26.),	// MANDELBULB
	Vec3(0., 2, -34.),		// TETRAHEDRON
	Vec3(11., 1.8, -26.),	// MANDELBOX
	Vec3(0., 2., -50.),		// REFRACT
	Vec3(7., 2., -45.),		// CLOUD
	Vec3(100., 0., 0.),		// FIELD
	Vec3(-8., 2., -46.),	// ASTEROID
	Vec3(0., 2., -20.),		// METABALLS
	Vec3(-8., 3., 0.),		// GLOW
	Vec3(0., 3., 5.),		// FRAMEBUFFER
	Vec3(8., 3., 0.)		// RENDERBUFFER
};

# define NEAR_Z 0.1f
# define FAR_Z 100.f
# define WIDTH 250.
# define HEIGHT 250.

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
		virtual void	render(Camera &cam, float timeS, std::vector<Mesh*> &lights, Vec2 resolution);
		void			clear(void);
		void			translate(Vec3 t);
		void			rotate(Vec3 r);
		virtual void	translate(e_axes axe, float speed);
		void			setPosition(Vec3 p);
		Vec3			getPosition(void);
		unsigned int	getShaderProgram(void);
		e_meshType		getType(void);
		unsigned int	getEntriesSize(void);
		unsigned int	getVao(unsigned int i);
		unsigned int	getNumIndices(unsigned int i);
		Mat				getMat();
		virtual ~Mesh();
};

#endif