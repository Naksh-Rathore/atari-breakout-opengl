#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include "game/game.h"

#include "init/init_gl.h"

void processInput(GLFWwindow *window, Game::Game& game);

int main() {
    
    GLFWwindow *window { Init::initOpenGL() };

    if (window == nullptr)
        return EXIT_FAILURE;

    Game::Game game;

    game.linkBall();
    game.linkPaddle();
    game.linkBrickMesh();
    game.linkBricks("level1.txt");

    game.setVPUniforms();

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window, game);

        game.drawAllObjects();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window, Game::Game& game) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    game.paddle().getKeyInput(window, 200.0f, -200.0f, game.deltaTime());
}
