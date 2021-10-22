/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:42:19 by gperez            #+#    #+#             */
/*   Updated: 2021/10/22 14:28:18 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_HPP
# define TEXTURES_HPP

# include "MeshEntry.hpp"

# define PATH_DEFAULT_TEXTURE "objToLoad/white.png"
# define PATH_TREE "objToLoad/tree/Tree1.3ds"
# define PATH_TEXTURE_TREE "objToLoad/tree/"

# define PATH_BALL "objToLoad/Ballon/Ball.obj"
# define PATH_TEXTURE_BALL "objToLoad/Ballon/"

# define PATH_DRAGON "objToLoad/BlackDragon/Dragon 2.5_ply.ply"
# define PATH_TEXTURE_DRAGON "objToLoad/BlackDragon/textures/"

# define PATH_CUBE "objToLoad/cube/cube.obj"
# define PATH_TEXTURE_CUBE "objToLoad/cube/"

# define PATH_PLANE "objToLoad/plane/plane.obj"
# define PATH_TEXTURE_PLANE "objToLoad/plane/"

# define PATH_PLANE_SIDE "objToLoad/planS/planS.obj"
# define PATH_TEXTURE_PLANE_SIDE "objToLoad/planS/"

# define PATH_CHURCHE "objToLoad/Church/churchModel.obj"
# define PATH_TEXTURE_CHURCHE "objToLoad/Church/"

# define PATH_FRAMEWORK "objToLoad/FrameWork/frameWork.obj"
# define PATH_TEXTURE_FRAMEWORK "objToLoad/FrameWork/"

enum	e_pathObj {E_PTREE, E_PBALL, E_PDRAGON, E_PCUBE, E_PPLANE, E_PPLANES, E_PCHURCHE, E_PFRAMEWORK, E_PEND};

typedef struct	s_objPath
{
	std::string path;
	std::string textPath;
}				t_objPath;

static t_objPath	g_objPath[]{
	{PATH_TREE, PATH_TEXTURE_TREE},
	{PATH_BALL, PATH_TEXTURE_BALL},
	{PATH_DRAGON, PATH_TEXTURE_DRAGON},
	{PATH_CUBE, PATH_TEXTURE_CUBE},
	{PATH_PLANE, PATH_TEXTURE_PLANE},
	{PATH_PLANE_SIDE, PATH_TEXTURE_PLANE_SIDE},
	{PATH_CHURCHE, PATH_TEXTURE_CHURCHE},
	{PATH_FRAMEWORK, PATH_TEXTURE_FRAMEWORK},
	{"", ""}
};

class Texture
{
	public:
		Texture();
		bool			load(GLenum target, char *txtPath);
		void			bind(GLenum textureUnit);
		int				getWidth(void);
		int				getHeight(void);
		unsigned int	getTxt(void);
		unsigned char	*getTxtData(void);
		~Texture();
	private:
		int				width;
		int				height;
		int				nrChannels;
		unsigned int	txt;
		unsigned char	*txtData;
		GLenum			txtTarget;
};

#endif