#include "Camera.h"

Camera::Camera(GLFWwindow* window, glm::vec3 default_position, glm::vec3 default_front, glm::vec3 default_up, float default_yaw, float default_pitch)
{
    this->viewed_window = window;
    this->position = default_position;
    this->front = default_front;
    this->up = default_up;
    this->yaw = default_yaw;
    this->pitch = default_pitch;
    this->width = 1200;
    this->height = 1000;
}

void Camera::notifyObservers(int index)
{
    if (this->spotLight != nullptr) {
        this->spotLight->SetPosition(this->position);
        this->spotLight->SetDirection(this->front);
    }
    
    for (Observer* observer : observers) {
        observer->updateCamera(this->position, this->front, getViewMatrix(), getProjectionMatrix());
    }
}

void Camera::setWidthHeight(int width, int height) {
    this->width = width;
    this->height = height;
}

void Camera::moveCamera(float deltaTime)
{
    const float cameraSpeed = 3.0f * deltaTime;
    if (glfwGetKey(this->viewed_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(this->viewed_window, true);
        notifyObservers(-1);
    }
    if (glfwGetKey(this->viewed_window, GLFW_KEY_W) == GLFW_PRESS) {
        this->position += cameraSpeed * this->front;
        notifyObservers(-1);
    }
    if (glfwGetKey(this->viewed_window, GLFW_KEY_S) == GLFW_PRESS) {
        this->position -= cameraSpeed * this->front;
        notifyObservers(-1);
    }
        
    if (glfwGetKey(this->viewed_window, GLFW_KEY_A) == GLFW_PRESS) {
        this->position -= glm::normalize(glm::cross(this->front, this->up)) * cameraSpeed;
        notifyObservers(-1);
    }
    if (glfwGetKey(this->viewed_window, GLFW_KEY_D) == GLFW_PRESS) {
        this->position += glm::normalize(glm::cross(this->front, this->up)) * cameraSpeed;
        notifyObservers(-1);
    }
}

void Camera::controlCameraWithMouse(float xpos, float ypos)
{
    if (this->first_time_mouse)
    {
        lastX = xpos;
        lastY = ypos;
        this->first_time_mouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    this->yaw += xoffset;
    this->pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(direction);

    notifyObservers(-1);
}

float Camera::getLastX()
{
    return this->lastX;
}

float Camera::getLastY()
{
    return lastY;
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix()
{
    return glm::perspective(glm::radians(70.f), width / height, 0.1f, 100.f);

}

void Camera::SetSpotlight(Spotlight* sp)
{
    this->spotLight = sp;
}
