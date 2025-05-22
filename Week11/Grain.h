#pragma once
#include <cstdint>
class Grain
{
public:
	const struct CellInfo
	{
		uint16_t x;
		uint16_t y;
		uint64_t count;
	};

	const Grain::CellInfo& getData() const;
private:
	CellInfo data;
};

