#include <fstream>
#include <string>

int main(int argc, char *argv[]){
    std::ofstream writing_file;
    std::string filename = "sample.txt";
    writing_file.open(filename, std::ios::out);
    std::string writing_text = "C++�i�V�[�v���X�v���X�j�́A�ėp�v���O���~���O����̂ЂƂł���B\n���{��b�҂̊Ԃł́u�V�[�v���v���́u�V�[�v���v���v�ƒʏ̂����B";
    writing_file << writing_text << std::endl;
    writing_file.close();
    return 0;
}