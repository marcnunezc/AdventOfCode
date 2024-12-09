AOC_DAY(Day09_1) {

    std::string line;
    std::size_t sum = 0;

    getline(cin, line);
    int file_id=0;
    std::vector<int> result;

    for (std::size_t i = 0; i<line.size(); i++) {
        int value = line[i] - '0';
        if (i%2 == 0) {
            for (int j=0; j<value; j++) {
                result.push_back(file_id);
            }
            file_id++;
        }
        else {
            for (int j=0; j<value; j++) {
                result.push_back(-1);
            }
        }
    }

    size_t front = 0;
    size_t back = result.size()-1;
    while(back>front) {
        while (result[front] != -1)
            front++;
        while (result[back] == -1)
            back--;
        if (back>front)
            std::swap(result[front], result[back]);
    }

    for (std::size_t i = 0; i<front; i++) {
        sum += i*result[i];
    }

    return std::to_string(sum);
}

int compute_length(std::vector<int>& result, int i, int increment) {
    auto value = result[i];
    int length = 0;
    while (result[i] == value) {
        length++;
        i += increment;
    }
    return length;
}

bool found_available_space(std::vector<int>& result, int& i, int increment, int target_length, int limit) {

    int length_dots = 0;
    while (length_dots < target_length) {
        while (result[i] != -1 && i<limit)
            i++;
        if (i >= limit){
            return false;
        }
        length_dots = compute_length(result, i, increment);
        if (length_dots < target_length)
            i++;
    }
    return true;

}

AOC_DAY(Day09_2){

    std::string line;
    std::size_t sum = 0;

    getline(cin, line);
    int file_id=0;
    std::vector<int> result;

    for (std::size_t i = 0; i<line.size(); i++) {
        int value = line[i] - '0';
        if (i%2 == 0) {
            for (int j=0; j<value; j++) {
                result.push_back(file_id);
            }
            file_id++;
        }
        else {
            for (int j=0; j<value; j++) {
                result.push_back(-1);
            }
        }

    }

    int target_id = file_id-1;
    int front = 0;
    int back = result.size()-1;
    while(target_id > 0) {
        front = 0;
        back =  result.size()-1;
        int starting_back = back;
        while (result[back] != target_id || back<0)
            back--;
        if (back<0){
            target_id--;
            continue;
        }
        int length_nums = compute_length(result, back, -1);
        int first_front = front;

        if (found_available_space(result, front, +1, length_nums, back)) {
            for (std::size_t i = 0; i<length_nums; i++) {
                std::swap(result[front+i], result[back-i]);
            }
        }
        target_id--;
    }

    for (std::size_t i = 0; i<result.size(); i++) {
        if (result[i] > 0)
            sum += i*result[i];
    }
    return std::to_string(sum);
}
