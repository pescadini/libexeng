
#include <xe/Application.hpp>
#include <xe/Timer.hpp>
#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/gfx/GraphicsManager.hpp>
#include <xe/gfx/Vertex.hpp>
#include <xe/gfx/Mesh.hpp>
#include <xe/gfx/MeshSubsetGeneratorPlane.hpp>
#include <xe/gfx/MeshSubsetGeneratorBox.hpp>
#include <xe/sg/Scene.hpp>
#include <xe/sg/Camera.hpp>

#include "fshader.hpp"
#include "vshader.hpp"
#include "SceneRenderer.hpp"
#include "RasterRenderer.hpp"

class PerspectiveCamera : public xe::sg::Camera {
public:
	virtual ~PerspectiveCamera() {}

	virtual xe::Matrix4f computeView() const {
		return xe::lookat(position, lookat, up);
		// return xe::identity<float, 4>();
	}

	virtual xe::Matrix4f computeProj() const {
		return xe::perspective(fov, aspect, znear, zfar);
		// return xe::identity<float, 4>();
	}

	virtual xe::Rectf getViewport() const override {
		return viewport;
	}

public:
	xe::Vector3f position = xe::Vector3f(0.0f, 1.5f, 3.5f);
	xe::Vector3f lookat = xe::Vector3f(0.0f, 0.0f, 0.0f);
	xe::Vector3f up = xe::Vector3f(0.0f, 1.0f, 0.0f);

	float fov = xe::rad(60.0f);
	float aspect = 1.3333f;
	float znear = 0.1f;
	float zfar = 100.0f;

	xe::Rectf viewport;
};

/**
 * Scene graph example
 */
class SceneApplication : public xe::Application {
public:
    xe::gfx::GraphicsDriverPtr createGraphicsDriver() {
        // display all available graphics drivers
        auto driverInfos = this->getGraphicsManager()->getAvailableDrivers();

        if (driverInfos.size() == 0) {
            std::cout << "No available graphics drivers!" << std::endl;
            throw std::runtime_error("");
        }
        
        // select the first graphics driver
        std::cout << "Available graphic drivers:" << std::endl;
        for (const auto &driverInfo : driverInfos) {
            std::cout << driverInfo.name << std::endl;
        }

        return this->getGraphicsManager()->createDriver(driverInfos[0]);
    }
    
    xe::gfx::MaterialFormat createMaterialFormat() {
        std::vector<xe::gfx::MaterialAttrib> attribs = {
            {"ambient"},
            {"diffuse"},
            {"specular"},
            {"emission"},
            {"shininess", xe::DataType::Float32, 1}
        };
        
        return xe::gfx::MaterialFormat(attribs);
    }
    
    xe::gfx::VertexFormat createVertexFormat() {
        return xe::gfx::StandardVertex::getFormat();
    }
    
    xe::gfx::MaterialPtr createMaterial() {
        auto material = std::make_unique<xe::gfx::Material>(&materialFormat);
        
		material->setAttribute("ambient", xe::Vector4f(1.0f, 1.0f, 0.0f, 1.0f));
		material->setAttribute("diffuse", xe::Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		material->setAttribute("specular", xe::Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		material->setAttribute("emission", xe::Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		material->setAttribute("shininess", 1.0f);

        return material;
    }
    
    xe::gfx::ShaderProgramPtr createProgram() {
		std::list<xe::gfx::ShaderSource> sources = {
			{xe::gfx::ShaderType::Vertex, vshader_src},
			{xe::gfx::ShaderType::Fragment, fshader_src}
		};

		auto modernModule = graphicsDriver->getModernModule();
		auto program = modernModule->createShaderProgram(sources);

		return program;
    }
    
    xe::gfx::MeshPtr createMesh() {
		xe::gfx::MeshSubsetGeneratorParams params;
		params.format = &vertexFormat;
		params.iformat = xe::gfx::IndexFormat::Index32;
		params.slices = 2;
		params.stacks = 2;

		xe::gfx::MeshSubsetGeneratorBox generator(this->graphicsDriver.get());

		auto subset = generator.generate(params);

		subset->setMaterial(material.get());

		return std::make_unique<xe::gfx::Mesh>(std::move(subset));
    }
    
	xe::sg::ScenePtr createScene() {
		auto scene = std::make_unique<xe::sg::Scene>();

		scene->setBackColor({0.0f, 0.0f, 8.0f, 1.0f});

		scene->getRootNode()->setRenderable(&camera);
		scene->getRootNode()->addChild("boxNode")->setRenderable(mesh.get());

		return scene;
	}

    void initialize() {
        graphicsDriver = this->createGraphicsDriver();
        graphicsDriver->initialize();
        shader = createProgram();
		graphicsDriver->getModernModule()->setShaderProgram(shader.get());

        vertexFormat = createVertexFormat();
        materialFormat = createMaterialFormat();
        
        material = createMaterial();
		mesh = createMesh();
		scene = createScene();

		renderer = std::make_unique<RasterRenderer>(graphicsDriver.get());
		sceneRenderer = std::make_unique<SceneRenderer>(renderer.get());
		sceneRenderer->setScene(scene.get());

		camera.viewport = xe::Rectf( xe::Vector2f(0.0f, 0.0f), xe::Vector2f(640.0f, 480.0f));
    }
    
    virtual int run(int argc, char **argv) override {
        
		this->initialize();

        inputManager = graphicsDriver->getInputManager();
        
        auto keyboardStatus = inputManager->getKeyboard()->getStatus();
        
        bool done = false;
        float angle = 0.0f;

		std::uint32_t lastTime = xe::Timer::getTime();

        while (!done) {
			float currentTime = (xe::Timer::getTime() - lastTime)/1000.0f;
			lastTime = xe::Timer::getTime();

            inputManager->poll();
			
            xe::Matrix4f model = xe::rotatey<float>(xe::rad(angle));

            done = keyboardStatus->isKeyPressed(xe::input2::KeyCode::KeyEsc);

			sceneRenderer->renderScene();
        }
        
        return 0;
    }
    
private:
    xe::input2::IInputManager *inputManager = nullptr;
  
	PerspectiveCamera camera;

    xe::gfx::GraphicsDriverPtr graphicsDriver;
    xe::gfx::VertexFormat vertexFormat;
    xe::gfx::MaterialFormat materialFormat;
    xe::gfx::MeshPtr mesh;
    xe::gfx::MaterialPtr material;
    xe::gfx::ShaderProgramPtr shader;

	xe::sg::ScenePtr scene;

	xe::sg::ISceneRendererPtr sceneRenderer;
	xe::sg::IRendererPtr renderer;
};

int main(int argc, char **argv) {
    return xe::Application::execute<SceneApplication>(argc, argv);
}