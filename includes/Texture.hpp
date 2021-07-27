/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:42:19 by gperez            #+#    #+#             */
/*   Updated: 2021/07/27 16:00:46 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_HPP
# define TEXTURES_HPP

# include "MeshEntry.hpp"

# define PATH_DEFAULT_TEXTURE "objToLoad/white.png"
# define PATH_HOUSE "objToLoad/house.dae"
# define PATH_TREE "objToLoad/tree/Tree1.3ds"
# define PATH_TEXTURE_TREE "objToLoad/tree/"
# define PATH_BALL "objToLoad/Ballon/Ball.obj"
# define PATH_TEXTURE_BALL "objToLoad/Ballon/"
# define PATH_DRAGON "objToLoad/BlackDragon/Dragon 2.5_ply.ply"
# define PATH_TEXTURE_DRAGON "objToLoad/BlackDragon/textures/"

enum	e_pathObj {E_PTREE, E_PBALL, E_PDRAGON, E_PEND};

typedef struct	s_objPath
{
	std::string path;
	std::string textPath;
}				t_objPath;

static t_objPath	g_objPath[]{
	{PATH_TREE, PATH_TEXTURE_TREE},
	{PATH_BALL, PATH_TEXTURE_BALL},
	{PATH_DRAGON, PATH_TEXTURE_DRAGON},
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