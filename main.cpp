#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    std::vector<std::string> files;


    for (int i = 1; i < argc; ++i) {
        files.push_back(argv[i]);
    }

    if (files.empty()) {
        std::cerr << "ошибка" << std::endl;
        return 1;
    }


    std::ofstream outfile("out.lua", std::ios::binary);


    if (!outfile.is_open()) {
        std::cerr << "Ошибка" << std::endl;
        return 1;
    }


    unsigned char header[] = { 0x1b, 0x4c, 0x4a, 0x02, 0x01, 0x00, 0x04, 0x04 };
    outfile.write(reinterpret_cast<const char*>(header), sizeof(header));


    for (const auto& file : files) {
        std::ifstream infile(file, std::ios::binary);

        if (!infile.is_open()) {
            std::cerr << "Ошибка: " << file << std::endl;
            continue;
        }

        outfile << infile.rdbuf();
    }

    return 0;
}
