#include <string>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include "shader.h"
#include "resourceloader.h"
#include "drawingmanager.h"
#include "statemachine.h"

std::shared_ptr <StateMachine> state_machine;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (action == GLFW_PRESS)
    {
        state_machine->keyboard_pressed(key);
    }
}

void mouse_callback ( GLFWwindow* window, int button, int action, int mode )
{
    if ( button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double x, y;
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glfwGetCursorPos ( window, &x, &y );
        double gl_x = 2 * x / width - 1;
        double gl_y = 2 * (height - y) / height - 1;
        state_machine->clicked(gl_x,gl_y);
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    int width = 1800, height = 720;

    GLFWwindow* window = glfwCreateWindow(width, height, "Slot", nullptr, nullptr);

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    Shader ourShader("shader/textures.vs", "shader/textures.frag");
    ourShader.Use();

    auto rl = std::make_shared <ResourceLoader>();
    rl->put("star", "textures/star_small_cr.png");
    rl->put("square", "textures/square_cr.png");
    rl->put("triangle", "textures/triangle_small_cr.png");
    rl->put("circle", "textures/circle_cr.png");
    rl->put("haste", "textures/haste.png");
    rl->put("start_active", "textures/start_active_cr.png");
    rl->put("stop_active", "textures/stop_cr.png");
    rl->put("background", "textures/background.png");
    rl->put("start_passive", "textures/start_passive_cr.png");
    rl->put("stop_passive", "textures/stop_passive_cr.png");
    rl->put("delay", "textures/delay.png");
    rl->put("pause", "textures/pause.png");
    rl->put("star_win", "textures/star_win.png");
    rl->put("circle_win", "textures/circle_win.png");
    rl->put("square_win", "textures/square_win.png");
    rl->put("triangle_win", "textures/triangle_win.png");
    auto scene_info = std::make_shared<SceneInfo>(width, height);
 /*   auto test_image = std::make_shared <Image>(rl->get("star"), scene_info);
    test_image->set_scale(0.3, 0.3);
    test_image->set_center(900, 300);*/

    auto drawing_manager = std::make_shared <DrawingManager>();
    state_machine = std::make_shared <StateMachine>(drawing_manager, rl, scene_info);
  //  drawing_manager->add(test_image);
    glfwSetMouseButtonCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);
 //   desk = std::make_shared<Desk>(rl, scene_info);
    double old_time = 0, now_time;

    glfwSetTime(0);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        now_time = glfwGetTime();
        state_machine->update(now_time-old_time);
        drawing_manager->draw();

    /*    tween_manager->update(now_time-old_time);
        tween_manager->remove_empty_queues();

        if (!desk->is_paused())
        {
            timer_manager->update(now_time-old_time);
            timer_manager->remove_empty_timers();
        }*/

        //desk->move(now_time-old_time);
        old_time = now_time;
        glfwSwapBuffers(window);
    }

    //glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
