#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

#define DEBUG


/* TODO:
    - read_ISA()
    - save machine_code to file
*/

std::string to_hex(int val, int hexBits){
    int nbits = hexBits * 4;
    std::stringstream stream;
    stream << std::hex << val;
    return stream.str();
}

std::string format_operand(std::string operand, int hexBits){
    while (operand.length() != hexBits){ operand = '0' + operand; }
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
        if (ISA->find(opcode) == ISA->end()){ // if opcode is invalid
            std::cout << opcode + " instruction has not been implemented" << '\n';
            machine_code->push_back(line);
        } else { // if opcode is valid
            opcode = ISA->at(opcode);
            int operand_hex_size = 4 - opcode.length();
            std::string operand = (operand_hex_size > 0) ? line.substr(line.find(' ')+1, line.length()) : ""; // take operand if present, also +1 is necessary to remove leading space
            if (opcode.length() <= 3){
                if (operand.find("0x") != std::string::npos){ // if operand is given as hex
                    machine_code->push_back(opcode + format_operand(operand.substr(2, operand.length()), operand_hex_size));
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
