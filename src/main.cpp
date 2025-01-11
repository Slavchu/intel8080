#include <cstdint>
#include <iostream>
#include <common.hpp>
#include <cpu8080.hpp>
#include <memory.hpp>
#include <chrono>
#include <thread>
#include <fstream>

bool load_program(std::string program_path = DEFAULT_PROGRAM_PATH);

int main(){
    std::cout << "Emulator by slavchoo\n";
    load_program(); 
    auto &cpu = CPU_8080::instance(); 
    while(1){
        auto awake_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(1000/FREQUENCY_HZ); 
        cpu.tick();
        std::this_thread::sleep_until(awake_time);
    } 
    return 0;
}

bool load_program(std::string program_path){
    using namespace std;

    ifstream in(program_path, ios::binary);
    uint16_t mem_adress = 0;
    auto &mem = RAM::instance();

    if(!in.is_open())
        return 0;

    while(!in.eof()){
        mem.write(mem_adress, in.get());
        mem_adress++;
    }
    return 1;
}

