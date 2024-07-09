#include <stdio.h>
int main() {
    // ファイルポインタの宣言とファイルのオープン
    FILE *fp;
    fp = fopen("sample.txt", "w"); //ファイルが存在しない場合は自動で作成される
    // ファイルのクローズ
    fclose(fp);
    return 0;
}