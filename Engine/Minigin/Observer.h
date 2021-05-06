#pragma once
#include "Subject.h"
#include "GameObject.h"
namespace dae {
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const GameObject& GameObject, Event event) = 0;
	};
}
