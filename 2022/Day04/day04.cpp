AOC_DAY(Day04_1){
    std::string line;
    int f1,f2,s1,s2, counter = 0;
    while (getline(cin, line)) {
        sscanf(line.c_str(), "%i-%i,%i-%i", &f1, &f2, &s1, &s2);
        if ((f1 <= s1 && s2 <= f2) || (s1 <= f1 && f2 <= s2)) {
            counter++;
        }
    }
    return std::to_string(counter);
}

AOC_DAY(Day04_2){
    std::string line;
    int f1,f2,s1,s2, counter = 0;
    while (getline(cin, line)) {
        sscanf(line.c_str(), "%i-%i,%i-%i", &f1, &f2, &s1, &s2);
        if ((f1 <= s1 && s1 <= f2) || (s1 <= f1 && f1 <= s2)) {
            counter++;
        }
    }
    return std::to_string(counter);
}
