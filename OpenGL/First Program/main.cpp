#include "includes.hpp"  // Include necessary libraries and headers for OpenGL, GLFW, etc.

// Vertex Shader source code
const char* vertexShaderSource =
    "#version 330 core\n"                    // Specify the GLSL version (330 core is used for OpenGL 3.3)
    "layout (location = 0) in vec3 aPos;\n"  // The vertex position input (a 3D vector)
    "void main()\n"                          // Main function of the vertex shader
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"  // Set the final position of the vertex
    "}\0";                                                   // Null-terminate the string

// Fragment Shader source code
const char* fragmentShaderSource =
    "#version 330 core\n"    // Specify the GLSL version (330 core is used for OpenGL 3.3)
    "out vec4 FragColor;\n"  // Output color of the fragment (the pixel)
    "void main()\n"          // Main function of the fragment shader
    "{\n"
    "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"  // Set the color of the fragment (RGB + alpha)
    "}\n\0";                                           // Null-terminate the string

// Function declarations for later use
void setVersion();
GLFWwindow* createWindow();

// Define the structure to hold vertex data
struct Vertex
{
    GLfloat x, y, z;  // Coordinates of the vertex (x, y, z)
};

int main(int argc, char* argv[])
{
    glfwInit();  // Initialize the GLFW library, which is used to create the window and manage events

    setVersion();  // Set the OpenGL version to 3.3 (core profile)

    // Define the triangle vertices with x, y, and z coordinates
    Vertex verticies[] = {{-0.5f, -0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}, {0.0f, 0.5f, 0.0f}};

    GLFWwindow* window = createWindow();  // Create a window
    glfwMakeContextCurrent(window);       // Set the OpenGL context to the created window

    gladLoadGL();  // Load OpenGL functions using GLAD

    glViewport(0, 0, 800, 800);  // Set the viewport size (where OpenGL renders, in this case 800x800)

    // Create Shader Program
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);         // Create a new vertex shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);  // Load the source code for the vertex shader
    glCompileShader(vertexShader);                                  // Compile the vertex shader

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);         // Create a new fragment shader
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);  // Load the source code for the fragment shader
    glCompileShader(fragmentShader);                                    // Compile the fragment shader

    GLuint ShaderProgram = glCreateProgram();       // Create a new shader program
    glAttachShader(ShaderProgram, vertexShader);    // Attach the vertex shader to the program
    glAttachShader(ShaderProgram, fragmentShader);  // Attach the fragment shader to the program
    glLinkProgram(ShaderProgram);                   // Link the shaders into a complete program

    glDeleteShader(vertexShader);    // Delete the vertex shader (we no longer need it after linking)
    glDeleteShader(fragmentShader);  // Delete the fragment shader (we no longer need it after linking)

    // Set up vertex array and buffer objects to send data to the GPU
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);  // Generate a Vertex Array Object (VAO)
    glGenBuffers(1, &VBO);       // Generate a Vertex Buffer Object (VBO)

    glBindVertexArray(VAO);              // Bind the VAO to the current OpenGL context
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  // Bind the VBO to the current OpenGL context

    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);  // Upload the vertex data to the GPU

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);  // Define how the vertex data should be interpreted (location 0, 3 components per vertex, type float)
    glEnableVertexAttribArray(0);                                                  // Enable the vertex attribute at location 0

    glBindBuffer(GL_ARRAY_BUFFER, 0);  // Unbind the VBO
    glBindVertexArray(0);              // Unbind the VAO

    glClearColor(0.05f, 0.08f, 0.15f, 1.0f);  // Set the clear color for the window (dark blue)
    glClear(GL_COLOR_BUFFER_BIT);             // Clear the screen with the current clear color
    glfwSwapBuffers(window);                  // Swap the back buffer with the front buffer (to display the current frame)

    // Main loop: keep rendering until the window is closed
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.05f, 0.08f, 0.15f, 1.0f);  // Set the color to clear to (dark blue)
        glClear(GL_COLOR_BUFFER_BIT);             // Clear the screen

        glUseProgram(ShaderProgram);  // Use the shader program we created earlier
        glBindVertexArray(VAO);       // Bind the VAO (this tells OpenGL to use the vertex data we set up)

        glDrawArrays(GL_TRIANGLES, 0, 3);  // Draw the triangle using 3 vertices (starts at index 0, and we have 3 vertices total)

        glfwSwapBuffers(window);  // Swap the back buffer with the front buffer (to display the current frame)

        glfwPollEvents();  // Process any events (like keyboard or mouse input)
    }

    glDeleteVertexArrays(1, &VAO);  // Delete the VAO
    glDeleteBuffers(1, &VBO);       // Delete the VBO

    glfwDestroyWindow(window);  // Destroy the GLFW window
    glfwTerminate();            // Terminate the GLFW library

    return 0;  // Exit the program
}

// Set OpenGL version and profile
void setVersion()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // Set OpenGL major version to 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                  // Set OpenGL minor version to 3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Use OpenGL's core profile
}

// Create the window and check if it was successful
GLFWwindow* createWindow()
{
    GLFWwindow* window = glfwCreateWindow(800, 800, "My Window", nullptr, nullptr);  // Create a window with size 800x800

    if (window == nullptr)  // If the window was not created, print an error and terminate GLFW
    {
        std::cerr << "Window was unable to be created." << std::endl;
        glfwTerminate();
        return nullptr;
    }

    return window;  // Return the window if it was created successfully
}
