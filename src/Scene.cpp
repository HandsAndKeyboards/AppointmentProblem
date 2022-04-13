#include "Scene.h"

/** *************************************************** PUBLIC ***************************************************** **/

Scene::Scene(Qt3DExtras::Qt3DWindow * view) :
		view{view},
		scene{new Qt3DCore::QEntity()},
		camera{view->camera()},
		cameraController{new Qt3DExtras::QOrbitCameraController(scene)}
{
	cameraController->setCamera(camera);
	view->setRootEntity(scene);
}

Scene::~Scene()
{
	// scene, camera и cameraController уничтожаются при уничтожении view
	view.clear();
}

/**
 * @brief установка перспективной проекции
 * @param fieldOfView угол обзора в градусах
 * @param aspect соотношение сторон
 * @param nearPlane ближняя плоскость обзора
 * @param farPlane дальняя плоскость обзора
 */
void Scene::SetCameraPerspectiveProjection(float fieldOfView, float aspect, float nearPlane, float farPlane)
{
	camera->lens()->setPerspectiveProjection(
			fieldOfView,
			aspect,
			nearPlane,
			farPlane
	);
}

/// установка позиции камеры
void Scene::SetCameraPosition(const QVector3D & position)
{
	camera->setPosition(position);
}

/// установка центра обзора камеры
void Scene::SetCameraViewCenter(const QVector3D & viewCenter)
{
	camera->setViewCenter(viewCenter);
}

/// установка скорости вращения камеры
void Scene::SetCameraLookSpeed(float cameraLookSpeed)
{
	cameraController->setLookSpeed(cameraLookSpeed);
}

/// установка скорости движения камеры
void Scene::SetCameraLinearSpeed(float cameraLinearSpeed)
{
	cameraController->setLinearSpeed(cameraLinearSpeed);
}
