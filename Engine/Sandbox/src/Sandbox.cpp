#include <Peach.h>

class Sandbox final : public peach::Application
{
public:
	Sandbox()
	{
		
	}
	~Sandbox() override
	{
		
	}


	void LoadGame() const override;
private:
	
};

peach::Application* peach::CreateApplication()
{
	return new Sandbox();
}
void Sandbox::LoadGame() const
{
	printf("Yoink\n");
}

