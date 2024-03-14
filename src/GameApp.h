#pragma once

#include <Spark.h>
#include <memory>

class GameApp :
	public Spark::Application, public Spark::Events::EventListener {
private:
	std::shared_ptr<Spark::Window::Window> window;
	std::unique_ptr<Spark::Graphics::Renderer> renderer;
	std::unique_ptr<Spark::Graphics::ShaderProgram> shader;
	std::unique_ptr<Spark::Graphics::VertexArray> vertexArray;
	std::unique_ptr<Spark::Graphics::Texture> texture;
	std::shared_ptr<Spark::Graphics::Camera> camera;

public:
	GameApp();
	~GameApp();

	void onEvent(Spark::Events::EventContainer& event) const override;

	void update(const float dt) override;
	void render() override;
};