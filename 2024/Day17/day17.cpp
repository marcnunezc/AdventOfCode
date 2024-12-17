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
    regA=1e15;
    std::stringstream ss(line.substr(line.find(":")+2));
    std::vector<int> instructions;
    std:string value;
    while(getline(ss, value, ','))
        instructions.push_back(stoi(value));

    std::string output="";

    for (size_t i=0; i<instructions.size(); i++) {
        auto opcode = (size_t) instructions[i];
        auto combo = (size_t) instructions[++i];
            cout << opcode << " " << combo<< endl;
        perform_operation(opcode, combo, regA, regB, regC, i, output);
        cout << "regA: " << regA << endl;
        cout << "regB: " << regB << endl;
        cout << "regC: " << regC << endl;
    }
    output = output.substr(0, output.size()-1);
    return output;
}


AOC_DAY(Day17_2){
    std::string line;
    std::size_t sum = 0;
    std::size_t sA, sB, sC, regA, regB, regC;
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

    sA = 2e14+1.5e13;
    sB = regB;
    sC = regC;

    std::string output="";
    while (output != ss.str()) {
        output.clear();
        sA+=1e8;
        // if (sA > 1e14+4e13)
        if (sA > 2e14+2e13)
            break;
        if (sA % 1000 == 0)
            cout << sA << " ";
        regA = sA;
        regB = sB;
        regC = sC;
        for (size_t i=0; i<instructions.size(); i++) {
            auto opcode = (size_t) instructions[i];
            auto combo = (size_t) instructions[++i];
            perform_operation(opcode, combo, regA, regB, regC, i, output);

        }
        output = output.substr(0, output.size()-1);
        if (sA % 1000 == 0)
            cout << output << endl;
    }

    return std::to_string(sA);
}