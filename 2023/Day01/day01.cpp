AOC_DAY(Day01_1){

    return std::to_string(max);
}

AOC_DAY(Day01_2){


    return std::to_string(std::accumulate(max_values.begin(), max_values.end(), 0));
}
