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

def generate_machine_code(assembly, machine_code):
    for line in assembly:
        if line.isspace():
            continue

        match line.split(' ', 1)[0]:
            case "MOVEI":
                machine_code.append("C"+ to_hex(int(line.split(' ')[1])))

                debug_output(machine_code)

            case "JMP":
                machine_code.append("E" + to_hex(int(line.split(' ')[1])))

                debug_output(machine_code)

            case "ADDI":
                machine_code.append("D" + to_hex(int(line.split(' ')[1])))

                debug_output(machine_code)

            case "BZ":
                machine_code.append("FE" + to_hex(int(line.split(' ')[1]), nbits=8))

                debug_output(machine_code)


            case _:
                print(line.partition(' ')[0] + " machine_code is instruction has not been implemented")
                machine_code.append(line)


def main():
    file_name = input("Please enter the filename of the assembly source: ")
    try:
        assembly_file = open(file_name, 'r')
        assembly = assembly_file.readlines()
        assembly_file.close()
    except:
        print("File {0} could not be found or opened".format(file_name))
        exit()

    machine_code = []
    generate_machine_code(assembly, machine_code)

    machine_code_output = open('machine_code.cdm', 'w')
    for (instruction_mem, instruction) in enumerate(machine_code):
        machine_code_output.writelines(str(instruction_mem) + ' : ' + instruction + '\n')


if __name__ == "__main__":
    main()