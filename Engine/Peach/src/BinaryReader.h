#pragma once
#include <fstream>

namespace BinaryReader {
	template <typename T>
	void Read(std::ifstream& in, T& toRead)
	{
		if (std::is_pod<T>::value)
		{
			if (in.is_open())
			{
				in.read((char*)&toRead, sizeof(toRead));
			}
		}
		else
		{
			std::cerr << typeid(toRead).name() << "is not a pod and BinaryReader has no appropriate overloaded read function\n";
		}
	}
	template<>
	void Read<std::string>(std::ifstream& in, std::string& toRead)
	{
		if (in.is_open())
		{
			uint32_t stringLength{};
			in.read((char*)&stringLength, sizeof(stringLength));

			toRead.resize(stringLength);

			in.read((char*)&toRead[0], stringLength);
		}
	}
}
