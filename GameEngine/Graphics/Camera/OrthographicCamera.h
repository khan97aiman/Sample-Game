#pragma once
#include "Camera.h"

namespace NCL {
	class OrthographicCamera : public Camera {
	public:
		OrthographicCamera(float pitch, float yaw, Vector3 position) : Camera(pitch, yaw, position) {}
		OrthographicCamera(float pitch, float yaw, Vector3 position, float znear, float zfar, float right, float left, float top, float bottom) : Camera(pitch, yaw, position) {
			this->znear = znear;
			this->zfar = zfar;
			this->right = right;
			this->left = left;
			this->top = top;
			this->bottom = bottom;
		};
		virtual ~OrthographicCamera(void) {};
		virtual Matrix4 BuildProjectionMatrix() { return Matrix4::Orthographic(znear, zfar, right, left, top, bottom); }
		virtual Matrix4 GenerateInverseProjection() {
			Matrix4 m;

			return m;
		}
	protected:
		float right = 0.0f;
		float left = 0.0f;
		float top = 0.0f;
		float bottom = 0.0f;
	};
}
