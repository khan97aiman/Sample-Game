#pragma once
#include "Camera.h"

namespace NCL {
	class PerspectiveCamera : public Camera {
	public:
		PerspectiveCamera(float pitch, float yaw, Vector3 position) : Camera(pitch, yaw, position) {}
		PerspectiveCamera(float pitch, float yaw, Vector3 position, float znear, float zfar, float aspect, float fov) : Camera(pitch, yaw, position) {
			this->znear = znear;
			this->zfar = zfar;
			this->aspect = aspect;
			this->fov = fov;
		};
		virtual ~PerspectiveCamera(void) {};
		virtual Matrix4 BuildProjectionMatrix() { return Matrix4::Perspective(znear, zfar, aspect, fov); }
		virtual Matrix4 GenerateInverseProjection() {
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
	protected:
		float aspect = 0.0f;
		float fov = 0.0f;
	};
};
