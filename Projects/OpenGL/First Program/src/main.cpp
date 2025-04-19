#include "includes.hpp"

// Vertex Shader source code
const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// Fragment Shader source code
const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
    "}\n\0";

void setVersion();
GLFWwindow* createWindow();

struct Vertex
{
    GLfloat x, y, z;
};

int main(int argc, char* argv[])
{
    glfwInit();

    setVersion();

    Vertex verticies[] = {{-0.5f, -0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}, {0.0f, 0.5f, 0.0f}};

    GLFWwindow* window = createWindow();
    glfwMakeContextCurrent(window);  // Now we tell OpenGL we want to use the window.

    gladLoadGL();  // Load the config for OpenGL

    // Set the dimensions in which stuff should be drawn.
    glViewport(0, 0, 800, 800);

    // Create Vertex Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Create Shader Program
    GLuint ShaderProgram = glCreateProgram();
    glAttachShader(ShaderProgram, vertexShader);
    glAttachShader(ShaderProgram, fragmentShader);
    glLinkProgram(ShaderProgram);

    // Clean up shaders as they're no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set up vertex array and buffer objects
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Clear screen color (done only once before the loop)
    glClearColor(0.05f, 0.08f, 0.15f, 1.0f);  // Set the color.

    // Main rendering loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen with the new color.

        glUseProgram(ShaderProgram);  // Use the compiled shader program

        glBindVertexArray(VAO);  // Bind the VAO
        glDrawArrays(GL_TRIANGLES, 0, 3);  // Draw the triangle

        glfwSwapBuffers(window);  // Swap the back buffer to the front (show the color)
        glfwPollEvents();  // Process events
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwDestroyWindow(window);  // Destroy the window
    glfwTerminate();

    return 0;
}

void setVersion()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* createWindow()
{
    GLFWwindow* window = glfwCreateWindow(800, 800, "My Window", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cerr << "Window was unable to be created." << std::endl;
        glfwTerminate();
        return nullptr;
    }

    return window;
}
