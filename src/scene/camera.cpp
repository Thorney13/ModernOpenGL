#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float yaw, float pitch)
	:   position(position),
		front(front),
		worldUp(up),
		yaw(yaw),
		pitch(pitch),
		movementSpeed(2.5f),
		mouseSensitivity(0.1f)
{
	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	front = glm::normalize(direction);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

void Camera::setPerspective(float fov, float aspect, float nearPlane, float farPlane)
{
	projection.mode = ProjectionMode::Perspective;
	projection.fov = fov;
	projection.aspect = aspect;
	projection.nearPlane = nearPlane;
	projection.farPlane = farPlane;
}

void Camera::setOrthographic(float width, float height, float nearPlane, float farPlane)
{
	projection.mode = ProjectionMode::Orthographic;
	projection.orthoWidth = width;
	projection.orthoHeight = height;
	projection.nearPlane = nearPlane;
	projection.farPlane = farPlane;
}

void Camera::setOrthographicFromPerspective(float distanceToTarget)
{
	if (projection.mode == ProjectionMode::Perspective) {
		// Calculate the visible height at the given distance based on FOV
		float visibleHeight = 2.0f * distanceToTarget * tan(projection.fov / 2.0f);
		float visibleWidth = visibleHeight * projection.aspect;

		// Switch to orthographic with the same visible area
		setOrthographic(visibleWidth, visibleHeight, projection.nearPlane, projection.farPlane);
	}
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix() const {
	switch (projection.mode) {
	case ProjectionMode::Perspective:
		return glm::perspective(glm::radians(projection.fov), projection.aspect, projection.nearPlane, projection.farPlane);
	case ProjectionMode::Orthographic:
		return glm::ortho(
			-projection.orthoWidth / 2.0f, projection.orthoWidth / 2.0f,
			-projection.orthoHeight / 2.0f, projection.orthoHeight / 2.0f,
			projection.nearPlane, projection.farPlane);
	default:
		return glm::mat4(1.0f);
	}
}

// Processes keyboard input for camera movement
void Camera::processKeyboardInput(int direction, float deltaTime) {
	float velocity = movementSpeed * deltaTime;

	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
	if (direction == UP)
		position += up * velocity;
	if (direction == DOWN)
		position -= up * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;
	yaw += xoffset;
	pitch += yoffset;
	if (constrainPitch) {
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}
	updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset) {
	projection.fov -= yoffset;
	if (projection.fov < 1.0f)
		projection.fov = 1.0f;
	if (projection.fov > 45.0f)
		projection.fov = 45.0f;
}
