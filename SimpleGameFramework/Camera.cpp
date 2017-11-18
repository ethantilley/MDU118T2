#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	type = "Cam"; 
}


Camera::~Camera()
{
}
void Camera::Save(std::ofstream & fs)
{
	GameObject::Save(fs);
}

void Camera::Load(std::ifstream & fs){
	GameObject::Load(fs);
}

void Camera::Update(double deltaTime)
{
}
