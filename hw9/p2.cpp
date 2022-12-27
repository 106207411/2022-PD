// author: R10521802

#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
using namespace std;

const int MAX_STR_OBJ = 10;
const int MAX_VARNAME_LEN = 20;
const int MAX_STR_LEN = 50;
int objCnt = 0;


class MyString {
    private:
        string chars;
        string varname;
        // something else ...
    public:
        MyString();
        MyString(char* c);
        MyString(string s);
        ~MyString();
        MyString(const MyString& m);
        // something else ...?
        char& operator[](int i);
        const MyString operator+(const MyString& s2);
        const MyString operator*(int j);
        const MyString& operator=(const MyString& m);
        const MyString& operator=(const string& s);
        const MyString& operator=(const char* c);
        const string getStr();
        const string getVarname();
        void setVarname(string varname);
};

MyString::MyString() {
    this->chars = "";
    this->varname = "";
}
MyString::MyString(char* c) {
    string str(c);
    this->chars = str;
    this->varname = "";
}
MyString::MyString(string s) {
    this->chars = s;
    this->varname = "";
}
MyString::~MyString() {
    // nothing to do
}
MyString::MyString(const MyString& m) {
    this->chars = m.chars;
    this->varname = m.varname;
}
char& MyString::operator[](int i) {
    // if(i < 0 || i >= this->chars.length()) {
    //     cout << "Error: index out of range" << endl;
    //     exit(1);
    // }
    return this->chars[i];
}
const MyString MyString::operator+(const MyString& s2) {
    MyString sum(*this);
    sum.chars += s2.chars;
    return sum;
}
const MyString MyString::operator*(int j) {
    MyString result(*this);
    for(int i = 1; i < j; i++) {
        result.chars += this->chars;
    }
    return result;
}
const MyString& MyString::operator=(const MyString& m) {
    this->chars = m.chars;
    return *this;
}
const MyString& MyString::operator=(const string& s) {
    this->chars = s;
    return *this;
}
const MyString& MyString::operator=(const char* c) {
    string str(c);
    this->chars = str;
    return *this;
}
const string MyString::getStr() {
    return this->chars;
}
const string MyString::getVarname() {
    return this->varname;
}
void MyString::setVarname(string varname) {
    this->varname = varname;
}

MyString& getMyStrByName(MyString** strObjPtrs, string varname) {
    for(int i = 0; i < objCnt; i++) {
        if(strObjPtrs[i]->getVarname() == varname) {
            return *strObjPtrs[i];
        }
    }
}


int main() {
    int n;
    cin >> n;
    MyString* strObjPtrs[MAX_STR_OBJ];
    for (int i = 0; i < n; i++) {
        string cmd;
        cin >> cmd;
        if (cmd == "declare") {
            string varname, varname2;
            cin >> varname;
            cin.ignore();
            getline(cin, varname2);
            // varname2 is a string
            if (varname2.find("\"") != string::npos) {
                string value = varname2.length() > 2 ? varname2.substr(1, varname2.length() - 2) : ""; 
                MyString myStr(value);
                myStr.setVarname(varname);
                strObjPtrs[objCnt] = new MyString(myStr);
                objCnt++;
            } 
            // varname2 is a variable name
            else {
                if (varname2.find("+") != string::npos) {
                    string left = varname2.substr(0, varname2.find("+"));
                    string right = varname2.substr(varname2.find("+") + 1, varname2.length() - varname2.find("+") - 1);
                    MyString myStr = getMyStrByName(strObjPtrs, left) + getMyStrByName(strObjPtrs, right);
                    myStr.setVarname(varname);
                    strObjPtrs[objCnt] = new MyString(myStr);
                } 
                else if (varname2.find("*") != string::npos) {
                    string left = varname2.substr(0, varname2.find("*"));
                    string right = varname2.substr(varname2.find("*") + 1, varname2.length() - varname2.find("*") - 1);
                    MyString myStr = getMyStrByName(strObjPtrs, left) * stoi(right);
                    myStr.setVarname(varname);
                    strObjPtrs[objCnt] = new MyString(myStr);
                }
                else {
                    // avoid change the original object
                    MyString myStr_ = getMyStrByName(strObjPtrs, varname2);
                    MyString myStr(myStr_);
                    myStr.setVarname(varname);
                    strObjPtrs[objCnt] = new MyString(myStr);
                }
                objCnt++;
            }
        } 
        else if (cmd == "assignString") {
            string varname, str;
            cin >> varname;
            cin.ignore();
            getline(cin, str);
            // with index
            if (varname.find("[") != string::npos) {
                int index = stoi(varname.substr(varname.find("[") + 1, varname.find("[") - varname.find("]") - 1));
                varname = varname.substr(0, varname.find("["));
                getMyStrByName(strObjPtrs, varname)[index] = str[1];
            }
            // without index
            else {
                string value = str.length() > 2 ? str.substr(1, str.length() - 2) : "";
                getMyStrByName(strObjPtrs, varname) = value;
            }
        } 
        else if (cmd == "assignObject") {
            string varname, varname2;
            cin >> varname;
            cin.ignore();
            getline(cin, varname2);
            // varname2 is a string
            if (varname2.find("\"") != string::npos) {
                string value = varname2.length() > 2 ? varname2.substr(1, varname2.length() - 2) : ""; 
                getMyStrByName(strObjPtrs, varname) = value;
            }
            // varname2 is a variable name
            else {
                if (varname2.find("+") != string::npos) {
                    string left = varname2.substr(0, varname2.find("+"));
                    string right = varname2.substr(varname2.find("+") + 1, varname2.length() - varname2.find("+") - 1);
                    getMyStrByName(strObjPtrs, varname) = getMyStrByName(strObjPtrs, left) + getMyStrByName(strObjPtrs, right);
                } 
                else if (varname2.find("*") != string::npos) {
                    string left = varname2.substr(0, varname2.find("*"));
                    string right = varname2.substr(varname2.find("*") + 1, varname2.length() - varname2.find("*") - 1);
                    getMyStrByName(strObjPtrs, varname) = getMyStrByName(strObjPtrs, left) * stoi(right);
                }
                else {
                    getMyStrByName(strObjPtrs, varname) = getMyStrByName(strObjPtrs, varname2);
                }
            }
        } 
        else if (cmd == "print") {
            string varname;
            cin >> varname;
            // with index
            if (varname.find("[") != string::npos) {
                int index = stoi(varname.substr(varname.find("[") + 1, varname.find("[") - varname.find("]") - 1));
                varname = varname.substr(0, varname.find("["));
                cout << getMyStrByName(strObjPtrs, varname)[index] << endl;
            }
            // without index
            else {
                cout << getMyStrByName(strObjPtrs, varname).getStr() << endl;
            }
        }
        
    }

    // free memory
    for (int i = 0; i < objCnt; i++) {
        delete strObjPtrs[i];
    }
    delete[] strObjPtrs;
    return 0;

}