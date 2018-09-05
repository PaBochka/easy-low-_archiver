#include "Zipper.h"
#include <iostream>
#include <string>
#include <vector>
#include <string.h>

int main(int argc, char *argv[])
{
    std::cout << "######ZIPPER######" << std::endl;
    // if(argc > 1)
    // {
    //     std::vector<std::string> files;
    //     std::string path = "";
    //     bool flag_fs = false, flag_path = false;
    //     char type[6];
    //     memset(type, 0, 6);

    //     for(int i = 1; i < argc; ++i)
    //     {
    //         if(strcmp(argv[i], "-pack") == 0)
    //         {
    //             strcpy(type, "-pack");
    //             flag_fs = flag_path = false;
    //         }
    //         if(strcmp(argv[i], "-unpack") == 0)
    //         {
    //             strcpy(type, "-unpack");
    //             flag_fs = flag_path = false;
    //         }
    //         if(strcmp(argv[i], "-path") == 0)
    //         {
    //             flag_path = true;
    //             flag_fs = false;
    //             continue;
    //         }
    //         if(strcmp(argv[i], "-files") == 0)
    //         {
    //             flag_fs = true;
    //             flag_path = false;
    //             continue;
    //         }
    //         if(flag_path)
    //         {
    //             path.assign(argv[i]);
    //         }
    //         if(flag_fs)
    //         {
    //             files.push_back(std::string(argv[i]));
    //         }
    //     }
    //     Zipper *zip = new Zipper(files, path);
    //     if(strcmp(type, "-pack") == 0)
    //     {
    //         zip->Archive();
    //     }
    //     if(strcmp(type, "-unpack") == 0)
    //     {
    //         zip->unArchive(files[0]);
    //     }
    // }
    std::string path;
    std::string command;
    std::string file;
    //path = "/home/pavel/VScode_proj/unpack";
    std::cout << "change command" << std::endl;
    std::cout << "input command" << std::endl;
    std::cin >> command;
    std::string ch;
    if(command == "-pack")
    {
        std::vector<std::string> files;
        do
        {
            std::cout << "input file" << std::endl;
            std::cin >> file;
            std::cout << file << std::endl;
            files.push_back(file);
            std::cout << "continue [y/n]" << std::endl;
            std::cin >> ch;
        } while (ch == "y");

        std::cout << "input path" << std::endl;
        std::cin >> path;
        std::cout << path << std::endl;

        Zipper *zip = new Zipper(files, path);
        zip->Archive();
        command = "";
        ch = "";
        file = "";
        path = "";
    }
    if(command == "-unpack")
    {
        std::vector<std::string> files;
        
        std::cout << "input file" << std::endl;
        std::cin >> file;
        std::cout << file << std::endl;
        files.push_back(file);

        std::cout << "input path" << std::endl;
        std::cin >> path;
        std::cout << path << std::endl;

        Zipper *zip = new Zipper(files, path);
        zip->unArchive(files[0]);
        command = "";
        ch = "";
        file = "";
        path = "";
    }
    std::cin.get();
    return 0;
}
