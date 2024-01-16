#pragma once
/**
 *
 * @brief Observer header file
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

class Observer {
public:
    virtual void updateCamera(const glm::vec3& cameraPos, const glm::vec3& cameraFront, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) = 0;
    virtual void updatePointLight(int index, const glm::vec3& lightPos, const glm::vec3& lightColor, float Kc, float Kl, float Kq) = 0;
    virtual void updateDirLight(int index, const glm::vec3& lightDir, const glm::vec3& lightColor, float Kc, float Kl, float Kq) = 0;
    virtual void updateSpotlight(int index, const glm::vec3& lightPos, const glm::vec3& lightDir, float cutOff, float outerCutOff, const glm::vec3& lightColor, float Kc, float Kl, float Kq) = 0;
};