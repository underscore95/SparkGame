#include "GameApp.h"
#include "TestComponent.h"
#include "TestSystem.h"

GameApp::GameApp() : EventListener(Spark::Events::EventType::WindowResize)
{
	// TEST LOGGING
	Spark::Logging::registerLogger(std::make_unique<Spark::Logging::Logger>(Spark::Logging::LogLevel::INFO, "game"));
	auto& logger = Spark::Logging::getLogger("game");

	// TEST WINDOW
	window = Spark::Window::create("My Spark Game");

	if (!window->isSuccessfullyInitialised()) {
		logger.severe("Failed to init window");
	}

	// TEST ENTITIES
	auto entity = Spark::Entity::addEntity();
	logger.info("entity id: " + std::to_string(entity));

	Spark::Entity::removeEntity(entity);
	//logger.info("a after delete: " + testPointer->a); // Attempt to access dangling pointer

	// TEST SYSTEMS
	Spark::registerSystem(std::make_unique<TestSystem>());

	// TEST CAMERA
	//camera = Spark::Graphics::ortho(0.0f, 1.6f, 0.9f, 0.0f);

	camera = Spark::Graphics::perspective(glm::radians(75.0f), glm::vec2(1280.0f, 720.0f));
	//camera->setPerspectiveProjection(glm::radians(75.0f), glm::vec2(1280, 720));
	//camera->setPosition(glm::vec3(0, 0, 10));
	//camera->setRotationInDegrees(glm::vec3(0, 0, 20));
	//camera->setRotationInDegrees(glm::vec3(0, 20.0, 100.0));

	camera->setCameraController(std::make_unique<Spark::Graphics::KeyboardCameraController>(camera, window->getUserInput(), 10.0f, 2.5f));

	camera->linkWindow(window);

	// TEST RENDERER
	renderer = Spark::Graphics::createRenderer(window, camera);

	// Shaders
	auto vertexShader = Spark::Graphics::createVertexShader("resources/shaders/test.vert");
	auto fragShader = Spark::Graphics::createFragmentShader("resources/shaders/test.frag");

	std::vector<Spark::Graphics::Shader> shaders = { *vertexShader, *fragShader };
	shader = Spark::Graphics::createShaderProgram(shaders);

	// Vertex Buffer Layout
	std::shared_ptr<Spark::Graphics::VertexBufferLayout> layout = Spark::Graphics::createVertexBufferLayout();
	layout->pushFloat(3); // Position Coordinates
	layout->pushFloat(2); // Texture Coordinates

	// Vertex Buffer
	const size_t VERTEX_COUNT = 4;
	constexpr float z = -1.0f;
	const float* vertices = new float[] {
		-0.5f, -0.5f, z, 0.0f, 0.0f,
			0.5f, -0.5f, z, 1.0f, 0.0f,
			0.5f, 0.5f, z, 1.0f, 1.0f,
			-0.5f, 0.5f, z, 0.0f, 1.0f,
		};

	std::unique_ptr<Spark::Graphics::VertexBuffer> vertexBuffer =
		Spark::Graphics::createVertexBuffer(VERTEX_COUNT * layout->getStride(), vertices);

	// Vertex Buffer 2
	const float* vertices2 = new float[] {
		-0.5f, -2.5f, z, 0.0f, 0.0f,
			0.5f, -2.5f, z, 1.0f, 0.0f,
			0.5f, -1.5f, z, 1.0f, 1.0f,
			-0.5f, -1.5f, z, 0.0f, 1.0f
		};

	std::unique_ptr<Spark::Graphics::VertexBuffer> vertexBuffer2 =
		Spark::Graphics::createVertexBuffer(VERTEX_COUNT * layout->getStride(), vertices2);

	// Index Buffer
	const size_t INDICES_COUNT = 6;
	const unsigned int* indices = new unsigned int[] {
		0, 1, 2,
			2, 3, 0
		};

	std::shared_ptr<Spark::Graphics::IndexBuffer> indexBuffer = Spark::Graphics::createIndexBuffer(sizeof(unsigned int) * INDICES_COUNT, INDICES_COUNT, indices);

	// Vertex Array
	vertexArray = Spark::Graphics::createVertexArray(indexBuffer, std::move(vertexBuffer), layout);
	vertexArray2 = Spark::Graphics::createVertexArray(indexBuffer, std::move(vertexBuffer2), layout);

	// Textures
	textureCat = Spark::Graphics::loadTexture("resources/textures/cat.png");
	textureCroc = Spark::Graphics::loadTexture("resources/textures/croc.png");

	// Materials
	material = std::make_unique<Spark::Graphics::Material>(shader);
	material->withTexture(textureCat, 0);
	material->withTexture(textureCroc, 1);
}

GameApp::~GameApp()
{
}

void GameApp::onEvent(Spark::Events::EventContainer& event) const
{
	//std::cout << "Window Resized, width: " << window->getDimensions().x << ", height: " << window->getDimensions().y << "\n";
}

void GameApp::update(const float dt)
{
	auto& logger = Spark::Logging::getLogger("game");

	window->update();

	if (!window->isWindowOpen()) {
		stop();
	}
}

void GameApp::render()
{
	//Spark::Graphics::getMVP().setProj(glm::ortho(0.0f, (float)window->getDimensions().x, 0.0f, (float)window->getDimensions().y, -1.0f, 1.0f));

	renderer->startDrawing(material);

	// crocTexture is a uniform int that I use to determine which sampler2d to use
	shader->setUniform1i("crocTexture", false);
	renderer->draw(*vertexArray);

	shader->setUniform1i("crocTexture", true);
	renderer->draw(*vertexArray2);

	window->swapBuffers();

	renderer->stopDrawing();
}
