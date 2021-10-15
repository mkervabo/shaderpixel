/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shaderpixel.cc                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:39:27 by gperez            #+#    #+#             */
/*   Updated: 2021/10/15 15:58:07 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Shaderpixel.hpp"

Shaderpixel::Shaderpixel()
{
	this->time.setTime();
	this->frameNb = 0;
	this->currentFrameNb = 0;
	this->lastTime = 0.;
	this->deltaTime = 0.;
	this->firstMoove = true;
	for (unsigned int i = 0; i < GLFW_KEY_END; i++)
		this->keys[i] = KEY_RELEASE;
	this->isCursor = false;
}

void				Shaderpixel::setMouseLastPos(Vec2 pos)
{
	this->mouseLastPos = pos;
}

Vec2				Shaderpixel::getMouseLastPos(void)
{
	return (this->mouseLastPos);
}

unsigned int		Shaderpixel::getState(unsigned int k)
{
	if (k > GLFW_KEY_END)
		return (KEY_RELEASE);
	return (this->keys[k]);
}

GLFWwindow			*Shaderpixel::getWindow(void)
{
	return (this->window);
}

Camera				&Shaderpixel::getCam(void)
{
	return (this->cam);
}

void				Shaderpixel::setFirst(bool isFirst)
{
	this->firstMoove = isFirst;
}

static void			mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Shaderpixel		*engine = (Shaderpixel*)glfwGetWindowUserPointer(window);
	Vec2		offsetMouse;
	Vec2		lastMousePos;

	if (!engine)
		return ;
	if (engine->isFirst())
	{
		engine->setMouseLastPos(Vec2(xpos, ypos));
		engine->setFirst(false);
	}
	lastMousePos = engine->getMouseLastPos();
	offsetMouse.setY(xpos - lastMousePos.getX());
	offsetMouse.setX(ypos - lastMousePos.getY());
	engine->setMouseLastPos(Vec2(xpos, ypos));
	offsetMouse = offsetMouse * SENSITIVITY;
	engine->getCam().rotate(Vec3(offsetMouse.getX(), offsetMouse.getY(), 0.0));
}

void				Shaderpixel::initWindow(void)
{
	if (!glfwInit())
	{
		throw (Error(E_FAIL_INIT_GLFW, FAIL_INIT_GLFW, 1));
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	this->window = glfwCreateWindow(WIDTH, HEIGHT, (char*)PROG_NAME, NULL, NULL);
	if (this->window == NULL)
	{
		throw (Error(E_FAIL_CREATE_WINDOW, FAIL_CREATE_WINDOW, 1));
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(this->window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw (Error(E_FAIL_INIT_GLFW, FAIL_INIT_GLAD, 1));
		return ;
	}
	glfwSetCursorPosCallback(this->window, mouse_callback);
	glfwSetWindowUserPointer(this->window, this);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSwapInterval(VSYNC_ON);
}

bool						Shaderpixel::loadMesh(t_objPath obj)
{
	return (this->loadMesh(obj, VERTEX, FRAGMENT, E_DEFAULT_MESH));
}

bool						Shaderpixel::loadMesh(t_objPath obj, std::string pathVertex, std::string pathFragment, e_meshType type)
{
	if (type == E_CLOUD)
		this->meshes.push_back(new CloudMesh);
	else if (type == E_REFRACT)
		this->meshes.push_back(new RefractMesh);
	else if (type == E_FRACTAL)
		this->meshes.push_back(new FractalMesh);
	else if (type == E_FIELD)
		this->meshes.push_back(new FieldMesh);
	else if (type == E_ASTEROID)
		this->meshes.push_back(new AsteroidMesh);
	else if (type == E_METABALLS)
		this->meshes.push_back(new MetaballsMesh);
	else if (type == E_GLOW)
		this->meshes.push_back(new GlowMesh);
	else if (type == E_RENDER_BUFFER)
		this->meshes.push_back(new RenderBufferMesh);
	else
		this->meshes.push_back(new Mesh);
	if (!this->meshes.size())
		return (1);
	if (this->meshes[this->meshes.size() - 1]->loadMesh(obj, pathVertex, pathFragment))
	{
		this->meshes.pop_back();
		return (1);
	}
	return (0);
}

bool				Shaderpixel::load(e_pathObj enu, std::string pathVertex, std::string pathFragment, e_meshType type)
{
	if (enu >= E_PEND)
		return (1);
	return (this->loadMesh(g_objPath[enu], pathVertex, pathFragment, type));
}

bool				Shaderpixel::init(void)
{
	if (this->hud.init())
		return (1);
	if (load(E_PBALL, VERTEX_LIGHT, FRAGMENT_LIGHT, E_DEFAULT_MESH)
		|| load(E_PBALL, VERTEX, FRAGMENT, E_DEFAULT_MESH)
		|| load(E_PCUBE, VERTEX_MANDELBULB, FRAGMENT_MANDELBULB, E_FRACTAL))
			return (1);
	this->meshes[1]->translate(Vec3(0., 0., -3.5));
	// this->meshes[2]->rotate(Vec3(90., 0., 0.));

	// std::cout << this->meshes[0]->getShaderProgram() << " " << this->meshes[1]->getShaderProgram() << "\n";
	this->time.setTime();
	return (0);
}

void				Shaderpixel::update(Camera &cam)
{
	float	time = this->time.getTimeSeconds();
	Vec3	lightPos = Vec3(1. * cos(time * 0.5), 1., 1. * sin(time * 0.5));
	
	this->meshes[0]->setPosition(lightPos);
	for (unsigned int i = 0; i < this->meshes.size(); i++)
		this->meshes[i]->render(cam, time, lightPos);
	this->currentFrameNb++;
}

void				Shaderpixel::displayHud(void)
{
	if (this->isTimeToDisplay())
	{
		std::cout << this->frameNb << "\n";
		this->frameNb = currentFrameNb;
		this->currentFrameNb = 0;
	}
	this->hud.display(this->getFrameNb());
}

void				Shaderpixel::inputKey(unsigned int key)
{
	if (glfwGetKey(this->window, key) == GLFW_PRESS
		&& this->keys[key] == KEY_RELEASE)
	{
		this->keys[key] = KEY_PRESS;
		this->queue.push(key);
	}
	else if (glfwGetKey(this->window, key) == GLFW_RELEASE
		&& this->keys[key] == KEY_DONE)
			this->keys[key] = KEY_RELEASE;
}

void				Shaderpixel::fieldKeys(void)
{
	if (this->meshes.size() <= 2)
		return;
	if (glfwGetKey(this->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		this->meshes[2]->translate(E_RIGHT, -SPEED);
	if (glfwGetKey(this->window, GLFW_KEY_LEFT) == GLFW_PRESS)
		this->meshes[2]->translate(E_RIGHT, SPEED);
	if (glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS)
		this->meshes[2]->translate(E_FRONT, -SPEED);
	if (glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS)
		this->meshes[2]->translate(E_FRONT, SPEED);
}

void				Shaderpixel::getKeys(void)
{
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(this->window, true);
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
		this->cam.translate(E_FRONT, SPEED);
	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
		this->cam.translate(E_FRONT, -SPEED);
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
		this->cam.translate(E_RIGHT, SPEED);
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
		this->cam.translate(E_RIGHT, -SPEED);
	if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
		this->cam.translate(E_UP, SPEED);
	if (glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		this->cam.translate(E_UP, -SPEED);
	fieldKeys();
	this->inputKey(GLFW_KEY_APOSTROPHE);
}

void				Shaderpixel::checkKeys(void)
{
	char	i;

	while (this->queue.size())
	{
		i = this->queue.front();
		if (i == GLFW_KEY_APOSTROPHE)
		{
			this->isCursor = !this->isCursor;
			glfwSetInputMode(window, GLFW_CURSOR, this->isCursor
				? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
			glfwSetCursorPosCallback(this->window, this->isCursor
				? NULL : mouse_callback);
		}
		this->keys[(int)i] = KEY_DONE;
		this->queue.pop();
	}
}

bool				Shaderpixel::isFirst(void)
{
	return (this->firstMoove);
}

void				Shaderpixel::calcTime(void)
{
	float currentTime = this->time.getTimeSeconds();
	this->deltaTime = currentTime - this->lastTime;
	this->lastTime = currentTime;
}

bool				Shaderpixel::isTimeToDisplay(void)
{
	this->addedTime += this->deltaTime;
	if (this->addedTime < 1. + PREC)
		return (false);
	this->addedTime = 0.;
	return (true);
}

int					Shaderpixel::getFrameNb(void)
{
	return (this->frameNb);
}

Shaderpixel::~Shaderpixel()
{
	for (unsigned int i = 0; i < this->meshes.size(); i++)
		delete meshes[i];
	glfwDestroyWindow(this->window);
	glfwTerminate();
}