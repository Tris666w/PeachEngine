#pragma once
#include <XInput.h>
#include "unordered_map"

namespace peach
{

	class Command;
	enum class ControllerButton
	{
		ButtonUp = 0x0001,
		ButtonDown = 0x0002,
		ButtonLeft = 0x0004,
		ButtonRight = 0x0008,

		ButtonStart = 0x0010,
		ButtonBack = 0x0020,

		ButtonLeftThumb = 0x0040,
		ButtonRightThumb = 0x0080,

		ButtonLeftShoulder = 0x0100,
		ButtonRightShoulder = 0x0200,

		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,


		Count
	};
	enum class CommandExecuteCause
	{
		ButtonPressed = 0,
		ButtonUp = 1,
		ButtonDown = 2
	};
	class InputManager final
	{
	public:
		InputManager();

		bool ProcessInput();
		[[nodiscard]] bool IsPressed(const ControllerButton button) const;
		[[nodiscard]] bool IsButtonUp(const ControllerButton button) const;
		[[nodiscard]] bool IsButtonDown(const ControllerButton button) const;

		[[nodiscard]] bool IsButtonUp(const int key) const;
		[[nodiscard]] bool IsButtonDown(const int key) const;

		void AddOrChangeCommand(ControllerButton button, const std::shared_ptr<Command>& pCommand, CommandExecuteCause executeCause);
		void AddOrChangeCommand(int keyboardKey, const std::shared_ptr<Command>& pCommand, CommandExecuteCause executeCause);

		void Init();
	private:

		XINPUT_STATE m_CurrentState{};

		std::unordered_map<ControllerButton, std::pair< std::shared_ptr<Command>, CommandExecuteCause>> m_ControllerUnorderedMap = {};
		std::vector<bool>m_IsButtonPressedVector = {};

		std::unordered_map<int, std::pair< std::shared_ptr<Command>, CommandExecuteCause>> m_KeyboardUnorderedMap = {};
		std::vector<bool>m_IsKeyPressedVector = {};

		//SEE SDLK.h for the key that are supported
		//WARNING:: Setting this too high, will make the program very heavy and init very long
		int const m_KeyBoardSupported;
	};
}
