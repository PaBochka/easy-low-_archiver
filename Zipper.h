#include <iostream>
#include <vector>
#include <string>

class Zipper {
public:
    std::vector<std::string> files;
    std::string path;
    std::string real_bin_file;
public:
    Zipper(std::vector<std::string> &vec, std::string p);
    void getInfo();
    void Archive();
    void unArchive(std::string bin_file);
    static std::string get_file_name(std::string fn);
    int digs(double w);
    ~Zipper();
};