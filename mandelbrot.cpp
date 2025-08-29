#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "shaders.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void ProcessMouseClick(GLFWwindow* window, int button, int action, int mods);

void init_window();

const float REF_SIZE = 1000;

int WIDTH = 800;
int HEIGHT = 600;

float ZoomScale = 1.0;
float ZoomOffsetX = 0;
float ZoomOffsetY = 0;

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

    unsigned int vertexShader = GetShader("fullscreen_vertex", GL_VERTEX_SHADER);
    unsigned int fragmentShader = GetShader("MB_frag", GL_FRAGMENT_SHADER);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    int ZoomVarLocation = glGetUniformLocation(shaderProgram, "Zoom");

    // could be done every frame
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUniform4f(ZoomVarLocation, ZoomOffsetX, ZoomOffsetY,
                    ZoomScale * (WIDTH / REF_SIZE), ZoomScale * (HEIGHT / REF_SIZE));

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

    glfwSetMouseButtonCallback(window, ProcessMouseClick);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    WIDTH = width;
    HEIGHT = height;
}

void ProcessMouseClick(GLFWwindow* window, int button, int action, int mods)
{
    double posx = 0;
    double posy = 0;

    glfwGetCursorPos(window, &posx, &posy);

    posx = posx / WIDTH;
    posy = posy / HEIGHT;
    posy = 1.0 - posy;

    posx = 2 * posx - 1;
    posy = 2 * posy - 1;

    if (action == GLFW_PRESS)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT)
        {
            ZoomOffsetX += posx * ZoomScale * (WIDTH / REF_SIZE);
            ZoomOffsetY += posy * ZoomScale * (HEIGHT / REF_SIZE);
            ZoomScale *= 0.5f;
        }
        else if (button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            ZoomScale *= 2.0f;
        }
    }
}
