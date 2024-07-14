#include "parser.h"
#include "utility/on_scope_exit.hpp"
#include "assert/advanced_assert.h"

#include <QFile>

template <typename T>
inline T read(QFile& f) noexcept {
	T value;
	if (f.read(reinterpret_cast<char*>(&value), sizeof(T)) != sizeof(T))
		return {};

	return value;
}

Replay parseReplay(const QString& path)
{
	QFile file{ path };
	assert_and_return_r(file.open(QFile::ReadOnly), {});

	// auto* mappedFile = file.map(0, file.size());
	// assert_and_return_r(mappedFile, {});

	// EXEC_ON_SCOPE_EXIT([&]{
	// 	file.unmap(mappedFile);
	// });

	const uint32_t magic = read<uint32_t>(file);
	assert_and_return_r(magic == 0x11343212u, {});
	uint32_t blockCount = read<uint32_t>(file);

	Replay r;

	for (uint32_t i = 0 ; i < blockCount; ++i)
	{
		uint32_t len = read<uint32_t>(file);
		r.dataBlocks.emplace_back(len);
		file.seek(file.pos() + len);
	}

	return r;
}
