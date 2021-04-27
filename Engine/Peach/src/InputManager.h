#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "unordered_map"
#include <memory>

class Command;
namespace peach
{

	enum class ControllerButton
	{
		ButtonUp = 0,
		ButtonDown = 1,
		ButtonLeft = 2,
		ButtonRight = 3,
		
		ButtonStart = 4,
		ButtonBack = 5,
		
		ButtonLeftThumb = 6,
		ButtonRightThumb = 7,
		
		ButtonLeftShoulder = 8,
		ButtonRightShoulder = 9,
		
		ButtonA = 10,
		ButtonB = 11,
		ButtonX = 12,
		ButtonY = 13,


		Count
	};
		enum class CommandExecuteCause
	{
		ButtonPressed = 0,
		ButtonUp = 1,
		ButtonDown = 2
	};
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		[[nodiscard]] bool IsPressed(const ControllerButton button) const;
		[[nodiscard]] bool IsButtonUp(const ControllerButton button) const;
		[[nodiscard]] bool IsButtonDown(const ControllerButton button) const;

		void AddOrChangeCommand(ControllerButton button, const std::shared_ptr<Command>& pCommand, CommandExecuteCause executeCause);

		void Init();
	private:

		XINPUT_STATE m_CurrentState{};
		
		std::unordered_map<ControllerButton,std::pair< std::shared_ptr<Command>,CommandExecuteCause>> m_CommandMap = {};
		std::vector<bool>m_IsKeyPressedVector = {};
	};
}
