#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

unsigned int frag_shader_init();

unsigned int vert_shader_init();

void init_window();


const int WIDTH = 800;
const int HEIGHT = 600;

GLFWwindow* window = 0;

int main()
{
    init_window();

    //Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);


    float vertices[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f
    };

    unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // Binds VBO which is currently GL_ARRAY_BUFFER bound
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    unsigned int vertexShader = vert_shader_init();
    unsigned int fragmentShader = frag_shader_init();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);




    // could be done every frame
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();


}

void init_window()
{
    int windw_init = glfwInit();
    if (!windw_init)
    {
        std::cout << "Failed to init window\n";
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    window = glfwCreateWindow(WIDTH, HEIGHT, "gl window", nullptr, nullptr);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

unsigned int frag_shader_init()
{
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 VertPos;\n"
"vec2 iterate(vec2 vect, vec2 c);\n"
"void main()\n"
"{\n"
"    vec2 mainvec = VertPos;\n"
"    float iteration = 0;\n"
"    while (length(mainvec) < 10.0 && iteration < 100)\n"
"    {\n"
"        iteration += 1.0;\n"
"        mainvec = iterate(mainvec, VertPos);\n"
"    }\n"
"    if (iteration > 99)\n"
"    {\n"
"        FragColor = vec4(0.0, 0.0, 0.0, 1.0);\n"
"    }\n"
"    else\n"
"    {\n"
"        FragColor = vec4(1.0 - iteration * 0.04, 1.0 - iteration * 0.04, 1.0, 1.0);\n"
"    }\n"
"}\n"
"vec2 iterate(vec2 vect, vec2 c)\n"
"{\n"
"    float real = vect.x;\n"
"    vect.x = vect.x * vect.x - vect.y * vect.y;\n"
"    vect.y = 2.0 * real * vect.y;\n"
"    vect = vect + c;\n"
"    return vect;\n"
"}\n";

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    int success;
    char infoLog[512];
    //Get shader compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
        infoLog << std::endl;
    }

    return fragmentShader;
}



unsigned int vert_shader_init()
{
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "out vec2 VertPos;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    " VertPos = vec2(aPos.x*2.0, aPos.y*2.0);\n"
    "}\0";

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Get shader compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
        infoLog << std::endl;
    }
    return vertexShader;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
