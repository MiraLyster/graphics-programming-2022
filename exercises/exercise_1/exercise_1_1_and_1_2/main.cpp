#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

/*Source code for the vertex shader. For OpenGl to use the shader, it has to dynamically
compile it at run-time from its source code*/
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
/*Source code for fragment shader*/
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main(){
	//The GLW window is instantiated

	//Here we initialize GLFW and then we can configure
	glfwInit();
	/*glfWindowHint tells us what option we want to configure. There's different prefixed options when using GLFW_
	The second argument is an integer that sets the value of our option. 
	Both major and minor is set to 3 to say it's OpenGL version 3.3 we want to use*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	/*We're telling GLFW we want to use core-profile, as we'll get access to a 
	smaller subset of OpenGL features*/
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	/*This is a window object and holds all the windowing data that is 
	required by most of GLFW's other functions*/

	/*glfwCreateWindow function requires the window width and height as the first two 
	arguments. The third argument allows us to create a name for the window. 
	We can ignore the last two parameters. The function returns a 
	GLFWwindow objct that we'll later need for other GLFW operations.
	After that we tell GLFW to make the context of our window the main context
	on the current thread*/
	//glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/*GLAD manages function pointers for OpenGL and we want to initialize GLAD before
	we CALL any OpenGL function*/
	/*We pass GLAD the function to load the adress of the OpenGL function pointers
	which is OS-specific. GLWF gives us glfwGetProcAddress that defines the 
	correct function based on which OS we're compiling for.*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/*Build and compile the shader program. 
	This is the vertexShader*/
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	/*We provide the type of shader we want to create as an argument to glCreateShader
	Since we're creating a vertex shader we pass in GL_VERTEX_SHADER.
	The glShaderSource function takes the shader object to compile to as its first argument.
	The second argument specifies how many strings we're passing as source code, which is only 1.
	The third parameter is the actual source code of the vertex shader and we can leave the 
	4th parameter to NULL*/
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	/*Check for shader compile errors
	First we define an integer to indicate success and a storage container for the error messages (if any)
	Then we check if compilation was successful with glGetShaderiv. If compilation failed, we should
	retrieve the error message with glGetShaderInforLog and print the error message.*/
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	/*Build and compile fragment shader*/
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//Check for shader compile errors 
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	/*A shader program object is the final linked version of mulitple shaders combined. 
	To use recently compiled shaders, we have to link to a shader program object and then activate
	this shader program when rendering objects. This actived shader program's shaders
	will be used when we issue render calls. 
	
	When linking the shaders into a program it links the outputs of each shader to the input
	of the next shader. This is also where you'll get linking errors if your outputs don't match.
	Link shaders. 
	
	glCreateProgram() - function creates a program and returns the ID reference to the newly
	created progam object. Now we need attach the previously compiled shaders to the program
	object and then link them with glLinkProgram*/
	//Link shaders
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Check for linking errors 
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	/*The shader objects has to be deleted once we've linked them into the program object*/
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/*OpenGL is a 3D graphics library so all coordinates that we specify are in 3D (x,y and z)
	Anything other than between -1.0 and 1.0 won't be rendered. Because we want to render a single
	triangle we want to specify a total of three vertices with each vertex having a 3D position.
	They are defined in normalized device coordinates in a float array (the visible region of
	OpenGL). Since it works in 3D space, we render a 2D triangle with each vertex having a z coordinate
	of 0.0. This way the depth of the triangle remains the same
	
	These NDC coordinates will then be transformed to screen-space coordinates via the 
	viewport transform, using data that was provided to the glViewport. The resulting screen-space
	coordinates are then transformed to fragtments as inputs to the fragment shader*/
	/*Set up vertex data (and buffers) and configure vertex attributes*/
	float vertices[] = {//Vertex data 
			0.5f,  0.5f, 0.0f,  // top right
			0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
	/*Vertex buffer object. Just like any object in OpenGL, this buffer has a unique ID 
	correspondring to that buffer. We generate on with a buffer ID, using glGenBuffers function:
	VBO holds information anout each vertex attribute. You can choose which VBO takes it's data
	from (has you can have more than one VBO). It's determined by the VBO vurently bound to 
	GL_ARRAY_BUFFER when calling glVertexAttibPointer. */
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	/*Bind the Vertex Array Object first, then bind and set the buffer(s), and then configure
	vertex attribute(s)*/
	glBindVertexArray(VAO);
	/*OpenGL has many types of buffer objects and the buffer type of a vertex buffer is
	GL_ARRAY_BUFFER. OpenGL allows us to bind several buffers at once as long as they are 
	a different buffer type. 
	We can bind the buffer to the GL_ARRAY_BUFFER target with the glBindBuffer function*/
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	/*From that point on any buffer calls we make (on the GL_ARRAY_BUFFER target) will be
	used to configure the currently bound buffer, which is VBO. Then we can make a call to the 
	glBufferData function that copies the previously defined vertex data into the buffer's memory.
	1) Its first argument is the type of buffer we want to copy data into, 2) the second argument
	specifies the size of the data (in bytes) we want to pass to the buffer, 3) the third parameter
	is the actual data we want to send, 4) the fourth argument specifies how we want the graphics
	card to manage the given data (this can take 3 forms)*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/*We have to specify what part of our input data goes to which vertex attributes in the
	vertex shader. This means we have to specify how OpenGL should interpret the 
	vertex data before rendering. 
	glVertexAttribPointer: full explanation is on the website.*/
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	/*You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO
	but this rarely happens. Modifying other VAOs requires a call to glBindVertexArray anyways
	so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.*/
	glBindVertexArray(0);
	
	 
	/*Viewport: Before we can start rendering we have to do one last thing. 
	We have to tell OpenGL the size of the rendering window so OpenGL knows 
	how we want to display data and coordinates with respect to the window. 
	We can set those dimensions via the glViewport function:*/
	/*The first two parameters of glViewport set the location of the lower left corner 
	of the window. The third and fourth parameter setthe width and height of the
	rendering window in pixels, which is set equal to GLFW's window size*/
	//glViewport(0, 0, 800, 600);
	

	/*We don't want the application to draw a single image and then immediately quit and close 
	the window. We want the application to keep drawing images and handling user input until
	the program has been explicitly told to stop. For this reasion, we have to create a while loop, 
	that we now call the render loop, that keeps on running until we tell GLFW to stop. 
	The following code shows a very simple render loop:*/

	/*The glfwWindowShouldClose function checks at the start of each loop iteration if GLFW 
	has been instructed to close. If so, the function returns true and the render loop stops 
	running, after which we close the application.
	
	glfwPollEvents: function checks if any events are triggered (like keyboard input or mouse
	movement events), updates the window state, and calls the corresponding functions (which 
	we canr register via callback methods).
	
	glfwSwapBuffers: will swap the color buffer (a large 2D buffer that contains color values
	for each pixel in GLFW's window) that is used to render to during this render iteration
	and show it as output to the screen.*/
	//Render loop
	while (!glfwWindowShouldClose(window)) {
		//We call this every iteration of the render loop and therefore it has to be here..
		//Input
		processInput(window); 
		
		/*Rendering commands can be put here in the render loop as we want it to execute each frame/iteration
		At the start of frame we want to clear the screen. Otherwise we would see the results from the 
		previous frame. This is done by using glClear where we pass in buffer bits to sepcify
		which buffer we would like to clear.
		We also specify the color to clear the screen with using glClearColor*/
		//Rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw our first triangle
		/*Draw our first triangle.
		Every shader and rendering call after glUseProgram will 
		now use this program object (and thus the shaders).*/
		glUseProgram(shaderProgram);
		/*Seeing as we only have a single VAO there's no need to bind it every time, but we'll
		do so to keep things a bit more organized*/
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//Check and call events and swap the buffers (keys pressed/released, mouse moved etc)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	/*De-Allocate all resources once they've outlived their purpose*/
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	/*As soon as we exit the render loop we would like to properly clean/delete all of GLFW's resources
	that were allocated. We do this by this function that is called at the end of the main function.
	This will clean up all the resources and properly exit the application.*/
	/*glfw: Terminate, clearling all previously allocated GLFW resources.*/
	glfwTerminate();
	return 0;
}

/*Process all input. 
windowShouldClose: is set to true, and when escape is pressed the program will close.
This gives us an easy way to check for specific key presses and react accordinly every frame.
An iteration of the render loop is more commonly called a frame.*/
/*Process all input : Query GLFW whether relevant keys are pressed / released this frame and react
accordingly*/
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

/*The moment a user resizes the window the viewport should be adjusted too.
This is a callback function that gets called each time the window is resized
This resize callback function has the following prototype:*/

/*The framebuffer size function takes a GLFWwindow as its first argument
and two integers indicating the new window dimensions. Whenever the window
changes in size, GLFW calls this function and fills in the proper arguments
for you to process*/

/*We do have to tell GLFW we want to call this function on every window resize
* by registering it:
* glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
*
*There are many callbacks functions we can set to register our own functions. For example,
* we can make a callback function to process joystick input changes, process error messages etc.
* We register the callback functions after we've created the window and before the
* render loop is initiated.
*/

/*glfw: Whenever the window size changed (by OS or user resize) this callback function executes*/
void framebuffer_size_callback(GLFWwindow * window,int width, int height) {
	glViewport(0, 0, width, height);
}
