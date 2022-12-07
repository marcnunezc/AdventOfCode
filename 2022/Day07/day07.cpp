class FileSystem {
    std::string mName;
    FileSystem* mpParentDir;
    std::size_t mSize;
    std::map<std::string, FileSystem*> mDirs;
    std::map<std::string, FileSystem*> mFiles;
    public:
        FileSystem(std::string name, std::size_t size, FileSystem* p_parent_dir=nullptr) : mName(name), mSize(size), mpParentDir(p_parent_dir) {};
        FileSystem* pGetParent() {
            return mpParentDir;
        }
        void AddDir(FileSystem* p_new_dir) {
            mDirs[p_new_dir->GetName()] = p_new_dir;
        };
        void AddFile(FileSystem* p_new_file) {
            mFiles[p_new_file->GetName()] = p_new_file;
        };
        std::string GetName() {
            return mName;
        };
        std::size_t GetSize() {
            return mSize;
        };
        FileSystem* pGetDir(std::string name) {
            return mDirs[name];
        }

        void PrintDirsAndFiles() {
            if (mpParentDir)
                cout << "--- " << mName << "(dir) with parent:" << mpParentDir->GetName() <<endl;
            for (auto it = mFiles.begin(); it != mFiles.end(); it++) {
                cout << "------- " << it->first << " " << it->second->GetSize() << endl;
            }
            for (auto it = mDirs.begin(); it != mDirs.end(); it++) {
                cout << "------- " << it->first << "(dir)" << endl;
                it->second->PrintDirsAndFiles();
            }


        }

        int FillSizesMap(std::vector<int>& sizes_vector) {
            int size=0;
            for (auto it = mFiles.begin(); it != mFiles.end(); it++)
                size += it->second->GetSize();

            for (auto it = mDirs.begin(); it != mDirs.end(); it++)
                size += it->second->FillSizesMap(sizes_vector);

            sizes_vector.push_back(size);
            return size;
        }
};




void parse_command(std::string command, FileSystem* root_dir) {
    if (command[0] == '$') {
        if(command.find("cd") != string::npos) {
            std::string dir = command.substr(5, string::npos);
            std::string newcommand;
            getline(cin, newcommand);
            if (dir.compare("..")==0)
                parse_command(newcommand, root_dir->pGetParent());
            else
                parse_command(newcommand, root_dir->pGetDir(dir));
        }
        else if (command.find("ls") != string::npos)
        {
            std::string newcommand;
            while(getline(cin, newcommand) && newcommand.find("$") == string::npos) {
                if(newcommand.find("dir") != string::npos) {
                    std::string dir = newcommand.substr(4, string::npos);
                    FileSystem* p_new_dir = new FileSystem(dir, 0, root_dir);
                    root_dir->AddDir(p_new_dir);

                } else {
                    int whitespace = newcommand.find(" ");
                    int size = std::stoi(newcommand.substr(0, whitespace));
                    auto file = newcommand.substr(whitespace+1, string::npos);
                    FileSystem* p_new_file = new FileSystem(file, size, root_dir);
                    root_dir->AddFile(p_new_file);
                }
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
        parse_command(line, &root_dir);
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
        parse_command(line, &root_dir);
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