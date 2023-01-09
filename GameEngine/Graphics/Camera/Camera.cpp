#include "Camera.h"
#include "Window.h"
#include <algorithm>
#include <math.h>

using namespace NCL;
void Camera::SetBasicCameraParameters(float pitch, float yaw, const Vector3& position, float znear, float zfar) {
	this->pitch = pitch;
	this->yaw = yaw;
	this->position = position;
	this->znear = znear;
	this->zfar = zfar;
}
void Camera::SetPerspectiveCameraParameters(float aspect, float fov) {
	this->znear = znear;
	this->zfar = zfar;
	this->aspect = aspect;
	this->fov = fov;
	camType = CameraType::Perspective;
}
void Camera::SetOrthographicCameraParameters(float right, float left, float top, float bottom) {
	this->right = right;
	this->left = left;
	this->top = top;
	this->bottom = bottom;
	camType = CameraType::Orthographic;
}
/*
Polls the camera for keyboard / mouse movement.
Should be done once per frame! Pass it the msec since
last frame (default value is for simplicities sake...)
*/
void Camera::UpdateCamera(float dt) {
	//Update the mouse by how much
	pitch	-= (Window::GetMouse()->GetRelativePosition().y);

	//Bounds check the pitch, to be between straight up and straight down ;)
	pitch = std::min(pitch, 90.0f);
	pitch = std::max(pitch, -90.0f);

	//CalculateZoom();
	//CalculateAngleAroundPlayer();
}

/*
Generates a view matrix for the camera's viewpoint. This matrix can be sent
straight to the shader...it's already an 'inverse camera' matrix.
*/
Matrix4 Camera::BuildViewMatrix() const {
	//Why do a complicated matrix inversion, when we can just generate the matrix
	//using the negative values ;). The matrix multiplication order is important!
	return	Matrix4::Translation(-Vector3(0, 0, distanceFromPlayer)) *
		Matrix4::Rotation(-pitch, Vector3(1, 0, 0)) *
		Matrix4::Rotation(-yaw, Vector3(0, 1, 0)) *
		Matrix4::Translation(-position);
}

/*
And here's how we generate an inverse view matrix. It's pretty much
an exact inversion of the BuildViewMatrix function of the Camera class!
*/
Matrix4 Camera::GenerateInverseView() const {
	Matrix4 iview =
		Matrix4::Translation(position) *
		Matrix4::Rotation(yaw, Vector3(0, 1, 0)) *
		Matrix4::Rotation(pitch, Vector3(1, 0, 0));

	return iview;
}
Matrix4 Camera::BuildProjectionMatrix() const {
	if (camType == CameraType::Orthographic) {
		return Matrix4::Orthographic(left, right, bottom, top, znear, zfar);
	}
	else if (camType == CameraType::Perspective) {
		return Matrix4::Perspective(znear, zfar, aspect, fov);
	}
}
Matrix4 Camera::GenerateInverseProjection() const
{
	Matrix4 m;

	float t = tan(fov * PI_OVER_360);

	float neg_depth = znear - zfar;

	const float h = 1.0f / t;

	float c = (zfar + znear) / neg_depth;
	float e = -1.0f;
	float d = 2.0f * (znear * zfar) / neg_depth;

	m.array[0][0] = aspect / h;
	m.array[1][1] = tan(fov * PI_OVER_360);
	m.array[2][2] = 0.0f;

	m.array[2][3] = 1.0f / d;

	m.array[3][2] = 1.0f / e;
	m.array[3][3] = -c / (d * e);

	return m;
}
;

//
//void NCL::Camera::CalculateZoom() {
//	float zoomLevel = Window::GetMouse()->GetWheelMovement() * 0.1f;
//	distanceFromPlayer -= zoomLevel;
//}
//
//void NCL::Camera::CalculateAngleAroundPlayer() {
//	angleAroundPlayer -= Window::GetMouse()->GetRelativePosition().x;
//}
//
//float NCL::Camera::CalculateHorizontalDistanceFromPlayer() {
//	return distanceFromPlayer * cos(Maths::DegreesToRadians(pitch));
//}
//
//float NCL::Camera::CalculateVerticalDistanceFromPlayer() {
//	return distanceFromPlayer * sin(Maths::DegreesToRadians(pitch));
//}
//
//void NCL::Camera::CalculateThirdPersonCameraPosition(const Vector3& playerPosition, const Quaternion& playerOrientation, bool init) {
//	float vDist = CalculateVerticalDistanceFromPlayer();
//	float hDist = CalculateHorizontalDistanceFromPlayer();
//
//	float theta = Maths::DegreesToRadians(playerOrientation.ToEuler().y + angleAroundPlayer);
//	float xOffset = hDist * sin(theta);
//	float zOffset = hDist * cos(theta);
//
//	position.x = playerPosition.x - xOffset;
//	position.z = playerPosition.z - zOffset;
//	position.y = playerPosition.y + vDist + 14;
//
//	Vector3 lockedOffset = Vector3(0, 14, distanceFromPlayer);	
//
//	Matrix4 temp = Matrix4::BuildViewMatrix(position, playerPosition, Vector3(0, 1, 0));
//
//	Matrix4 modelMat = temp.Inverse();
//
//	Quaternion q(modelMat);
//	Vector3 angles = q.ToEuler(); 
//	if (init) SetPitch(angles.x);
//	SetYaw(angles.y);
//}
