import csv

DEBUG = True

def to_hex(val, nbits = 12):
    hex_value = hex((val + (1 << nbits)) % (1 << nbits))[2:].upper()
    operand_size = nbits/4;
    while (len(hex_value) != operand_size):
        hex_value = '0' + hex_value
    return hex_value

def debug_output(machine_code):
    if DEBUG:
        print(str(len(machine_code)-1) + " : " + machine_code[len(machine_code)-1])

def read_ISA():
    ISA = {}
    with open("./ISA.csv", 'r', newline='') as ISA_file:
        reader = csv.DictReader(ISA_file)
        for row in reader:
            ISA[row['instruction']] = [row['opcode'], row['operand_bit_size']]
        ISA_file.close()
    return ISA


def generate_machine_code(assembly, machine_code, ISA):
    for line in assembly:
        if line.isspace():
            continue

        if (line.split(' ', 1)[0] not in ISA):
            print(line.split(' ', 1)[0] + " instruction has not been implemented")
            machine_code.append(line)
        else:
            operand = line.split(' ')[1]
            opcode = ISA[line.split(' ', 1)[0]][0]
            operand_bit_size = ISA[line.split(' ', 1)[0]][1]
            if operand[:2].lower() == "0x":
                machine_code.append(opcode + operand[2:len(operand)-1])
            else:
                machine_code.append(opcode + to_hex(int(operand), int(operand_bit_size)))
            debug_output(machine_code)


def main():
    ISA = read_ISA()
    file_name = input("Please enter the filename of the assembly source: ")
    try:
        assembly_file = open(file_name, 'r')
        assembly = assembly_file.readlines()
        assembly = [line.rstrip('\n') for line in assembly]
        assembly_file.close()
    except:
        print("File {0} could not be found or opened".format(file_name))
        exit()

    machine_code = []
    generate_machine_code(assembly, machine_code, ISA)

    machine_code_file = open('machine_code.cdm', 'w')
    for (instruction_mem, instruction) in enumerate(machine_code):
        machine_code_file.writelines(str(instruction_mem) + ' : ' + instruction + '\n')
    machine_code_file.close()


if __name__ == "__main__":
    main()
