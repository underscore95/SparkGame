#include <Spark.h>

class TestSystem : public Spark::System {
public:
	void onUpdate(const float dt) override;

	void onRender() override;

};