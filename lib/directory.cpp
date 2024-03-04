#include <tmp/directory>

#include <filesystem>
#include <string_view>
#include <system_error>
#include <unistd.h>

namespace fs = std::filesystem;

namespace {

/// Creates a temporary directory with the given prefix in the system's
/// temporary directory, and returns its path
/// @param prefix   The prefix to use for the temporary file name
/// @returns A path to the created temporary file
/// @throws fs::filesystem_error if the temporary directory cannot be created
fs::path create(std::string_view prefix) {
    std::string pattern = tmp::path::make_pattern(prefix);
    if (mkdtemp(pattern.data()) == nullptr) {
        std::error_code ec = std::error_code(errno, std::system_category());
        throw fs::filesystem_error("Cannot create temporary directory", ec);
    }

    return pattern;
}
}    // namespace

namespace tmp {

directory::directory(std::string_view prefix)
    : path(create(prefix)) {}

directory directory::copy(const fs::path& path, std::string_view prefix) {
    if (fs::is_regular_file(path)) {
        std::error_code ec = std::make_error_code(std::errc::is_a_directory);
        throw fs::filesystem_error("Cannot copy temporary directory", ec);
    }

    directory tmpdir = directory(prefix);
    fs::copy(path, tmpdir, fs::copy_options::recursive
                           | fs::copy_options::overwrite_existing);
    return tmpdir;
}

fs::path directory::operator/(std::string_view source) const {
    return static_cast<const fs::path&>(*this) / source;
}

directory::~directory() noexcept = default;

directory::directory(directory&&) noexcept = default;
directory& directory::operator=(directory&&) noexcept = default;
}    // namespace tmp
