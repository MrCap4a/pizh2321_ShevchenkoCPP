#pragma once
#include "Grain.h"
#include <vector>
#include <string>

class MatrixToSandConverter
{
public:
	static const Grain::CellInfo toGrain(std::vector<std::string> line);
	static const std::vector<Grain::CellInfo> matrixToSand(std::vector<std::vector<std::string>> filename);
};

