#pragma once

#include <Spark.h>
#include <memory>

class GameApp :
	public Spark::Application, public Spark::Events::EventListener {
private:
	std::shared_ptr<Spark::Window::Window> window;
	std::unique_ptr<Spark::Graphics::Renderer> renderer;
	std::shared_ptr<Spark::Graphics::ShaderProgram> shader;
	std::unique_ptr<Spark::Graphics::VertexArray> vertexArray;
	std::unique_ptr<Spark::Graphics::VertexArray> vertexArray2;
	std::shared_ptr<Spark::Graphics::Texture> textureCat;
	std::shared_ptr<Spark::Graphics::Texture> textureCroc;
	std::shared_ptr<Spark::Graphics::Camera> camera;
	std::shared_ptr<Spark::Graphics::Material> material;

public:
	GameApp();
	~GameApp();

	void onEvent(Spark::Events::EventContainer& event) const override;

	void update(const float dt) override;
	void render() override;
};