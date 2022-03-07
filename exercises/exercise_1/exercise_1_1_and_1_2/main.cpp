#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


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

	/*This is a window object and holds all the windowing data that is 
	required by most of GLFW's other functions*/

	/*glfwCreateWindow function requires the window width and height as the first two 
	arguments. The third argument allows us to create a name for the window. 
	We can ignore the last two parameters. The function returns a 
	GLFWwindow objct that we'll later need for other GLFW operations.
	After that we tell GLFW to make the context of our window the main context
	on the current thread*/
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	/*GLAD manages function pointers for OpenGL and we want to initialize GLAD before
	we CALL any OpenGL function*/

	/*We pass GLAD the function to load the adress of the OpenGL function pointers
	which is OS-specific. GLWF gives us glfwGetProcAddress that defines the 
	correct function based on which OS we're compiling for.*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/*Viewport: Before we can start rendering we have to do one last thing. 
	We have to tell OpenGL the size of the rendering window so OpenGL knows 
	how we want to display data and coordinates with respect to the window. 
	We can set those dimensions via the glViewport function:*/

	/*The first two parameters of glViewport set the location of the lower left corner 
	of the window. The third and fourth parameter setthe width and height of the
	rendering window in pixels, which is set equal to GLFW's window size*/
	glViewport(0, 0, 800, 600);

	/*The moment a user resizes the window the viewport should be adjusted too.
	This is a callback function that gets called each time the window is resized
	This resize callback function has the following prototype:*/

	/*The framebuffer size function takes a GLFWwindow as its first argument
	and two integers indicating the new window dimensions. Whenever the window
	changes in size, GLFW calls this function and fills in the proper arguments 
	for you to process

	void framebuffer_size_callback(GLFWwindow * window,int width, int height) {
		glViewport(0, 0, width, height);
	}
	*/
	void framebuffer_size_callback(GLFWwindow * window, int width, int height);
	
	/*We do have to tell GLFW we want to call this function on every window resize
	* by registering it:
	* glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 
	* 
	*There are many callbacks functions we can set to register our own functions. For example,
	* we can make a callback function to process joystick input changes, process error messages etc. 
	* We register the callback functions after we've created the window and before the 
	* render loop is initiated. 
	*/

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

	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}














	return 0;
}