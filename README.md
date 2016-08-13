# vna_emulator

g++ -std=c++11 main.cpp -o vna_emulator && ./vna_emulator

socat -d -d pty,raw exec:./vna_emulator


