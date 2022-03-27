#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// 自定义函数
void ProcessInput(GLFWwindow* window);

int main() {
    // 初始化glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建一个窗口对象
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (nullptr == window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 设置视口(Viewport)大小/设置窗口的维度(Dimension)
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // 注册窗口大小回调函数
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    // 定义顶点坐标
    float vertices[] = {
         0.5f,  0.5f, 0.0f,     // 右上角
         0.5f, -0.5f, 0.0f,     // 右下角
        -0.5f, -0.5f, 0.0f,     // 左下角
        -0.5f,  0.5f, 0.0f      // 左上角
    };

    // 定义索引坐标
    unsigned int indices[] = {
        0, 1, 3,    // 第一个三角形
        1, 2, 3     // 第二个三角形
    };

    // 生成顶点数组对象(Vertex Array Objects, VAO)
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);

    // 绑定VAO
    glBindVertexArray(VAO);

    // 生成顶点缓冲对象(Vertex Buffer Objects, VBO)
    unsigned int VBO = 0;
    glGenBuffers(1, &VBO);

    // 绑定缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // 绑定数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 链接顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 生成索引缓冲对象(Index Buffer Object,IBO/Element Buffer Object, EBO)
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    // 绑定数据
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 生成Shader对象
    Shader shader("res/shaders/VertexShader.glsl", "res/shaders/FragmentShader.glsl");

    // 激活程序对象
    shader.Use();

    // 线框模式（可选）
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // 渲染循环(Rnder Loop)
    while (!glfwWindowShouldClose(window)) {
        // 处理输入
        ProcessInput(window);

        // 渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 更新uniform颜色
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        shader.SetFloat4("ourColor", 0.0f, greenValue, 0.0f, 1.0f);

        // 绘制三角形
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // 检查并调用事件，交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    shader.Delete();

    // 释放资源
    glfwTerminate();
    return 0;
}

void ProcessInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
