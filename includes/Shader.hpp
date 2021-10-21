/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 17:47:37 by gperez            #+#    #+#             */
/*   Updated: 2021/10/21 14:04:11 by maiwenn          ###   ########.fr       */
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

# define VERTEX_MANDELBULB "shader/vertexMandelbulb.glsl"
# define FRAGMENT_MANDELBULB "shader/fragmentMandelbulb.glsl"

# define FRAGMENT_MANDELBOX "shader/fragmentMandelbox.glsl"
# define VERTEX_MANDELBOX "shader/vertexMandelbox.glsl"

# define FRAGMENT_METABALLS "shader/fragmentMetaballs.glsl"
# define VERTEX_METABALLS "shader/vertexMetaballs.glsl"

# define FRAGMENT_TETRAHEDRON "shader/fragmentTetrahedron.glsl"

# define VERTEX_FIELD "shader/vertexField.glsl"
# define FRAGMENT_FIELD "shader/fragmentField.glsl"

# define VERTEX_ASTEROID "shader/vertexAsteroid.glsl"
# define FRAGMENT_ASTEROID "shader/fragmentAsteroid.glsl"

# define VERTEX_CLOUD "shader/vertexCloud.glsl"
# define FRAGMENT_CLOUD "shader/fragmentCloud.glsl"

# define VERTEX_REFRACT "shader/vertexRefract.glsl"
# define FRAGMENT_REFRACT "shader/fragmentRefract.glsl"

# define VERTEX_LIGHT "shader/vertexLight.glsl"
# define FRAGMENT_LIGHT "shader/fragmentLight.glsl"

# define FRAGMENT_GLOW "shader/fragmentGlow.glsl"
# define VERTEX_GLOW "shader/vertexGlow.glsl"

# define FRAGMENT_FRAMEBUFFER "shader/frameBuffer/fragmentFrameBuffer.glsl"
# define VERTEX_FRAMEBUFFER "shader/frameBuffer/vertexFrameBuffer.glsl"

# define FAILED_OPEN_FILE "Failed open file"
# define FAILED_READ_SHADER "Failed to read shader"
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
		int				createShader(std::string vertex_path, std::string frag_path);
	public:
		Shader(void);
		unsigned int	getProgram(void);
		void			setProgram(unsigned int p);
		int				loadShader(std::string vertexPath, std::string fragPath);
		void			freeProgram(void);
		~Shader();
};

#endif