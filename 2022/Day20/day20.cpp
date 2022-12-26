struct double_linked_list {
    int value;
    double_linked_list* prev;
    double_linked_list* next;
};
AOC_DAY(Day20_1) {
    std::vector<int> values;
    std::vector<double_linked_list*> linked_list_vector;
    int x, x_next;
    int i=0;
    cin >> x;
    double_linked_list* start = new double_linked_list;
    start->value = x;
    double_linked_list* p_null_value;
    while(cin >> x_next) {
        double_linked_list* next = start;
        next->prev = start;
        next->value = x_next;
        start->next = next;
        if (start->value == 0)
            p_null_value = start;
        linked_list_vector.push_back(start);
        auto prev = start;
        start = new double_linked_list;
        start->value = x_next;
        start->prev = prev;
    }
    start->next = linked_list_vector.front();
    linked_list_vector.push_back(start);
    linked_list_vector.front()->prev = linked_list_vector.back();

    for (auto p_value : linked_list_vector) {
        // cout << p_value->value << " next is " << p_value->next->value<<" prev is " << p_value->prev->value<<  endl;
        int steps = 0;
        auto printing = p_value;
        auto* next = p_value;
        // cout << "hey " << endl;
        while (steps < linked_list_vector.size()) {
            cout << printing -> value << " ";
            next = printing->next;
            if (next)
                printing = next;
            steps++;
        }
        cout << endl;

        // int count = 0;
        // if (p_value->value > 0) {
        //     linked_list next = p_value->next;
        //     while (count++ < (p_value->value-1)) {
        //         next = next->next;
        //     }
        //     linked_list* aux_p_value = p_value;
        //     linked_list* aux_next = next->next;
        //     p_value->prev->next = p_value->next;
        //     next->next = aux_p_value;
        //     p_value->next = aux_next->next;
        //     p_value->prev = next;
        // } else (p_value->value < 0) {
        //     linked_list prev = p_value->prev;
        //     while (count++ < (std::abs(p_value->value)-1)) {
        //         prev = prev->prev;
        //     }
        //     linked_list* aux_p_value = p_value;
        //     linked_list* aux_prev = prev->prev;
        //     p_value->next->prev = p_value->prev;
        //     prev->prev = aux_p_value;
        //     p_value->prev = aux_prev->prev;
        //     p_value->next = prev;
        // }
    }

    cout << endl;
    return std::to_string(2);
}

AOC_DAY(Day20_2) {

    return std::to_string(3);
}