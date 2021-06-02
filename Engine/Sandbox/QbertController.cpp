#include "QbertPCH.h"

#include "QbertController.h"
#include "InputManager.h"
#include "MoveCommand.h"

void peach::QbertController::Initialize()
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
