/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 17:47:10 by gperez            #+#    #+#             */
/*   Updated: 2021/07/12 21:58:34 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Shader.hpp"

Shader::Shader(void)
{
	this->shaderProgram = 0;
}

static int		readShader(t_shader &shader, const std::string fileName, char glsl)
{
	std::string		line;
	std::ifstream	file(fileName);
	std::string		output;

	if (file.is_open())
	{
		while (std::getline(file, line))
			output += line + "\n";
		if (glsl == 'v')
			shader.vertex = output;
		else
			shader.fragment = output;
		return (0);
	}
	return (1);
}

static int		shaderError(int i_s, std::string info, std::string error_msg)
{
	glGetShaderInfoLog(i_s, 1024, NULL, (char*)info.c_str());
	std::cout << error_msg << "\n";
	std::cout << info << "\n";
	return (1);
}

unsigned int	Shader::getProgram(void)
{
	return (Shader::shaderProgram);
}

void			Shader::setProgram(unsigned int p)
{
	this->shaderProgram = p;
}

int				Shader::createShader(std::string info, const std::string vertex_path,
	const std::string frag_path)
{
	t_shader		shader;
	int				success;

	if (readShader(shader, vertex_path, 'v')
		|| readShader(shader, frag_path, 'f'))
		return (1);
	shader.i_v = glCreateShader(GL_VERTEX_SHADER);

	const char *fileV = shader.vertex.c_str();
	glShaderSource(shader.i_v, 1, &fileV, NULL);
	glCompileShader(shader.i_v);
	glGetShaderiv(shader.i_v, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		shaderError(shader.i_v, info, (char*)VERTEX_FAILED);
		glDeleteShader(shader.i_v);
		return (1);
	}
	shader.i_f = glCreateShader(GL_FRAGMENT_SHADER);

	const char *fileF = shader.fragment.c_str();
	glShaderSource(shader.i_f, 1, &fileF, NULL);
	glCompileShader(shader.i_f);
	glGetShaderiv(shader.i_f, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		shaderError(shader.i_f, info, (char*)FRAGMENT_FAILED);
		glDeleteShader(shader.i_v);
		glDeleteShader(shader.i_f);
		return (1);
	}
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, shader.i_v);
	glAttachShader(shaderProgram, shader.i_f);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		shaderError(shaderProgram, info, (char*)LINK_SHADER_FAILED);
		glDeleteShader(shader.i_v);
		glDeleteShader(shader.i_f);
		return (1);
	}
	glDeleteShader(shader.i_v);
	glDeleteShader(shader.i_f);
	return (0);
}

int				Shader::loadShader(std::string vertexPath, std::string fragPath)
{
	std::string			info;

	if (vertexPath.size() && fragPath.size())
	{
		if (createShader(info, vertexPath, fragPath))
			return (1);
	}
	return (0);
}


void			Shader::freeProgram(void)
{
	glDeleteProgram(this->shaderProgram);
	this->shaderProgram = 0;
}

Shader::~Shader()
{
	if (this->shaderProgram)
		this->freeProgram();
}