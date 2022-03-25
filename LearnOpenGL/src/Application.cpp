#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// �Զ��庯��
void ProcessInput(GLFWwindow* window);

int main() {
    // ��ʼ��glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ����һ�����ڶ���
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
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
    glViewport(0, 0, 800, 800);

    // ע�ᴰ�ڴ�С�ص�����
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    // ��Ⱦѭ��(Rnder Loop)
    while (!glfwWindowShouldClose(window)) {
        // ��������
        ProcessInput(window);

        // ��Ⱦָ��
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ��鲢�����¼�����������
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // �ͷ���Դ
    glfwTerminate();
    return 0;
}

void ProcessInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
