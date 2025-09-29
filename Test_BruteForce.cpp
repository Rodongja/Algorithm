#include <iostream>
#include <fstream>
#include <string>
#include "BruteForce.h" // BruteForce �ñ״�ó�� �°� ����

using namespace std;

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string filePath;
    string pattern;

    // ����� �μ��� ������ ���, ������ ���ͷ�Ƽ�� �Է�
    if (argc >= 3) {
        filePath = argv[1];
        // argv[2]���� ���Ͽ� ������ ���ٰ� ����. ���� ���� �����ϰ� �Ϸ���
        // ���� argv�� ��ġ���� �߰��� ó���� �� ����.
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
    int patLen = static_cast<int>(pattern.size()); // BruteForce�� int�� ����ϸ� ĳ��Ʈ

    while (std::getline(infile, line)) {
        ++lineNum;
        int textLen = static_cast<int>(line.size());

        // BruteForce �Լ��� char*�� �䱸�ϸ� const_cast ��� (�����ϸ� BruteForce�� const char*�� �ٲټ���)
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