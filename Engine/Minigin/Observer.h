#pragma once
#include "Subject.h"
#include "GameObject.h"
namespace peach {
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const GameObject& GameObject, Event event) = 0;
	};
}
