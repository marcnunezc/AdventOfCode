size_t count_digits(long int number) {
    size_t digits = 1;
    while(number/10) {
        digits++;
        number = number/10;
    }
    return digits;
}

struct node {
    long int value;
    node* next = nullptr;
};
AOC_DAY(Day11_1) {

    std::string line;

    std::vector<node*> node_list;
    std::size_t node_count = 0;
    std::size_t x;
    node* p_first = nullptr;
    int i=0;
    while(cin >> x) {
        auto p_node = new node;
        if (!p_first) {
            p_first = p_node;
            p_node->value = x;
        } else {
            p_node->value = x;
            node_list[i-1]->next = p_node;
        }
        node_list.push_back(p_node);
        node_count++;
        i++;
    }

    int max_rounds = 25;
    for (int count=0; count < max_rounds; count++) {
        auto current_node = p_first;
        while (current_node) {
            auto number_of_digits = count_digits(current_node->value);
            if (current_node->value == 0) {
                current_node->value = 1;
            } else if (number_of_digits % 2 == 1) {
                current_node->value *= 2024;
            } else {
                int upper = current_node->value / (int) std::pow(10,number_of_digits/2);
                int lower = current_node->value % (int) std::pow(10,number_of_digits/2);

                current_node->value = upper;
                auto tmp_next = current_node->next;

                auto p_node = new node;
                node_count++;
                p_node->value = lower;
                p_node->next = tmp_next;

                current_node->next = p_node;

                current_node = p_node;
            }
            current_node=current_node->next;
        }
    }

    return std::to_string(node_count);
}


void advance_loop(std::size_t number, int current_depth, int final_depth, std::size_t& count, std::map<std::pair<std::size_t,int>, std::size_t>& cache) {
    auto starting_count = count;
    if (current_depth == final_depth) {
        count++;
        return;
    }

    if (cache.find({number,current_depth})!=cache.end()) {
        count += cache[{number, current_depth}];
        return;
    }

    auto number_of_digits = count_digits(number);
    if (number == 0) {
        advance_loop(1, current_depth+1, final_depth, count,cache);
    } else if (number_of_digits % 2 == 1) {
        advance_loop(number*2024, current_depth+1, final_depth, count,cache);
    } else {
        int upper = number / (int) std::pow(10,number_of_digits/2);
        int lower = number % (int) std::pow(10,number_of_digits/2);
        advance_loop(upper, current_depth+1, final_depth, count, cache);
        advance_loop(lower, current_depth+1, final_depth, count, cache);
    }
    cache[{number, current_depth}] = count-starting_count;
    return;
}

AOC_DAY(Day11_2){


    std::vector<std::size_t> numbers;
    std::map<std::pair<std::size_t,int>, std::size_t> cache;
    std::size_t sum = 0;
    std::size_t x;
    while(cin >> x) {
        numbers.push_back(x);
    }
    int max_rounds = 75;
    for (auto number : numbers) {
        std::size_t count=0;
        advance_loop(number, 0, max_rounds, count, cache);
        sum += count;
    }

    return std::to_string(sum);
}
