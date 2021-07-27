/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 17:47:37 by gperez            #+#    #+#             */
/*   Updated: 2021/07/27 14:31:15 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SHADER_HPP_
# define _SHADER_HPP_

# include <iostream>
# include <string>
# include <fstream>
# include "Material.hpp"

# define VERTEX "shader/vertex.glsl"
# define FRAGMENT "shader/fragment.glsl"

# define FAILED_OPEN_FILE "Failed open file"
# define VERTEX_FAILED "Shader vertex compilation failed"
# define FRAGMENT_FAILED "Shader fragment compilation failed"
# define LINK_SHADER_FAILED "Shader link failed"

typedef struct				s_shader
{
	std::string			vertex;
	unsigned int		i_v;
	std::string			fragment;
	unsigned int		i_f;
}							t_shader;

class Shader
{
	private:
		unsigned int	shaderProgram;
		int				createShader(std::string info, std::string vertex_path,
			std::string frag_path);
	public:
		Shader(void);
		unsigned int	getProgram(void);
		void			setProgram(unsigned int p);
		
		int				loadShader(std::string vertexPath, std::string fragPath);
		void			freeProgram(void);
		~Shader();
};

#endif