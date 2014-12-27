

#include "SceneLoader.hpp"

#include <exeng/Vector.hpp>
#include <exeng/scenegraph/Mesh.hpp>
#include <exeng/graphics/Material.hpp>

namespace raytracer {
    using namespace exeng;
    using namespace exeng::scenegraph;
    using namespace exeng::graphics;
    
    SceneLoader::~SceneLoader() {}
    
    SceneLoader::SceneLoader(GraphicsDriver *driver_, MeshManager *meshManager_) : graphicsDriver(driver_), meshManager(meshManager_) {
    }
    
    // For now, just create a simple scene, boxed scene.
    std::unique_ptr<Scene> SceneLoader::loadScene(const std::string &filename) {
        // empty object
        auto scene = std::unique_ptr<Scene>(new Scene());

		this->addBoxNode ( 
			scene.get(), "boxNode", 
			"boxMaterial", {1.0f, 0.3f, 0.2f, 1.0f},
			"boxMesh1", {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}
		);

        return scene;
    }

	SceneNode* SceneLoader::addBoxNode(
		Scene *scene, const std::string &boxNodeName, 
		const std::string &materialName, const Vector4f &materialColor, 
		const std::string &boxMeshName, const Vector3f &boxCenter, const Vector3f &boxSize) 
	{
		// box material
        Material *boxMaterial = scene->createMaterial(materialName);
        boxMaterial->setProperty("diffuse", materialColor);

        // box mesh
        // Mesh *boxMesh = this->meshManager->getMesh("/cube", this->graphicsDriver);
		Mesh *boxMesh = this->meshManager->generateBoxMesh(boxMeshName, this->graphicsDriver, boxCenter, boxSize);
        boxMesh->getMeshSubset(0)->setMaterial(boxMaterial);

        // box scenenode
        scene->getRootNode()->addChild(boxNodeName)->setData(boxMesh);

		return scene->getRootNode()->getChild(boxNodeName);
	}
}
