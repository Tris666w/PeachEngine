#include "PeachPCH.h"
#include "Transform.h"

void peach::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void peach::Transform::SetPosition(glm::vec3 pos)
{
	m_Position = pos;
}
