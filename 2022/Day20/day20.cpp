struct double_linked_list {
    long int value;
    double_linked_list* prev;
    double_linked_list* next;
};

void perform_movement(double_linked_list* p_value, int size) {
    int count = 0;
    if (p_value->value > 0) {
        //pop p_value
        auto aux_p_value = p_value;
        p_value->prev->next = aux_p_value->next;
        p_value->next->prev = aux_p_value->prev;
        auto next = p_value->next;
        int limit = p_value -> value < size ? p_value -> value : p_value -> value % (size-1);
        while (++count < limit) {
            next = next->next;
        }
        auto next_next = next->next;
        //insert p_value
        next->next = aux_p_value;
        p_value->next = next_next;
        p_value->prev = next;
        next_next -> prev = p_value;

    } else if (p_value->value < 0) {
        auto aux_p_value = p_value;
        //pop p_value
        p_value->prev->next = aux_p_value->next;
        p_value->next->prev = aux_p_value->prev;
        auto prev = p_value->prev;
        int limit = -1L*(p_value -> value) < size ? -1L*(p_value -> value) : -1L*(p_value -> value) % (size-1);
        while (++count < limit) {
            prev = prev->prev;
        }
        auto prev_prev = prev->prev;

        //insert p_value
        prev->prev = aux_p_value;
        p_value->prev = prev_prev;
        p_value->next = prev;
        prev_prev->next = p_value;
    }
}

AOC_DAY(Day20_1) {
    std::vector<int> values;
    std::vector<double_linked_list*> linked_list_vector;
    int x;
    double_linked_list* p_null_value;
    while(cin >> x) {
        auto node = new double_linked_list;
        node->value = x;
        if (x==0)
            p_null_value = node;
        linked_list_vector.push_back(node);
    }
    for (int i=0; i<linked_list_vector.size(); i++) {
        if (i==0)
            linked_list_vector[i]->prev = linked_list_vector.back();
        else
            linked_list_vector[i]->prev = linked_list_vector[i-1];
        if (i==linked_list_vector.size()-1)
            linked_list_vector[i]->next = linked_list_vector.front();
        else
            linked_list_vector[i]->next = linked_list_vector[i+1];
    }

    for (auto p_value : linked_list_vector) {
        perform_movement(p_value, linked_list_vector.size());
    }
    auto node = p_null_value;
    int steps = 0;
    int sum = 0;
    while (true) {

        if ((steps) % 1000 == 0)
            sum += node -> value;
        if (steps == 3000)
            break;
        steps++;
        node = node->next;
    }

    return std::to_string(sum);
}

AOC_DAY(Day20_2) {
    std::vector< long  int> values;
    std::vector<double_linked_list*> linked_list_vector;
    long int x;
    double_linked_list* p_null_value;
    while(cin >> x) {
        auto node = new double_linked_list;
        node->value = x*811589153L;
        if (x==0)
            p_null_value = node;
        linked_list_vector.push_back(node);
    }
    for (int i=0; i<linked_list_vector.size(); i++) {
        if (i==0)
            linked_list_vector[i]->prev = linked_list_vector.back();
        else
            linked_list_vector[i]->prev = linked_list_vector[i-1];
        if (i==linked_list_vector.size()-1)
            linked_list_vector[i]->next = linked_list_vector.front();
        else
            linked_list_vector[i]->next = linked_list_vector[i+1];
    }

    for (int i=0; i<10; i++) {
        for (auto p_value : linked_list_vector) {
            perform_movement(p_value, linked_list_vector.size());
        }
    }
    auto node = p_null_value;
    int steps = 0;
    long int sum = 0;
    while (true) {

        if ((steps) % 1000 == 0)
            sum += node -> value;
        if (steps == 3000)
            break;
        steps++;
        node = node->next;
    }

    return std::to_string(sum);
}