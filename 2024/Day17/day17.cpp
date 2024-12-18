void perform_operation(size_t opcode, size_t literal_operand, std::size_t& regA, std::size_t& regB, std::size_t& regC, size_t& instruction_pointer, std::string& output) {
    size_t result;
    size_t comboOperand;
    switch (literal_operand) {
        case 1:
        case 2:
        case 3:
            comboOperand = literal_operand;
            break;
        case 4:
            comboOperand = regA;
            break;
        case 5:
            comboOperand = regB;
            break;
        case 6:
            comboOperand = regC;
            break;
        case 7:
            break;
    }
    switch (opcode) {
        case 0:
            regA = (size_t) regA / (std::pow(2, comboOperand));
            break;
        case 1:
            regB = regB ^ literal_operand;
            break;
        case 2:
            regB = comboOperand % 8;
            break;
        case 3:
            if (regA != 0) {
                instruction_pointer = literal_operand-1;
            }
            break;
        case 4:
            regB = regB ^ regC;
            break;
        case 5:
            output += std::to_string(comboOperand % 8);
            output += ",";
            break;
        case 6:
            regB = (size_t) regA / (std::pow(2, comboOperand));
            break;
        case 7:
            regC = (size_t) regA / (std::pow(2, comboOperand));
            break;

    }
}


AOC_DAY(Day17_1) {
    std::string line;
    std::size_t sum = 0;
    std::size_t regA, regB, regC;
    getline(cin, line);
    sscanf(line.c_str(), "Register A: %ld", &regA);
    getline(cin, line);
    sscanf(line.c_str(), "Register B: %ld", &regB);
    getline(cin, line);
    sscanf(line.c_str(), "Register C: %ld", &regC);
    getline(cin, line);
    getline(cin, line);

    std::stringstream ss(line.substr(line.find(":")+2));
    std::vector<int> instructions;
    std:string value;
    while(getline(ss, value, ','))
        instructions.push_back(stoi(value));

    std::string output="";

    for (size_t i=0; i<instructions.size(); i++) {
        auto opcode = (size_t) instructions[i];
        auto combo = (size_t) instructions[++i];
        perform_operation(opcode, combo, regA, regB, regC, i, output);
    }
    output = output.substr(0, output.size()-1);
    return output;
}


AOC_DAY(Day17_2){
    std::string line;
    std::size_t sum = 0;
    std::size_t startA, startB, startC, regA, regB, regC;
    getline(cin, line);
    sscanf(line.c_str(), "Register A: %ld", &regA);
    getline(cin, line);
    sscanf(line.c_str(), "Register B: %ld", &regB);
    getline(cin, line);
    sscanf(line.c_str(), "Register C: %ld", &regC);
    getline(cin, line);
    getline(cin, line);
    std::stringstream ss(line.substr(line.find(":")+2));
    std::string target = ss.str();
    std::vector<int> instructions;
    std:string value;
    while(getline(ss, value, ','))
        instructions.push_back(stoi(value));
    size_t lower = std::pow(10, instructions.size()-3);
    size_t upper = std::pow(10, instructions.size()-2);
    startA = regA;
    startB = regB;
    startC = regC;

    size_t pointer = target.size()-3;
    size_t step = lower / 10;

    std::string output="";
    while (output != ss.str()) {
        startA = lower;

        while(output.size() != target.size() || target.substr(pointer, target.size()) != output.substr(pointer, output.size())) {
            output.clear();
            startA+=step;
            regA = startA;
            regB = startB;
            regC = startC;
            for (size_t i=0; i<instructions.size(); i++) {
                auto opcode = (size_t) instructions[i];
                auto combo = (size_t) instructions[++i];
                perform_operation(opcode, combo, regA, regB, regC, i, output);

            }
            output = output.substr(0, output.size()-1);
        }
        lower = startA-step;
        step = step/100;
        if (step <1)
            step = 1;
        pointer -= 4;
    }

    return std::to_string(startA);
}