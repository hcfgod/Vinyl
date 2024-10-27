#pragma once
#include "Vinyl/Core/Buffer.h"

namespace Vinyl
{
	class FileSystem
	{
	public:
		// TODO: move to FileSystem class
		static Buffer ReadFileBinary(const std::filesystem::path& filepath);
	};
}