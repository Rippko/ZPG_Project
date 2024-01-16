#pragma once
/**
 *
 * @brief Camera header file
 *
 * @author Adam Fiury
 *
 * @year 2023
 **/
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ObservableObject.h"
#include "Spotlight.h"

class Camera : public ObservableObject {
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float yaw;
    float pitch;
    float lastX = 600, lastY = 500;
    bool first_time_mouse = true;
    GLFWwindow* viewed_window;
    float width;
    float height;
    Spotlight* spotLight;
public:
    Camera(GLFWwindow* window, glm::vec3 default_position = glm::vec3(0.0f, 4.0f, 3.0f),
          glm::vec3 default_front = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 default_up = glm::vec3(0.0f, 1.0f, 0.0f),
          float default_yaw = 0.0f, float default_pitch = 0.0f);
    void notifyObservers(int index) override;
    void setWidthHeight(int width, int height);
    void moveCamera(float deltaTime);
    void controlCameraWithMouse(float xoffset, float yoffset);
    float getLastX();
    float getLastY();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    void SetSpotlight(Spotlight* sp);
};
