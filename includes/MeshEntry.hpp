/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MeshEntry.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:16:17 by gperez            #+#    #+#             */
/*   Updated: 2021/07/15 16:59:30 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MESH_ENTRY_HPP__
# define __MESH_ENTRY_HPP__

extern "C"
{
	# include "glad.h" // Implementation OpenGl
}

# include "Vec3.hpp"
# include "Vec2.hpp"
# include <vector>

typedef struct	s_vertex
{
	Vec3		pos;
	Vec2		text;
	Vec3		norm;
}				t_vertex;

class MeshEntry {
	public:
		MeshEntry();
		~MeshEntry();
		bool			init(std::vector<t_vertex>& vertices,
							std::vector<unsigned int>& indices);
		void			setMatIdx(unsigned int matIdx);
		void			setNumIndices(unsigned int numInd);
		GLuint			getVao(void);
		GLuint			getVbo(void);
		GLuint			getEbo(void);
		unsigned int	getNumIndices(void);
		unsigned int	getMatIdx(void);
	private:
		GLuint			vao;
		GLuint			vbo;
		GLuint			ebo;
		unsigned int	numIndices;
		unsigned int	materialIndex;
};
#endif