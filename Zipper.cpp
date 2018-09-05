#include "Zipper.h"
#include <vector>
#include <iostream>
#include <string>
#include <string.h>
Zipper::Zipper(std::vector<std::string> &vec, std::string p)
{
    if(vec.size()>0)
        files.assign(vec.begin(), vec.end());
    path = p + "/";
    real_bin_file = path + "binary.zipper";
}
int Zipper::digs(double w)
{
    int yield = 0;
    while(w > 10)
    {
        yield++;
        w /= 10;
    }
    return yield + 1;
}
std::string Zipper::get_file_name(std::string fn)
{
    return fn.substr(fn.find_last_of("/") + 1, fn.size());
}
void Zipper::Archive()
{
    char byte[1];
    getInfo();
    FILE* f;
    FILE* main = fopen((this->real_bin_file).c_str(), "wb");
    FILE* info = fopen((this->path + "info.txt").c_str(), "rb");

    while(!feof(info))
    {
        
        if(fread(byte, 1, 1, info) == 1)
            fwrite(byte ,1, 1, main);
    }
    fclose(info);
    remove((this->path + "info.txt").c_str());
    for(std::vector<std::string>::iterator i = this->files.begin(); i != this->files.end(); ++i)
    {
        std::cout << *i << std::endl;
        f = fopen((*i).c_str(), "rb");
        if(!f)
        {
            std::cout << *i << " not found" << std::endl;
            break; 
        }
        while(!feof(f))
        {
            if(fread(byte, 1, 1, f) == 1)
                fwrite(byte, 1, 1, main);
        }
        std::cout << *i << " add to achive" << this->real_bin_file << "." << std::endl;
        fclose(f);
    }
    fclose(main);
}
void Zipper::getInfo()
{
    char byte[1];
    std::basic_string<char> s_info = "";
    remove ((this->path + "info.txt").c_str());
    FILE* info = fopen((this->path + "info.txt").c_str(), "a+");
    int bytes_size = 0;
    for(std::vector<std::string>::iterator i = this->files.begin(); i != this->files.end(); ++i)
    {
        FILE* f = fopen((*i).c_str(), "rb");
        if(!f) 
            break;
        fseek(f, 0, SEEK_END);
        int size = ftell(f);
        std::string name = Zipper::get_file_name(*i);
        char* m_size = new char[digs(size)];
        snprintf(m_size, size, "%d");
        fclose(f);
        bytes_size += digs(size);
        bytes_size += strlen(name.c_str());
        s_info.append(m_size);
        s_info.append("||");
        s_info.append(name);
        s_info.append("||");
        delete [] m_size;
    }
    bytes_size = s_info.size() + 2;
    char* b_buff = new char[digs(bytes_size)];
    snprintf(b_buff, bytes_size, "%d");

    if(digs(bytes_size) < 5)
        fputs(std::string(5 - digs(bytes_size), '0').c_str(), info);
    fputs(b_buff, info);
    fputs("||", info);
    fputs(s_info.c_str(), info);
    fclose(info);
}
void Zipper::unArchive(std::string bin_file)
{
    FILE* bin = fopen(bin_file.c_str(), "rb");
    char info_block_size[5];
    fread(info_block_size, 1, 5, bin);
    int _sz = atoi(info_block_size);
    char *info_block = new char[_sz];
    fread(info_block, 1, _sz, bin);

    std::vector<std::string> tokens;
    char* tok = strtok(info_block, "||");
    int toks = 0;
    while(tok)
    {
        if(strlen(tok) == 0)
        {
            break;
        }
        tokens.push_back(tok);
        tok = strtok(NULL, "||");
        ++toks;
    } 
    if(toks % 2 == 1) 
    {
        --toks;
    }
    char byte[1];
    int files = toks / 2;
    for(int i = 0; i < files; i++)
    {
        // const char* size = (tokens[i * 2].c_str());
        // const char* name = (tokens[i * 2 + 1].c_str());
        char full_path[255];
        strcpy(full_path, this->path.c_str());
        strcat(full_path, (tokens[i * 2 + 1].c_str()));
        int _sz = atoi((tokens[i * 2].c_str()));
        std::cout << "-- " << (tokens[i * 2 + 1].c_str()) << " unarchive in " << this->path << " ." << std::endl;
        FILE* curr = fopen(full_path, "wb");
        for(int r = 0; r < _sz; r++)
        {
            if(fread(byte, 1, 1, bin) == 1)
            {
                fwrite(byte, 1, 1, curr);
            }
        }
        fclose(curr);
        
        for(auto ch: full_path)
        {
            ch = NULL;
        }
        
    }
    fclose(bin);
    tokens.~vector();
}