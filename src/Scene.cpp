#include <Qt3DRender//QPointLight>

#include "Scene.h"

void Scene::addLight(const QVector3D & pos)
{
	auto * lightEntity = new Qt3DCore::QEntity(scene);
	auto * pointLight = new Qt3DRender::QPointLight(lightEntity);
	auto * lightTransform = new Qt3DCore::QTransform(scene);
	lightTransform->setTranslation(pos);
	
	lightEntity->addComponent(pointLight);
	lightEntity->addComponent(lightTransform);
}


/** *************************************************** PUBLIC ***************************************************** **/

Scene::Scene(Qt3DExtras::Qt3DWindow * view) :
		view{view},
		scene{new Qt3DCore::QEntity()},
		camera{view->camera()},
		cameraController{new Qt3DExtras::QOrbitCameraController(scene)}
{
	cameraController->setCamera(camera);
	view->setRootEntity(scene);
	
	addLight({50, 50, 100}); // передний
	addLight({-50, 50, -100}); // задний
	addLight({50, 100, 50}); // верхний
	addLight({50, -50, -100}); // нижний
	addLight({-100, 50, 50}); // левый
	addLight({100, 50, 50}); // правый
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

/// установка верхнего вектора камеры
void Scene::SetCameraUpVector(const QVector3D & upVector)
{
	camera->setUpVector(upVector);
}
