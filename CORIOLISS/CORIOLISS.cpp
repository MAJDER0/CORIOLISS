#include <SDL.h>
#include <glad/glad.h>
#include <iostream>


int main(int, char**) {

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";


	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
		"}\n\0";

	// Initialize window via SDL and get OpenGL dependencies
	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


	SDL_Window* window = SDL_CreateWindow("CORIOLISS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext openGLcontext = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, openGLcontext);
	SDL_GL_SetSwapInterval(1); 

	//load openGl functions
	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

	// tell openGL to draw on created window
	int dw, dh;
	SDL_GL_GetDrawableSize(window, &dw, &dh);
	glViewport(0, 0, dw, dh);


	//change background color
	 
	glClearColor(0.10f, 0.12f, 0.16f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(window);


	float vertices[] = 
	{ 
		-0.5f, -0.5f, 0.0f, 
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f 
	};

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	GLuint VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// keep window opened

	bool exitWindow = false;
	SDL_Event event;


	while(!exitWindow)
	{
		glClearColor(0.10f, 0.12f, 0.16f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		SDL_GL_SwapWindow(window);

		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				exitWindow = true;
			}
		}
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	SDL_Quit();

	return 0;
}
