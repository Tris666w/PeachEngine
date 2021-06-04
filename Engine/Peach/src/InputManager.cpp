#include "PeachPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "Command.h"

bool peach::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}

	//Loop over all Buttons in the unordered map and execute if appropriate
	for (auto& [button, command] : m_CommandMap)
	{
		if (IsPressed(button))
		{
			if (command.second == CommandExecuteCause::ButtonPressed || command.second == CommandExecuteCause::ButtonDown && IsButtonDown(button))
				command.first->Execute();
			m_IsKeyPressedVector[static_cast<int>(button)] = true;
		}
		else
		{
			if (command.second == CommandExecuteCause::ButtonUp && IsButtonUp(button))
				command.first->Execute();
			m_IsKeyPressedVector[static_cast<int>(button)] = false;
		}
	}

	return true;
}

bool peach::InputManager::IsPressed(ControllerButton button) const
{
	return (m_CurrentState.Gamepad.wButtons & static_cast<WORD> (button)) != 0;
}

bool peach::InputManager::IsButtonUp(const ControllerButton button) const
{
	if (!m_IsKeyPressedVector[static_cast<int>(button)])
	{
		return false;
	}
	return true;
}

bool peach::InputManager::IsButtonDown(const ControllerButton button) const
{
	if (m_IsKeyPressedVector[static_cast<int>(button)])
	{
		return false;
	}
	return true;
}

void peach::InputManager::AddOrChangeCommand(const ControllerButton button, const std::shared_ptr<Command>& pCommand, CommandExecuteCause executeCause)
{
	std::pair<std::shared_ptr<Command>, CommandExecuteCause> pair = std::make_pair(pCommand, executeCause);
	m_CommandMap.insert_or_assign(button, pair);
}

void peach::InputManager::Init()
{
	//Setup IsKeyPressed vector
	for (int index = 0; index < static_cast<int>(ControllerButton::Count); ++index)
		m_IsKeyPressedVector.push_back(false);
}


