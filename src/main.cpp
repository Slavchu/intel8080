#include <chrono>
#include <common.hpp>
#include <cpu8080.hpp>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <memory.hpp>
#include <thread>

enum EEXCEPTION_LOAD_PROGRAM {
    FILE_NOT_OPEN = 1
};

void load_program(std::string program_path = DEFAULT_PROGRAM_PATH);

int main(int argc, char* argv[]) {
    std::cout << "Emulator by slavchoo\n";

    try {
        load_program();
    } catch (EEXCEPTION_LOAD_PROGRAM ex) {
        switch (ex) {
            case FILE_NOT_OPEN: {
                DEBUG_ERROR("File not oppened");
                exit(-1);
                break;
            }
            default: {
                DEBUG_ERROR("Unknown error");
                exit(-1);
                break;
            }
        }
    } catch (std::ifstream::failure ex) {
        DEBUG_ERROR("Error reading/closing file");
    }

    auto& cpu = CPU_8080::instance();
    while (1) {
        auto awake_time = std::chrono::steady_clock::now() +
                          std::chrono::milliseconds(1000 / FREQUENCY_HZ);
        cpu.tick();
        std::this_thread::sleep_until(awake_time);
    }
    return 0;
}

void load_program(std::string program_path) {
    using namespace std;

    ifstream in(program_path, ios::binary);
    uint16_t mem_adress = 0;
    auto& mem = RAM::instance();

    if (!in.is_open()) throw EEXCEPTION_LOAD_PROGRAM::FILE_NOT_OPEN;

    while (!in.eof()) {
        mem.write(mem_adress, in.get());
        mem_adress++;
    }
    in.close();
}
