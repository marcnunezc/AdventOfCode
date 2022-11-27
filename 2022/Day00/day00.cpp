AOC_DAY(Day00_1){
    int value, value_old, counter = 0;
    value_old = std::numeric_limits<int>::max();
    while (cin >> value) {
        if (value > value_old)
            counter++;
        value_old = value;
    }
    cout << counter << endl;
}

AOC_DAY(Day00_2){
    unsigned int counter = 0;
    unsigned int a = 0, b=0, c=0,d=0;
    while (cin >> d) {
        if (a && (b+c+d) > (a+b+c)) {
            counter++;
        }
        a=b;
        b=c;
        c=d;
    }
    cout << counter << endl;
}