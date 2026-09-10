#include "scene.hpp"

void Scene::cleanupObjects()
{ objectManagement.cleanupObjects(); }

std::vector<Object *> Scene::getObjects()
{ return objectManagement.getObjects(); }

Object *Scene::getObjectByName(const std::string &targetName)
{ return objectManagement.getObjectByName(targetName); }

Object *Scene::createObject(const ObjectCreationData &data)
{ return objectManagement.createObject(data); }