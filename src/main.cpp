#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>

#define DEBUG


std::string to_hex(int val, int hexBits);

std::string format_operand(std::string operand, int hexBits){
    while (operand.size() != hexBits){ operand = '0' + operand; }
    return operand;
}

void debug_output(std::vector<std::string> *machine_code){
    #ifdef DEBUG
        std::cout << machine_code->size() << " : " << machine_code->at(machine_code->size()-1) << '\n';
    #endif
}


std::map<std::string, std::string> read_ISA();

void generate_machine_code(std::vector<std::string> *assembly, std::vector<std::string> *machine_code, std::map<std::string, std::string> *ISA);

int main(int argc, char const *argv[]) {
    // will be read from a CSV file eventually
    std::map<std::string, std::string> ISA = {{"JMP","E"},
                                        {"ADDI","D"},
                                        {"MOVEI","C"},
                                        {"MOVE","B"},
                                        {"STORE","A"},
                                        {"LDA","9"},
                                        {"LDSP","8"},
                                        {"BZ","FE"},
                                        {"BNZ","FD"},
                                        {"STA","FFFF"},
                                        {"STA+","FFFE"},
                                        {"MOVE(A)","FFFD"},
                                        {"MOVE(A)+","FFFC"},};
    std::string file_name;
    std::cout << "Please enter the filename of the assembly source: ";
    std::cin >> file_name;

    std::vector<std::string> assembly;

    try {
        std::fstream assembly_file(file_name);
        std::string line;
        while (assembly_file.good()) {
            std::getline(assembly_file, line);
            if (line.empty()) continue;
            assembly.push_back(line);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }

    std::vector<std::string> machine_code;
    generate_machine_code(&assembly, &machine_code, &ISA);


    return 0;
}
