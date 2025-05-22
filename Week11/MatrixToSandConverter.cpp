#include "MatrixToSandConverter.h"

const Grain::CellInfo MatrixToSandConverter::toGrain(std::vector<std::string> line) {
	Grain::CellInfo result = { 0, 0, 0 };
	for (int i = 0; i < line.size(); i++)
	{
		switch (i)
		{
		case 0:
			result.x = static_cast<uint16_t>(std::stoull(line[i]));
			break;
		case 1:
			result.y = static_cast<uint16_t>(std::stoull(line[i]));
			break;
		case 2:
			result.count = static_cast<uint64_t>(std::stoull(line[i]));
			break;
		default:
			break;
		}
	}
	return result;
}

const std::vector<Grain::CellInfo> MatrixToSandConverter::matrixToSand(std::vector<std::vector<std::string>> matrix) {
	std::vector<Grain::CellInfo> sand;
	for (int i = 0; i < matrix.size(); i++)
	{
		sand.push_back(toGrain(matrix[i]));
	}
	return sand;
}