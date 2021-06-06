#pragma once
#include <fstream>
#include <iostream>

namespace BinaryWriter {
	template <typename T>
	void Write(std::ofstream& out, T& toWrite)
	{
		if (std::is_pod<T>::value)
		{
			if (out.is_open())
			{
				out.write((char*)&toWrite, sizeof(toWrite));
			}
		}
		else
		{
			std::cerr << typeid(toWrite).name() << "is not a pod and BinaryWriter has no appropriate overloaded write function\n";
		}
	}
	template<>
	void Write<const std::string>(std::ofstream& out, const std::string& toWrite)
	{
		if (out.is_open())
		{
			uint32_t stringLength = toWrite.size();
			out.write((const char*)&stringLength, sizeof(stringLength));
			out.write(&toWrite[0], stringLength);
		}
	}
}
