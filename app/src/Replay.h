#pragma once

#include <stdint.h>
#include <vector>

struct Block {
	uint32_t length = 0;
};

struct Replay {
	std::vector<Block> dataBlocks;
	uint32_t binaryPacketCount = 0;
};
