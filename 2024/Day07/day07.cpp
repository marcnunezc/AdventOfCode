size_t compute_number_of_digits(long int number) {
    size_t digits = 1;
    while(number/10) {
        digits++;
        number = number/10;
    }
    return digits;
}

bool compute_operation(std::vector<int>& numbers, long int target, long int result, size_t number_of_operators, int operation, int i_operation, bool part_2 = false) {

    if (i_operation>number_of_operators)
        return target == result;

    if (result > target)
        return false;

    if (i_operation == 0) {
        if (operation==0) // sum
            result = numbers[i_operation] + numbers[i_operation+1];
        else if (operation==1)          //product
            result = numbers[i_operation]*numbers[i_operation+1];
        else
            result = numbers[i_operation]*std::pow(10,compute_number_of_digits(numbers[i_operation+1])) + numbers[i_operation+1];

        i_operation+=2;
    } else {
        if (operation==0) // sum
            result += numbers[i_operation];
        else if (operation==1)          //product
            result *= numbers[i_operation];
        else // concatenate
            result = result*std::pow(10,compute_number_of_digits(numbers[i_operation])) + numbers[i_operation];;
        i_operation++;
    }

    if (compute_operation(numbers, target, result, number_of_operators, 0, i_operation, part_2))
        return true;
    if (compute_operation(numbers, target, result, number_of_operators, 1, i_operation, part_2))
        return true;
    if (part_2 && compute_operation(numbers, target, result, number_of_operators, 2, i_operation, part_2))
        return true;

    return false;

}


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

        if (compute_operation(numbers, target, result, number_of_operators, 0, 0)) {
            sum+=target;
            continue;
        }
        if (compute_operation(numbers, target, result, number_of_operators, 1, 0)) {
            sum+=target;
            continue;
        }
    }

    return std::to_string(sum);
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

        if (compute_operation(numbers, target, result, number_of_operators, 0, 0, true)) {
            sum+=target;
            continue;
        }
        if (compute_operation(numbers, target, result, number_of_operators, 1, 0, true)) {
            sum+=target;
            continue;
        }
        if (compute_operation(numbers, target, result, number_of_operators, 2, 0, true)) {
            sum+=target;
            continue;
        }
    }

    return std::to_string(sum);
}
