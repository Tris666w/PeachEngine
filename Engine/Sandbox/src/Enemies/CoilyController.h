#pragma once
#include "ComponentBase.h"

namespace Qbert
{
	class CoilyController : public peach::ComponentBase
	{
	public:
		void Initialize()override;
		void Update() override;
		void Render()const override;

	private:

	};


}
