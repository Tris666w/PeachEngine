#pragma once

namespace peach
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;

	};
}