#include "QbertPCH.h"

#include "QbertController.h"
#include "InputManager.h"
#include "QbertMoveCommand.h"

Qbert::QbertController::QbertController(bool useController)
	:ComponentBase(),
	m_UseController(useController)
{
}

void Qbert::QbertController::Initialize()
{
	auto pInput = GetParent()->GetScene()->GetInputManager();

	using namespace peach;
	if (m_UseController)
	{
		auto moveCommand = std::make_shared<QbertMoveCommand>(GetParent(), MoveDirection::UpLeft);
		pInput->AddOrChangeCommand(ControllerButton::ButtonX, moveCommand, CommandExecuteCause::ButtonDown);

		moveCommand = std::make_shared<QbertMoveCommand>(GetParent(), MoveDirection::DownLeft);
		pInput->AddOrChangeCommand(ControllerButton::ButtonA, moveCommand, CommandExecuteCause::ButtonDown);

		moveCommand = std::make_shared<QbertMoveCommand>(GetParent(), MoveDirection::UpRight);
		pInput->AddOrChangeCommand(ControllerButton::ButtonY, moveCommand, CommandExecuteCause::ButtonDown);

		moveCommand = std::make_shared<QbertMoveCommand>(GetParent(), MoveDirection::DownRight);
		pInput->AddOrChangeCommand(ControllerButton::ButtonB, moveCommand, CommandExecuteCause::ButtonDown);
	}
	else
	{
		auto moveCommand = std::make_shared<QbertMoveCommand>(GetParent(), MoveDirection::UpLeft);
		pInput->AddOrChangeCommand('a', moveCommand, CommandExecuteCause::ButtonDown);

		moveCommand = std::make_shared<QbertMoveCommand>(GetParent(), MoveDirection::DownLeft);
		pInput->AddOrChangeCommand('s', moveCommand, CommandExecuteCause::ButtonDown);

		moveCommand = std::make_shared<QbertMoveCommand>(GetParent(), MoveDirection::UpRight);
		pInput->AddOrChangeCommand('w', moveCommand, CommandExecuteCause::ButtonDown);

		moveCommand = std::make_shared<QbertMoveCommand>(GetParent(), MoveDirection::DownRight);
		pInput->AddOrChangeCommand('d', moveCommand, CommandExecuteCause::ButtonDown);
	}

}

void Qbert::QbertController::Update()
{
}

void Qbert::QbertController::Render() const
{
}
