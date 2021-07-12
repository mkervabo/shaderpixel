/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:29:41 by gperez            #+#    #+#             */
/*   Updated: 2021/07/12 11:02:52 by maiwenn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Shaderpixel.hpp"

void	display(Shaderpixel &env, Shader &shader)
{
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(env.getVao());
	glUseProgram(shader.getProgram());
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(),
		"view"), 1, GL_FALSE, &(env.getCam().getMatrix(true)[0][0]));
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(),
		"projection"), 1, GL_FALSE,&(env.getCam().getProjMatrix()[0][0]));
	glDrawElements(GL_TRIANGLES, 6 * (2 * 3), GL_UNSIGNED_INT, NULL); // NbMeshs * NbFaces * NbPoints (EBO)
	glBindVertexArray(0);
}

void	exec(Shaderpixel &env, Shader &shader)
{
	env.getKeys();
	env.checkKeys();
	display(env, shader);
	glfwSwapBuffers(env.getWindow());
	glfwPollEvents();
}

int		main(void)
{
	Shaderpixel			env;
	Shader			&shader = env.getShader();
	Camera			&cam = env.getCam();

	// Init //
	try{
		env.initWindow();}
	catch (Error const &e)
	{
		std::cout << e.what() << "\n";
		return (1);
	}
	if (shader.loadShader((char*)VERTEX, (char*)FRAGMENT))
		return (1);
	cam.setProjMatrix(perspective(FOV, RATIO, 0.1f, (float)RENDER_DIST)); // Erreur dans la perspective
	cam.translate(0.0, 2.5, 10);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	try {
		env.init();}
	catch (Error const &e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}

	// Boucle Exec //
	while(!glfwWindowShouldClose(env.getWindow()))
	{
		try {
			exec(env, shader);}
		catch (Error const &e)
		{
			std::cout << e.what() << std::endl;
			glfwSetWindowShouldClose(env.getWindow(), true);
			return (1);
		}
		GLenum err;
		while((err = glGetError()) != GL_NO_ERROR){
			std::cout << "Error " << err << '\n';
		} 
	}
	return (0);
}