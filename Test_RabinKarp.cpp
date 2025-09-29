#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "RabinKarp.h" // 기존 시그니처를 유지한다고 가정

using namespace std;

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string filePath;
    string pattern;

    // 명령행 인수 처리:
    // usage: program <FilePath> <Pattern...>
    if (argc >= 3) {
        filePath = argv[1];
        // 패턴에 공백이 있을 수 있으므로 argv[2] 이후를 모두 합친다
        string combined;
        for (int i = 2; i < argc; ++i) {
            if (i > 2) combined += " ";
            combined += argv[i];
        }
        pattern = combined;
    }
    else {
        cout << "Enter file path: ";
        if (!getline(cin, filePath) || filePath.empty()) {
            cerr << "File path must not be empty.\n";
            return 1;
        }
        cout << "Enter pattern to search (can include spaces): ";
        if (!getline(cin, pattern) || pattern.empty()) {
            cerr << "Pattern must not be empty.\n";
            return 1;
        }
    }

    ifstream infile(filePath);
    if (!infile.is_open()) {
        cerr << "Cannot open file: " << filePath << "\n";
        return 1;
    }

    string line;
    int lineNum = 0;
    // pattern.size()는 size_t 이므로 BrabinKarp가 int를 기대하면 캐스트
    int patLen = static_cast<int>(pattern.size());

    while (std::getline(infile, line)) {
        ++lineNum;

        int textLen = static_cast<int>(line.size());

        // RabinKarp 함수가 (char* text, int textLen, int start, char* pattern, int patLen) 같은 시그니처라면:
        int pos = RabinKarp(const_cast<char*>(line.c_str()), textLen, 0,
            const_cast<char*>(pattern.c_str()), patLen);

        if (pos >= 0) {
            cout << "line: " << lineNum << ", column: " << (pos + 1)
                << " : " << line << '\n';
        }
    }

    infile.close();
    return 0;
}