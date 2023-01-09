/*
Part of Newcastle University's Game Engineering source code.

Use as you see fit!

Comments and queries to: richard-gordon.davison AT ncl.ac.uk
https://research.ncl.ac.uk/game/
*/
#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Maths.h"

namespace NCL {
	using namespace NCL::Maths;
	enum class CameraType {
		Orthographic,
		Perspective
	};
	class Camera {
	public:
		Camera(void) = default;
		void SetBasicCameraParameters(float pitch, float yaw, const Vector3& position, float znear = 1.0f, float zfar = 100.0f);
		void SetPerspectiveCameraParameters(float aspect, float fov = 45.0f);
		void SetOrthographicCameraParameters(float right, float left, float top, float bottom);
		~Camera(void) = default;

		void UpdateCamera(float dt);
		
		//Builds a view matrix for the current camera variables, suitable for sending straight to a vertex shader (i.e it's already an 'inverse camera matrix').
		Matrix4 BuildViewMatrix() const;
		Matrix4 GenerateInverseView() const;

		virtual Matrix4 BuildProjectionMatrix() const;
		virtual Matrix4 GenerateInverseProjection() const;

		//Gets position in world space
		Vector3 GetPosition() const { return position; }
		
		////Gets yaw, in degrees
		//float	GetYaw()   const { return yaw; }
		//
		////Gets pitch, in degrees
		//float	GetPitch() const { return pitch; }
		
		//void CalculateZoom();
		//void CalculateAngleAroundPlayer();
		//float CalculateHorizontalDistanceFromPlayer();
		//float CalculateVerticalDistanceFromPlayer();
		//void CalculateThirdPersonCameraPosition(const Vector3& playerPosition, const Quaternion& playerOrientation, bool init = false);
	protected:
		float znear = 1.0f;
		float zfar = 100.0f;

		float aspect = 0.0f;
		float fov = 45.0f;

		float right = 0.0f;
		float left = 0.0f;
		float top = 0.0f;
		float bottom = 0.0f;

		float	yaw = 0.0f;
		float	pitch = 0.0f;
		Vector3 position;

		bool viewType = false;
		CameraType camType = CameraType::Perspective;

		float distanceFromPlayer = 10.0f;
		/*float angleAroundPlayer = 180.0f; */
	};
}