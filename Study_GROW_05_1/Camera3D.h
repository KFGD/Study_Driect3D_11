#pragma once
#include "polyram.h"
#include "polyram_d3d11.h"

class Camera3D
{
private:
	PRVec3 moveUnit;
	float yaw, pitch, roll;
	bool isFlyingMode;
	PRVec3 camPos;

public:
	Camera3D() : yaw(0), pitch(0), roll(0), isFlyingMode(false) {}

	void strafe(float unit) { moveUnit.x += unit; }
	void fly(float unit) { moveUnit.y += unit; }
	void walk(float unit) { moveUnit.z += unit; }
	void setYaw(float unit) { yaw += unit; }
	void setPitch(float unit) { pitch += unit; }
	void setRoll(float unit) { roll += unit; }

	void setPos(PRVec3 _camPos) { camPos = _camPos; }
	PRVec3 getPos() { return camPos; }

	void getMatrix(PRMat* result) {
		PRVec3 tempVec;
		PRQuat q(yaw, isFlyingMode ? pitch : 0, 0);
		PRMat tempMat(q);
		PRVec3::transform(&moveUnit, &tempMat, &tempVec);
		camPos = camPos + tempVec;

		q = PRQuat(yaw, pitch, roll);
		tempMat = PRMat(q);

		PRVec3 target, upVec;
		PRVec3::transform(&PRVec3(0, 0, -1), &tempMat, &target);
		PRVec3::transform(&PRVec3(0, 1, 0), &tempMat, &upVec);

		PRVec3 t = target + camPos;
		PRMat::createLookAtLH(&camPos, &t, &upVec, result);
		moveUnit = PRVec3(0, 0, 0);
	}

	//~Camera3D();
};

