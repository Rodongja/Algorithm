#include <iostream>
#include <fstream>
#include <string>
#include "BruteForce.h" // BruteForce 시그니처에 맞게 유지

using namespace std;

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string filePath;
    string pattern;

    // 명령행 인수가 있으면 사용, 없으면 인터랙티브 입력
    if (argc >= 3) {
        filePath = argv[1];
        // argv[2]부터 패턴에 공백이 없다고 가정. 공백 포함 가능하게 하려면
        // 여러 argv를 합치도록 추가로 처리할 수 있음.
        pattern = argv[2];
    }
    else {
        cout << "Enter file path: ";
        std::getline(cin, filePath);
        cout << "Enter pattern to search (can include spaces): ";
        std::getline(cin, pattern);
        if (filePath.empty() || pattern.empty()) {
            cerr << "File path and pattern must not be empty.\n";
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
    int patLen = static_cast<int>(pattern.size()); // BruteForce가 int을 기대하면 캐스트

    while (std::getline(infile, line)) {
        ++lineNum;
        int textLen = static_cast<int>(line.size());

        // BruteForce 함수가 char*을 요구하면 const_cast 사용 (가능하면 BruteForce를 const char*로 바꾸세요)
        int pos = BruteForce(const_cast<char*>(line.c_str()), textLen, 0,
            const_cast<char*>(pattern.c_str()), patLen);

        if (pos >= 0) {
            cout << "line: " << lineNum << ", column: " << (pos + 1)
                << " : " << line << '\n';
        }
    }

    infile.close();
    return 0;
}