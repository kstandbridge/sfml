#pragma once
#include <iostream>
#include <sstream>
#include "ECS_Types.h"

class C_Base
{
public:
	C_Base(const Component& type) {}
	virtual ~C_Base() {}

	Component GetType() { return m_type; }

	friend std::stringstream& operator >>(std::stringstream& stream, C_Base& b)
	{
		b.ReadIn(stream);
		return stream;
	}

	virtual void ReadIn(std::stringstream& stream) = 0;

protected:
	Component m_type;
};
