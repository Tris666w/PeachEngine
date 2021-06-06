#include "QbertPCH.h"
#include "CoilyController.h"
#include "CoilyMoveCommand.h"
#include "Level/LevelMovementComponent.h"

void Qbert::CoilyController::Initialize()
{
	auto pInput = GetParent()->GetScene()->GetInputManager();
	auto moveCommand = std::make_shared<CoilyMoveCommand>(GetParent(), MoveDirection::UpLeft);
	pInput->AddOrChangeCommand(peach::ControllerButton::ButtonX, moveCommand, peach::CommandExecuteCause::ButtonDown);

	moveCommand = std::make_shared<CoilyMoveCommand>(GetParent(), MoveDirection::DownLeft);
	pInput->AddOrChangeCommand(peach::ControllerButton::ButtonA, moveCommand, peach::CommandExecuteCause::ButtonDown);

	moveCommand = std::make_shared<CoilyMoveCommand>(GetParent(), MoveDirection::UpRight);
	pInput->AddOrChangeCommand(peach::ControllerButton::ButtonY, moveCommand, peach::CommandExecuteCause::ButtonDown);

	moveCommand = std::make_shared<CoilyMoveCommand>(GetParent(), MoveDirection::DownRight);
	pInput->AddOrChangeCommand(peach::ControllerButton::ButtonB, moveCommand, peach::CommandExecuteCause::ButtonDown);
}

void Qbert::CoilyController::Update()
{
}

void Qbert::CoilyController::Render() const
{
}
