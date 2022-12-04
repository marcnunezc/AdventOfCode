AOC_DAY(Day04_1){
    std::string line;
    int f1,f2,s1,s2, counter = 0;
    while (getline(cin, line)) {
        sscanf(line.c_str(), "%i-%i,%i-%i", &f1, &f2, &s1, &s2);
<<<<<<< HEAD
        if ((f1 <= s1 && s2 <= f2) || (s1 <= f1 && f2 <= s2)) {
=======
        if ((f1 <= s1 && s1 <= f2 && f1 <= s2 && s2 <= f2) || (s1 <= f1 && f1 <= s2 && s1 <= f2 && f2 <= s2)) {
>>>>>>> e0a4875a17fc5f8b515fc81726b261dc59d59e23
            counter++;
        }
    }
    cout << counter << endl;
}

AOC_DAY(Day04_2){
    std::string line;
    int f1,f2,s1,s2, counter = 0;
    while (getline(cin, line)) {
        sscanf(line.c_str(), "%i-%i,%i-%i", &f1, &f2, &s1, &s2);
<<<<<<< HEAD
        if ((f1 <= s1 && s1 <= f2) || (s1 <= f1 && f1 <= s2)) {
=======
        if ((f1 <= s1 && s1 <= f2 || f1 <= s2 && s2 <= f2) || (s1 <= f1 && f1 <= s2 || s1 <= f2 && f2 <= s2)) {
>>>>>>> e0a4875a17fc5f8b515fc81726b261dc59d59e23
            counter++;
        }
    }
    cout << counter << endl;
}
