/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shaderpixel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:39:31 by gperez            #+#    #+#             */
/*   Updated: 2021/06/18 18:34:18 by maiwenn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SHADERPIXEL_HPP__
# define __SHADERPIXEL_HPP__

# include <iostream>
# include "Error.hpp"
# include "Hud.hpp"
# include <queue>
# include "Vec2.hpp"
# include "TimeMs.hpp"
# include "Mesh.hpp"
# include "CloudMesh.hpp"
# include "RefractMesh.hpp"
# include "FractalMesh.hpp"
# include "FieldMesh.hpp"
# include "AsteroidMesh.hpp"
# include "MetaballsMesh.hpp"
# include "GlowMesh.hpp"
# include "FrameBufferMesh.hpp"
# include "RenderBufferMesh.hpp"
# include "glfw3.h" // Load fenetre

# define RATIO (float)WIDTH / (float)HEIGHT
# define PROG_NAME "Shaderpixel"
# define FRAME_RATE 1.0f / 30.0f

# define VBO_SIZE 24
# define EBO_SIZE 36

enum	e_vsync {VSYNC_OFF, VSYNC_ON};
enum	e_stateKey {KEY_PRESS, KEY_DONE, KEY_RELEASE};

class Shaderpixel
{
	private:
		GLFWwindow					*window;
		Hud							hud;
		TimeMs						time;
		int							frameNb;
		int							currentFrameNb;
		float						lastTime;
		float						deltaTime;
		float						addedTime;

		Camera						cam;
		bool						isCursor;
		Vec2						mouseLastPos;
		bool						firstMoove;

		// Keys //
		std::queue<char>			queue;
		char						keys[GLFW_KEY_END];
		void						setKey(unsigned int key, char state);
		void						inputKey(unsigned int key);
		void						fieldKeys(void);

		bool						load(e_pathObj enu, std::string pathVertex, std::string pathFragment, e_meshType type);
		std::vector<Mesh*>			meshes;

	public:
		Shaderpixel();
		void						initWindow(void);
		bool						init(void);
		void						update(Camera &cam);
		void						displayHud(void);
		void						checkKeys(void);
		void 						loadVBO(void);
		bool						loadMesh(t_objPath obj);
		bool						loadMesh(t_objPath obj, std::string pathVertex, std::string pathFragment, e_meshType type);

		void						getKeys(void);
		unsigned int				getState(unsigned int k);
		GLFWwindow					*getWindow(void);
		Camera						&getCam(void);
		Vec2						getMouseLastPos(void);

		void						setMouseLastPos(Vec2 pos);
		void						setFirst(bool isFirst);
		
		void						generateBuffers(void);
		
		bool						isFirst(void);

		void						calcTime(void);
		bool						isTimeToDisplay(void);
		int							getFrameNb(void);
		~Shaderpixel();
};

#endif