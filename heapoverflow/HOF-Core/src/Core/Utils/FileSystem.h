#pragma once

#include <filesystem>

namespace hof::Utils
{
    // This will be set at startup in main()
    inline std::filesystem::path G_ExecutableDirectory;
}
