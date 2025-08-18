#pragma once
#include "utils/glIncludes.h"

enum class ProjectionMode {
	Perspective,
	Orthographic
};

struct ProjectionType {
	ProjectionMode mode;
	float fov = 45.0f;
	float aspect = 1.0f;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;
	float orthoWidth = 10.0f;
	float orthoHeight = 10.0f;
};


class Camera {

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw;
	float pitch;

	float movementSpeed;
	float mouseSensitivity;

	void updateCameraVectors();

public:

	Camera(
		glm::vec3 potision = glm::vec3(0.0f, 0.0f, 5.0f),
		glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = -90.0f,
		float pitch = 0.0f
	);

	ProjectionType projection;
	void setPerspective(float fov, float aspect, float nearPlane, float farPlane);
	void setOrthographic(float width, float height, float nearPlane, float farPlane);
	void setOrthographicFromPerspective(float distanceToTarget);

	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;

	void processKeyboardInput(int direction, float deltaTime);
	void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
	void processMouseScroll(float yoffset);

	glm::vec3 getPosition() const { return position; }
	glm::vec3 getFront() const { return front; }
	glm::vec3 getUp() const { return up; }
	void setPosition(const glm::vec3& pos) { position = pos; }

	enum CameraMovement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
};
