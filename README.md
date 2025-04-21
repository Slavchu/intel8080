# INTEL8080 emulator by slavchoo

Current project is in develop. After first working version all the commits will be squashed to init commit </br>
To build a project you can use build.sh script. For build you need CMake and linux </br>

## Quick overview
Current project is in develop. After first working version all the commits will be squashed to init commit
To build a project you can use build.sh script. For build you need CMake

Instruction:
```bash
./build.sh [CMAKE ARGUMENTS]
#Example: ./build.sh -DCMAKE_BUILD_TYPE=Debug
#If you don't know how CMAKE ARGUMENTS can be helpful just skip the arguments
```
## Developing process

Current implemented instructions:
- mov
- mvi
- lxi
- lda
- sta
