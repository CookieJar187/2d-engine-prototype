#include <iostream>

#include "scene.h"

#include "shader_loader.h"

Scene::Scene() {
    
    shader.id = make_shader(
        "src/shaders/vertex2.txt",
        "src/shaders/fragment2.txt"
    );
    shader.modelLoc = glGetUniformLocation(shader.id, "model");
    shader.projectionLoc = glGetUniformLocation(shader.id, "projection");

    material.shader = shader;

    obj1.mesh = &objMesh;
    obj1.material = &material;
    obj1.transform.scale = Vector2(100, 100);

    ground.mesh = &objMesh;
    ground.material = &material;
    ground.transform.position = Vector2(0, -150);
    ground.transform.scale = Vector2(300, 50);

    objects.push_back(obj1);
    objects.push_back(ground);

}

void Scene::draw(const glm::mat4& projection) const {
    for (const auto& child : objects) {
        child.draw(projection);
    }
}