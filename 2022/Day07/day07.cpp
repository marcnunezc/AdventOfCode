class FileSystem {
    std::string mName;
    FileSystem* mpParentDir;
    std::size_t mSize;
    std::vector<FileSystem> mDirs;
    std::vector<FileSystem> mFiles;
    public:
        FileSystem(std::string name, std::size_t size, FileSystem* p_parent_dir=nullptr) : mName(name), mSize(size), mpParentDir(p_parent_dir) {};
        FileSystem* pGetParent() {
            return mpParentDir;
        }
        void AddDir(FileSystem& new_dir) {
            mDirs.push_back(new_dir);
        };
        void AddFile(FileSystem& new_file) {
            for (auto& this_file : mFiles) {
                if (new_file.GetName().compare(this_file.GetName()) == 0) {
                    return;
                }
            }
            mFiles.push_back(new_file);
        };
        std::string GetName() {
            return mName;
        };
        std::size_t GetSize() {
            return mSize;
        };
        FileSystem& GetDir(std::string name) {

            for (auto& this_dir : mDirs) {
                if (name.compare(this_dir.GetName()) == 0)
                    return this_dir;
            }
            cout << "DIR NOT FOUND. looked for: " << name << endl;
            return *this;
        }

        void PrintDirsAndFiles() {
            if (mpParentDir)
                cout << "--- " << mName << "(dir) with parent:" << mpParentDir->GetName() <<endl;
            for (auto& this_file : mFiles) {
                cout << "------- "<< this_file.GetName() << " "<< this_file.GetSize() << endl;
            }
            for (auto& this_dir : mDirs) {
                cout << "------- "<< this_dir.GetName() << endl;
                this_dir.PrintDirsAndFiles();
            }

        }

        int FillSizesMap(std::vector<int>& sizes_vector) {
            int size=0;
            for (auto& this_file : mFiles) {
                size += this_file.GetSize();
            }
            for (auto& this_dir : mDirs) {
                size += this_dir.FillSizesMap(sizes_vector);
            }
            sizes_vector.push_back(size);
            return size;
        }
};




void parse_command(std::string command, FileSystem& root_dir) {

    if (command[0] == '$') {
        if(command.find("cd") != string::npos) {
            std::string dir = command.substr(5, string::npos);
            std::string newcommand;
            getline(cin, newcommand);
            if (dir.compare("..")==0)
                parse_command(newcommand, *root_dir.pGetParent());
            else
                parse_command(newcommand, root_dir.GetDir(dir));
        }
        else if (command.find("ls") != string::npos)
        {
            std::string newcommand;
            getline(cin, newcommand);
            int eof=0;
            while(newcommand.find("$") == string::npos) {
                if(newcommand.find("dir") != string::npos) {
                    std::string dir = newcommand.substr(4, string::npos);
                    FileSystem new_dir = FileSystem(dir, 0, &root_dir);
                    root_dir.AddDir(new_dir);
                } else {
                    int whitespace = newcommand.find(" ");
                    int size = std::stoi(newcommand.substr(0, whitespace));
                    auto file = newcommand.substr(whitespace+1, string::npos);
                    FileSystem new_file = FileSystem(file, size, &root_dir);
                    root_dir.AddFile(new_file);
                }
                getline(cin, newcommand);
                if (cin.eof() && eof++==1)
                    return;
            }
            parse_command(newcommand, root_dir);
        }
    }
}

AOC_DAY(Day07_1){

    std::string line;
    getline(cin, line);
    FileSystem root_dir("/", 0);
    while (getline(cin, line)) {
        parse_command(line, root_dir);
    }

    std::vector<int> sizes_vector;
    root_dir.FillSizesMap(sizes_vector);

    int total=0;
    for (auto value : sizes_vector) {
        if (value <= 100000)
            total += value;
    }

    return std::to_string(total);
}

AOC_DAY(Day07_2) {

    std::string line;
    getline(cin, line);
    FileSystem root_dir("/", 0);
    while (getline(cin, line)) {
        parse_command(line, root_dir);
    }

    std::vector<int> sizes_vector;
    root_dir.FillSizesMap(sizes_vector);

    int min_valid_dir = 70000000;
    for (auto value : sizes_vector) {
        if (40000000 - sizes_vector.back() + value > 0)
            min_valid_dir = min(min_valid_dir, value);
    }
    return std::to_string(min_valid_dir);
}
