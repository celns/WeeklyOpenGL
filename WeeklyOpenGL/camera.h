#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

#include <vector>

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.f;
const float PITCH = 0.f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
    Camera();
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    glm::mat4 GetViewMatri();
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float yoffset);

private:
    void updateCameraVectors();

public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
};

#endif // CAMERA_H
