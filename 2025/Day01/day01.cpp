AOC_DAY(Day01_1) {

    std::string line;
    std::size_t sum = 0;
    std::size_t lock = 50;
    while (cin >> line)
    {
        char dir = line[0];
        std::size_t move = std::stoul(line.substr(1)) % 100;
        if (line[0]=='L'){
            if (move > lock){
                lock = 100 - (move - lock);
            } else {
                lock -= move;
            }
        } else if (line[0]=='R'){
            lock = (lock + move) % 100;
        }

        if (lock==0)
            sum++;
    }
    return std::to_string(sum);
}

AOC_DAY(Day01_2){
    std::string line;
    std::size_t sum = 0;
    std::size_t lock = 50;
    while (cin >> line)
    {
        char dir = line[0];
        std::size_t move = std::stoul(line.substr(1));
        if (move > 100) {
            sum += move / 100;
            move = move % 100;
        }
        if (line[0]=='L'){
            if (move > lock){
                if (lock != 0)
                    sum++;
                lock = 100 - (move - lock);
            } else {
                lock -= move;
            }
        } else if (line[0]=='R'){
            if (lock + move > 100){
                sum++;
            }
            lock = (lock + move) % 100;
        }

        if (lock==0)
            sum++;
    }
    return std::to_string(sum);
}
