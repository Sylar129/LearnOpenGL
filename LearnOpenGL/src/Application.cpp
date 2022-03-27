#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// �Զ��庯��
void ProcessInput(GLFWwindow* window);

int main() {
    // ��ʼ��glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ����һ�����ڶ���
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (nullptr == window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // ��ʼ��GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // �����ӿ�(Viewport)��С/���ô��ڵ�ά��(Dimension)
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // ע�ᴰ�ڴ�С�ص�����
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    // ���嶥������
    float vertices[] = {
         0.5f,  0.5f, 0.0f,     // ���Ͻ�
         0.5f, -0.5f, 0.0f,     // ���½�
        -0.5f, -0.5f, 0.0f,     // ���½�
        -0.5f,  0.5f, 0.0f      // ���Ͻ�
    };

    // ������������
    unsigned int indices[] = {
        0, 1, 3,    // ��һ��������
        1, 2, 3     // �ڶ���������
    };

    // ���ɶ����������(Vertex Array Objects, VAO)
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);

    // ��VAO
    glBindVertexArray(VAO);

    // ���ɶ��㻺�����(Vertex Buffer Objects, VBO)
    unsigned int VBO = 0;
    glGenBuffers(1, &VBO);

    // �󶨻������
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // ������
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // ���Ӷ�������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ���������������(Index Buffer Object,IBO/Element Buffer Object, EBO)
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    // ������
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // ����Shader����
    Shader shader("res/shaders/VertexShader.glsl", "res/shaders/FragmentShader.glsl");

    // ����������
    shader.Use();

    // �߿�ģʽ����ѡ��
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // ��Ⱦѭ��(Rnder Loop)
    while (!glfwWindowShouldClose(window)) {
        // ��������
        ProcessInput(window);

        // ��Ⱦָ��
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ����uniform��ɫ
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        shader.SetFloat4("ourColor", 0.0f, greenValue, 0.0f, 1.0f);

        // ����������
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // ��鲢�����¼�����������
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    shader.Delete();

    // �ͷ���Դ
    glfwTerminate();
    return 0;
}

void ProcessInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
