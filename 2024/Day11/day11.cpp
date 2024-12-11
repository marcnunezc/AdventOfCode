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
    std::size_t sum = 0;

    std::vector<std::size_t> numbers;
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
            // cout <<"i "<< i << " "<< x << endl;
        } else {
            // cout << "i " <<i<<" " << x << endl;
            p_node->value = x;
            // cout << x << endl;
            node_list[i-1]->next = p_node;
        }
        node_list.push_back(p_node);
        node_count++;
        i++;
    }
    // auto print_node = p_first;
    // while (print_node) {
    //     cout << print_node->value << " ";
    //     print_node = print_node->next;
    // }
    // cout << endl;

    int max_rounds = 25;
    for (int count=0; count < max_rounds; count++) {
        // cout << "count "<<count << " node_count " << node_count<<  endl;
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
        // auto print_node = p_first;
        // while (print_node) {
        //     cout << print_node->value << " ";
        //     print_node = print_node->next;
        // }
        // cout << endl;
    }

    return std::to_string(node_count);
}


AOC_DAY(Day11_2){

    std::string line;
    std::size_t sum = 0;


    return std::to_string(sum);
}
