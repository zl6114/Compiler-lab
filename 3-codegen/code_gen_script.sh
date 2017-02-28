chmod u+x ./code_gen_script.sh
mips-linux-gnu-g++ -static output.cpp -o output
qemu-mips output
