#include "PeachPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "Command.h"

peach::InputManager::InputManager()
	:m_KeyBoardSupported(SDLK_z)
{
}

bool peach::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		for (auto& [key, command] : m_KeyboardUnorderedMap)
		{
			if (key == e.key.keysym.sym)
			{
				if (command.second == CommandExecuteCause::ButtonPressed || command.second == CommandExecuteCause::ButtonDown && IsButtonDown(key))
					command.first->Execute();
				m_IsButtonPressedVector[static_cast<int>(key)] = true;
			}
			else
			{
				if (command.second == CommandExecuteCause::ButtonUp && IsButtonUp(key))
					command.first->Execute();
				m_IsButtonPressedVector[static_cast<int>(key)] = false;
			}
		}
	}

	//Loop over all Buttons in the unordered map and execute if appropriate
	for (auto& [button, command] : m_ControllerUnorderedMap)
	{
		if (IsPressed(button))
		{
			if (command.second == CommandExecuteCause::ButtonPressed || command.second == CommandExecuteCause::ButtonDown && IsButtonDown(button))
				command.first->Execute();
			m_IsButtonPressedVector[static_cast<int>(button)] = true;
		}
		else
		{
			if (command.second == CommandExecuteCause::ButtonUp && IsButtonUp(button))
				command.first->Execute();
			m_IsButtonPressedVector[static_cast<int>(button)] = false;
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
	if (!m_IsButtonPressedVector[static_cast<int>(button)])
	{
		return false;
	}
	return true;
}

bool peach::InputManager::IsButtonDown(const ControllerButton button) const
{
	if (m_IsButtonPressedVector[static_cast<int>(button)])
	{
		return false;
	}
	return true;
}

bool peach::InputManager::IsButtonUp(const int key) const
{
	if (!m_IsKeyPressedVector[key])
	{
		return false;
	}
	return true;
}

bool peach::InputManager::IsButtonDown(const int key) const
{
	if (m_IsKeyPressedVector[key])
	{
		return false;
	}
	return true;
}

void peach::InputManager::AddOrChangeCommand(const ControllerButton button, const std::shared_ptr<Command>& pCommand, CommandExecuteCause executeCause)
{
	std::pair<std::shared_ptr<Command>, CommandExecuteCause> pair = std::make_pair(pCommand, executeCause);
	m_ControllerUnorderedMap.insert_or_assign(button, pair);
}

void peach::InputManager::AddOrChangeCommand(int keyboardKey, const std::shared_ptr<Command>& pCommand,
	CommandExecuteCause executeCause)
{
	std::pair<std::shared_ptr<Command>, CommandExecuteCause> pair = std::make_pair(pCommand, executeCause);
	m_KeyboardUnorderedMap.insert_or_assign(keyboardKey, pair);
}

void peach::InputManager::Init()
{
	//Setup IsKeyPressed vector
	for (int index = 0; index < static_cast<int>(ControllerButton::Count); ++index)
		m_IsButtonPressedVector.push_back(false);

	for (int index = 0; index <= m_KeyBoardSupported; ++index)
		m_IsKeyPressedVector.push_back(false);
}


