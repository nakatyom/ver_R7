#include <fstream>
#include <string>

int main(int argc, char *argv[]){
    std::ofstream writing_file;
    std::string filename = "sample.txt";
    writing_file.open(filename, std::ios::out);
    std::string writing_text = "test C++ file. ETrobo HCM icg nkn zud";
    writing_file << writing_text << std::endl;
    writing_file.close();
    return 0;
}