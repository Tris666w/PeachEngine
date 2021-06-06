#pragma once
#include "Scene.h"
namespace Qbert
{
	class QbertScene final :public peach::Scene
	{
	public:
		QbertScene();

	protected:
		void Initialize() override;
	private:

	};
}