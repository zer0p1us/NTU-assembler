import csv

DEBUG = True

def to_hex(val, hexBits):
    nbits = hexBits * 4
    hex_value = hex((val + (1 << nbits)) % (1 << nbits))[2:].upper()
    return format_operand(hex_value, hexBits)

# check if operand is the correct size
# if not add leadind zeros to comply
def format_operand(operand, hexBits):
    while (len(operand) != hexBits):
        operand = '0' + operand
    return operand

def debug_output(machine_code):
    if DEBUG:
        print(str(len(machine_code)-1) + " : " + machine_code[len(machine_code)-1])

def read_ISA():
    ISA = {}
    with open("./ISA.csv", 'r', newline='') as ISA_file:
        reader = csv.DictReader(ISA_file)
        for row in reader:
            ISA[row['instruction']] = row['opcode']
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

            opcode = ISA[line.split(' ', 1)[0]]
            operand_hex_size = 4 - len(opcode) # compute size of operand in hex
            operand = line.split(' ')[1] if operand_hex_size > 0 else ""

            if (len(opcode) <= 3):
                # check if operand is already in hex
                if operand[:2].lower() == "0x":
                    # add operand to machine code as is
                    machine_code.append(opcode + format_operand(operand[2:len(operand)], operand_hex_size))
                else:
                    machine_code.append(opcode + to_hex(int(operand), operand_hex_size))

            # if there is no operand add opcode to machine code
            elif (len(opcode) == 4):
                machine_code.append(opcode)
            debug_output(machine_code)


def main():
    ISA = read_ISA()
    file_name = input("Please enter the filename of the assembly source: ")
    try:
        assembly_file = open(file_name, 'r')
        assembly = assembly_file.readlines()
        assembly_file.close()
        # removing comments, new line & trailing whitespaces if present
        for i in range(len(assembly)): assembly[i] = assembly[i].split(';')[0].rstrip('\n').rstrip(' ') if ';' in assembly[i] else assembly[i].rstrip('\n').rstrip(' ')
    except:
        print("File {0} could not be found or opened".format(file_name))
        exit()

    machine_code = []
    generate_machine_code(assembly, machine_code, ISA)

    # write machine code to CDM file
    machine_code_file = open(file_name[:file_name.rindex('\\')+1] + file_name[file_name.rindex('\\'):]+'.cdm', 'w')
    for (instruction_mem, instruction) in enumerate(machine_code):
        machine_code_file.writelines(str(instruction_mem) + ' : ' + instruction + '\n')
    machine_code_file.close()


if __name__ == "__main__":
    main()
