#include <stdio.h>
int main() {
    // �t�@�C���|�C���^�̐錾�ƃt�@�C���̃I�[�v��
    FILE *fp;
    fp = fopen("sample.txt", "w"); //�t�@�C�������݂��Ȃ��ꍇ�͎����ō쐬�����
    // �t�@�C���̃N���[�Y
    fclose(fp);
    return 0;
}