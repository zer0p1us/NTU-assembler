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

void generate_machine_code(std::vector<std::string> *assembly, std::vector<std::string> *machine_code, std::map<std::string, std::string> *ISA){
    for (std::string line : *assembly){
        std::string opcode = line.substr(0, line.find(' '));

        // check if opcode is valid
        if (*ISA->find(opcode) == *ISA->end()){ // if opcode is invalid
            std::cout << opcode + " instruction has not been implemented" << '\n';
            machine_code->push_back(line);
        } else { // if opcode is valid

            uint8_t operand_hex_size = 4 - opcode.size();
            std::string operand = (operand_hex_size > 0) ? line.substr(1, line.find(' ')) : "";

            if (opcode.size() <= 3){
                if (operand.substr(0, 1) == "0x"){
                    machine_code->push_back(opcode + format_operand(operand.substr(2, operand.size()), operand_hex_size));
                }else{
                    machine_code->push_back(opcode + to_hex(std::stoi(operand), operand_hex_size));
                }
            }else{
                machine_code->push_back(opcode);
            }
            debug_output(&*machine_code);

        }
    }
}

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
