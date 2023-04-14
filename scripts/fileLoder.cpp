#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

struct URL{
    std::string url;
    int index;
    std::string filename;

    void make_numbered_filename(std::string base_name,std::string replace_string){
        size_t pos = base_name.find(replace_string);
        std::string new_string = "";
        if (pos != std::string::npos){
            new_string = base_name;
            new_string.replace(pos, replace_string.length(), std::to_string(pos));
            filename= new_string;
        }else{
            std::cerr << "The given basename does not contain the character to be replaced." << std::endl;
        }
    }

    //initialization
    URL( std::string url, int index )
        :url(url), index(index)
    {}
};