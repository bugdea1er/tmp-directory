#include <tmp/file.hpp>

#include <cstdlib>

namespace tmp {

file::file(std::string_view prefix) : file(prefix, /*binary=*/true) {
}

file file::text(std::string_view prefix) {
    return file(prefix, /*binary=*/false);
}

void file::write(std::string_view content) const {
    this->stream(/*append=*/false) << content;
}

void file::append(std::string_view content) const {
    this->stream(/*append=*/true) << content;
}

file::~file() noexcept = default;

file::file(file&&) noexcept = default;
file& file::operator=(file&&) noexcept = default;

file::file(std::string_view prefix, bool binary) : path(create(prefix)),
                                                   binary(binary) {
}

std::filesystem::path file::create(std::string_view prefix) {
    auto pattern = make_pattern(prefix);
    if (mkstemp(pattern.data()) == -1) {
        auto ec = std::error_code(errno, std::system_category());
        throw error("Cannot create temporary file", ec);
    }

    return pattern;
}

std::ofstream file::stream(bool append) const noexcept {
    std::ios::openmode mode = append ? std::ios::app : std::ios::trunc;
    return this->binary
           ? std::ofstream { this->underlying, mode | std::ios::binary }
           : std::ofstream { this->underlying, mode };
};

}    // namespace tmp
