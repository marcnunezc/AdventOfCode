AOC_DAY(Day07_1) {

    std::string line;
    std::size_t sum = 0;

    while(getline(cin, line)) {

        long int target = std::stol(line.substr(0,line.find(':')));
        std::stringstream ss(line.substr(line.find(':')+2));
        std::vector<int> numbers;
        int number;
        while (ss >> number)
            numbers.push_back(number);

        long int result;
        auto number_of_operators = numbers.size()-1;
        size_t number_of_permutations = 1 << number_of_operators;
        for (size_t permutation = 0; permutation<number_of_permutations; permutation++) {
            size_t i=0;
            for (int bit = number_of_operators-1; bit >= 0; --bit) {
                bool operation = ((permutation >> bit) & 1);
                if (bit == number_of_operators-1) //first computation
                {
                    if (operation) // sum
                        result = numbers[i] + numbers[i+1];
                    else          //product
                        result = numbers[i]*numbers[i+1];
                    i+=2;
                } else {
                    if (operation) // sum
                        result += numbers[i];
                    else          //product
                        result *= numbers[i];
                    i++;
                }
            }
            if (result == target) {
                sum+=target;
                break;
            }
        }
    }

    return std::to_string(sum);
}

size_t compute_number_of_digits(long int number) {
    size_t digits = 1;
    while(number/10) {
        digits++;
        number = number/10;
    }
    return digits;
}

AOC_DAY(Day07_2){

    std::string line;
    std::size_t sum = 0;
    // same as part 1 but for permutations in base 3.
    while(getline(cin, line)) {

        long int target = std::stol(line.substr(0,line.find(':')));
        std::stringstream ss(line.substr(line.find(':')+2));
        std::vector<int> numbers;
        int number;
        while (ss >> number)
            numbers.push_back(number);

        long int result;
        auto number_of_operators = numbers.size()-1;
        size_t number_of_permutations = std::pow(3,number_of_operators);

        for (size_t permutation = 0; permutation<number_of_permutations; permutation++) {
            size_t i=0;
            for (int bit = number_of_operators-1; bit >= 0; --bit) {

                int operation = (permutation / (int)std::pow(3,bit)) % 3;
                if (bit == number_of_operators-1) //first computation
                {
                    if (operation == 0)      // sum
                        result = numbers[i] + numbers[i+1];
                    else if (operation ==  1) //product
                        result = numbers[i]*numbers[i+1];
                    else // concatenate
                        result = numbers[i]*std::pow(10,compute_number_of_digits(numbers[i+1])) + numbers[i+1];
                    i+=2;
                } else {
                    if (result > target)
                        break;
                    if (operation ==  0) // sum
                        result += numbers[i];
                    else if (operation ==  1) //product
                        result *= numbers[i];
                    else // concatenate
                        result = result*std::pow(10,compute_number_of_digits(numbers[i])) + numbers[i];;
                    i++;
                }
            }
            if (result == target) {
                sum+=target;
                break;
            }
        }
    }

    return std::to_string(sum);
}
