#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>


typedef std::vector<std::string> str_vector;
typedef std::map<std::string, std::string> dictionary;

std::string to_hex(int val, int hexBits);
std::string format_operand(std::string, int);
dictionary read_ISA();
void debug_output(str_vector *machine_code);
void generate_machine_code(str_vector *assembly, str_vector *machine_code, dictionary *ISA);


int main(int argc, char const *argv[]) {

    std::cout << "\n" <<
    "====================================================================================\n\n" <<
    "@@@@@@@@@@   @@@@@@@@  @@@@@@@   @@@@@@               @@@@@@    @@@@@@   @@@@@@@@@@ \n" <<
    "@@@@@@@@@@@  @@@@@@@@  @@@@@@@  @@@@@@@@             @@@@@@@@  @@@@@@@   @@@@@@@@@@@\n" <<
    "@@! @@! @@!  @@!         @@!    @@!  @@@             @@!  @@@  !@@       @@! @@! @@!\n" <<
    "!@! !@! !@!  !@!         !@!    !@!  @!@             !@!  @!@  !@!       !@! !@! !@!\n" <<
    "@!! !!@ @!@  @!!!:!      @!!    @!@!@!@!  @!@!@!@!@  @!@!@!@!  !!@@!!    @!! !!@ @!@\n" <<
    "!@!   ! !@!  !!!!!:      !!!    !!!@!!!!  !!!@!@!!!  !!!@!!!!   !!@!!!   !@!   ! !@!\n" <<
    "!!:     !!:  !!:         !!:    !!:  !!!             !!:  !!!       !:!  !!:     !!:\n" <<
    ":!:     :!:  :!:         :!:    :!:  !:!             :!:  !:!      !:!   :!:     :!:\n" <<
    ":::     ::    :: ::::     ::    ::   :::             ::   :::  :::: ::   :::     :: \n" <<
    " :      :    : :: ::      :      :   : :              :   : :  :: : :     :      :  \n" <<
    "\n By zer0p1us"<<
    "\n\n====================================================================================\n";

    dictionary ISA = read_ISA();
    std::string file_name;
    std::cout << "Please enter the filename of the assembly source: ";
    std::cin >> file_name;

    str_vector assembly;

    try {
        std::fstream assembly_file(file_name);
        std::string line;
        while (assembly_file.good()) {
            std::getline(assembly_file, line);
            if (line.empty() || line[0] == ';') continue;
            assembly.push_back(line.substr(0, line.find(';')-1));
        }
        // check if assembly dic is empty
        // if so either file was not found or was empty
        if (assembly.size() == 0){ std::cout << file_name << " could not be opened or was empty" << '\n'; return 0; }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return -1;
    }

    str_vector machine_code;
    generate_machine_code(&assembly, &machine_code, &ISA);

    std::ofstream machine_code_file;
    machine_code_file.open(file_name + ".cdm");
    int index = 0;
    for (std::string line : machine_code){
        machine_code_file << index++ << " : " <<  line << '\n';
    }
    machine_code_file.close();
    return 0;
}
std::string to_hex(int val, int hexBits){
    std::stringstream hex;
    hex << std::hex << val;
    return format_operand(hex.str(), hexBits);
}

std::string format_operand(std::string operand, int hexBits){
    while (operand.length() != hexBits){
        operand = '0' + operand;
        // check if operand is bigger than it should
        // if not done an infinite loop will accure
        if (operand.length() > hexBits) {
            std::cerr << "[Err]: operand seems bigger than legal size" << "\n";
            operand = operand.substr(operand.length()-hexBits, operand.length()-1); // remove zero
            continue;
        }
    }
    std::transform(operand.begin(), operand.end(), operand.begin(), toupper);
    return operand;
}

dictionary read_ISA(){
    std::ifstream f_ISA("ISA.csv", std::ios::in);
    if (!f_ISA.is_open()){
        std::cout << "[Err]: couldn't read ISA.csv file containing ISA specification!" << '\n';
        std::cout << "[Resolution]: please place the ISA.csv file in the same directory as the executable" << '\n';
    }
    std::string line;
    dictionary ISA;
    int index;
    std::string key;
    std::string data;
    while (getline(f_ISA, line)){
        index = line.find(",");
        key = line.substr(0, index);
        data = line.substr(index+1, line.length()-1);
        ISA[key] = data;
    }
    return ISA;
}

void generate_machine_code(str_vector *assembly, str_vector *machine_code, dictionary *ISA){
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
            std::cout << machine_code->size() << " : " << machine_code->at(machine_code->size()-1) << '\n';

        }
    }
}
