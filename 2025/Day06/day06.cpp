AOC_DAY(Day06_1) {

    std::size_t sum = 0;
    std::string line;

    std::vector<std::vector<size_t>> operands;
    std::vector<char> operations;

    while(getline(cin,line)) {
        std::stringstream ss(line);
        if (line[0]=='*' || line[0]=='+') {
            char operation;
            while (ss >> operation) {
                operations.push_back(operation);
            }
        } else {
            std::vector<size_t> numbers_row;

            size_t value;
            while (ss >> value) {
                numbers_row.push_back(value);
            }
            operands.push_back(numbers_row);
        }
    }

    for (int i=0; i<operations.size(); i++) {
        size_t result;
        if (operations[i] == '+') {
            result = 0;
            for (int j=0; j<operands.size(); j++) {
                result += operands[j][i];
            }
        } else {
            result=1;
            for (int j=0; j<operands.size(); j++) {
                result *= operands[j][i];
            }
        }
        sum+= result;
    }



    return std::to_string(sum);
}

int find_next_symbol(int i_start, std::string str_to_find)
{
    for (int i=i_start+1; i<str_to_find.size(); i++) {
        if (str_to_find[i] == '*' || str_to_find[i] == '+')
        {
            return i;
        }
    }
    return str_to_find.size();
}


AOC_DAY(Day06_2){
    std::size_t sum = 0;
    std::string line;
    std::vector<string> input;
    while(getline(cin,line)) {
        input.push_back(line);
    }

    std::string operator_str = input.back();
    int i_start = 0;
    int i_next = find_next_symbol(i_start, operator_str);

    while (i_start < operator_str.size()) {
        size_t result;
        if (operator_str[i_start] == '+') {
            result=0;
        } else {
            result=1;
        }
        int starting_i = i_next == operator_str.size() ? i_next-1 : i_next-2;
        for (int i = starting_i; i >= i_start; i--){
            int number_of_digits=0;
            int number = 0;
            for (int j=input.size()-1; j>=0; j--) {
                if (std::isdigit(input[j][i])) {
                    number += (input[j][i]-'0')*std::pow(10, number_of_digits++);
                }
            }

            if (operator_str[i_start] == '+') {
                result += number;
            } else {
                result *= number;
            }

        }
        sum+=result;
        i_start = i_next;
        i_next = find_next_symbol(i_start, operator_str);
    }

    return std::to_string(sum);
}
