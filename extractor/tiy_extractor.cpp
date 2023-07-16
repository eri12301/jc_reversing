#include "tiy_extractor.hpp"
#include <fstream>

void Extractor::unpack_tiy(const std::filesystem::path &srcTiy)
{
    if (!std::filesystem::is_regular_file(srcTiy)) {
            throw std::runtime_error{fmt::format(R"(Can't find "{}" in "{}")", srcTiy.filename().string(),
                                                 srcTiy.parent_path().string())};
        }
        std::ifstream tiyFile(srcTiy, std::ifstream::binary);
//        std::filesystem::create_directories(dest);
        fmt::print("Starting to unpack .tiy\n");
        uint32_t numberOfEntries = 0;
        tiyFile.read(reinterpret_cast<char *>(&numberOfEntries), sizeof(numberOfEntries));
        auto *offsets = new uint32_t(numberOfEntries);
        tiyFile.read(reinterpret_cast<char *>(offsets), numberOfEntries * sizeof(uint32_t));
        fmt::print("Num of entries: {}\n", numberOfEntries);
        int x;
        for (x = 0; x < numberOfEntries - 1; x++) {
            fmt::print("0x{:x} ", offsets[x]);
            uint32_t timSize = offsets[x+1] - offsets[x];
            std::vector<char> buffer(timSize);
            tiyFile.seekg(offsets[x]);
            tiyFile.read(buffer.data(), timSize);
            std::string::size_type const p(srcTiy.string().find_last_of('.'));
            std::string file_without_extension = srcTiy.string().substr(0, p);
            auto timPath = fmt::format("{}_{}.TIM", file_without_extension, x);
            std::ofstream file{timPath, std::ofstream::binary};
            file.write((const char *) buffer.data(), buffer.size());
        }
        if(numberOfEntries > 0) {
            fmt::print("0x{:x} ", offsets[numberOfEntries - 1]);
            uintmax_t fileSize = file_size(srcTiy);
            uintmax_t timSize = fileSize - offsets[numberOfEntries - 1];
            std::vector<char> buffer(timSize);
            tiyFile.seekg(offsets[numberOfEntries - 1]);
            tiyFile.read(buffer.data(), timSize);

            std::string::size_type const p(srcTiy.string().find_last_of('.'));
            std::string file_without_extension = srcTiy.string().substr(0, p);
            auto timPath = fmt::format("{}_{}.TIM", file_without_extension, numberOfEntries - 1);
            std::ofstream file{timPath, std::ofstream::binary};
            file.write((const char *) buffer.data(), buffer.size());
        }
}