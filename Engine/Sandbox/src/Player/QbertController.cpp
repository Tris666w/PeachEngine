#include "QbertPCH.h"

#include "QbertController.h"
#include "InputManager.h"
#include "Commands/MoveCommand.h"

Qbert::QbertController::QbertController(bool useController)
	:ComponentBase(),
	m_UseController(useController)
{
}

void Qbert::QbertController::Initialize()
{
	using namespace peach;
	if (m_UseController)
	{
		auto moveCommand = std::make_shared<MoveCommand>(GetParent(), MoveDirection::UpLeft);
		InputManager::GetInstance().AddOrChangeCommand(ControllerButton::ButtonX, moveCommand, CommandExecuteCause::ButtonDown);

		moveCommand = std::make_shared<MoveCommand>(GetParent(), MoveDirection::DownLeft);
		InputManager::GetInstance().AddOrChangeCommand(ControllerButton::ButtonA, moveCommand, CommandExecuteCause::ButtonDown);

		moveCommand = std::make_shared<MoveCommand>(GetParent(), MoveDirection::UpRight);
		InputManager::GetInstance().AddOrChangeCommand(ControllerButton::ButtonY, moveCommand, CommandExecuteCause::ButtonDown);

		moveCommand = std::make_shared<MoveCommand>(GetParent(), MoveDirection::DownRight);
		InputManager::GetInstance().AddOrChangeCommand(ControllerButton::ButtonB, moveCommand, CommandExecuteCause::ButtonDown);
	}
	else
	{
		auto moveCommand = std::make_shared<MoveCommand>(GetParent(), MoveDirection::UpLeft);
		InputManager::GetInstance().AddOrChangeCommand('a', moveCommand, CommandExecuteCause::ButtonDown);

		moveCommand = std::make_shared<MoveCommand>(GetParent(), MoveDirection::DownLeft);
		InputManager::GetInstance().AddOrChangeCommand('s', moveCommand, CommandExecuteCause::ButtonDown);

		moveCommand = std::make_shared<MoveCommand>(GetParent(), MoveDirection::UpRight);
		InputManager::GetInstance().AddOrChangeCommand('w', moveCommand, CommandExecuteCause::ButtonDown);

		moveCommand = std::make_shared<MoveCommand>(GetParent(), MoveDirection::DownRight);
		InputManager::GetInstance().AddOrChangeCommand('d', moveCommand, CommandExecuteCause::ButtonDown);
	}

}

void Qbert::QbertController::Update()
{
}

void Qbert::QbertController::Render() const
{
}
