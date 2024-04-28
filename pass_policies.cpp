#include "bits/stdc++.h"

using namespace std;
using int16 = uint16_t;

class Policy {
protected:
    bool isChecked;
public:
    virtual void check(const string &pass) = 0;

    bool getCheck() const {
        return isChecked;
    }
};

class LengthPolicy : public Policy {
    int16 minLength, maxLength;
public:
    LengthPolicy(int16 minLength) : minLength(minLength) {
        maxLength = 255;
    }

    LengthPolicy(int16 minLength, int16 maxLength) : minLength(minLength), maxLength(maxLength) {}

    void check(const string &pass) {
        if (pass.length() >= minLength && pass.length() <= maxLength)
            isChecked = true;
        else isChecked = false;
    }
};

class ClassPolicy : public Policy {
    int16 minClassCount;
public:
    ClassPolicy(int16 minClassCount) : minClassCount(minClassCount) {}

    void check(const string &pass) {
        int verf = 0;
        for (auto i: pass)
            if (islower(i)) {
                verf++;
                break;
            }
        for (auto i: pass)
            if (isupper(i)) {
                verf++;
                break;
            }
        for (auto i: pass)
            if (isdigit(i)) {
                verf++;
                break;
            }
        for (auto i: pass)
            if (isdigit(i) == 0 && isalpha(i) == 0) {
                verf++;
                break;
            }
        if (verf >= minClassCount)
            isChecked = true;
        else isChecked = false;

    }

};

class IncludePolicy : public Policy {
    char characterType;
public:
    IncludePolicy(char characterType) : characterType(characterType) {}

    void check(const string &pass) {
        int verf = 0;
        if (characterType == 'a')
            for (auto i: pass)
                if (islower(i)) {
                    verf++;
                    break;
                }

        if (characterType == 'A')
            for (auto i: pass)
                if (isupper(i)) {
                    verf++;
                    break;
                }

        if (characterType == '0')
            for (auto i: pass)
                if (isdigit(i)) {
                    verf++;
                    break;
                }

        if (characterType == '$')
            for (auto i: pass)
                if (isalpha(i) == 0 && isdigit(i) == 0) {
                    verf++;
                    break;
                }

        if (verf != 0)
            isChecked = true;
        else isChecked = false;


    }
};

class NotIncludePolicy : public Policy {
    char characterType;
public:
    NotIncludePolicy(char characterType) : characterType(characterType) {}

    void check(const string &pass) {
        int verf = 0;
        if (characterType == 'a')
            for (auto i: pass)
                if (islower(i)) {
                    verf++;
                    break;
                }

        if (characterType == 'A')
            for (auto i: pass)
                if (isupper(i)) {
                    verf++;
                    break;
                }

        if (characterType == '0')
            for (auto i: pass)
                if (isdigit(i)) {
                    verf++;
                    break;
                }

        if (characterType == '$')
            for (auto i: pass)
                if (isalpha(i) == 0 && isdigit(i) == 0) {
                    verf++;
                    break;
                }

        if (verf != 0)
            isChecked = false;
        else isChecked = true;
    }
};

class RepetitionPolicy : public Policy {
    int16 maxCount;
public:
    RepetitionPolicy(int16 maxCount) : maxCount(maxCount) {}

    void check(const string &pass) {
        int max = 0, count = 0;
        for (int i = 0; i < pass.size() - 1; i++) {
            if (pass[i] == pass[i + 1])
                count++;
            else {
                if (count > max)
                    max = count;
                count = 0;
            }
        }
        if (count > max)
            max = count;
        if (max >= maxCount)
            this->isChecked = false;
        else this->isChecked = true;
    }
};

class ConsecutivePolicy : public Policy {
    int16 maxCount;
public:
    ConsecutivePolicy(int16 maxCount) : maxCount(maxCount) {}

    void check(const string &pass) {
        int max = 0, count = 0;
        for (int i = 0; i < pass.size() - 1; i++) {
            if (int(pass[i]) == int(pass[i + 1]) - 1)
                count++;
            else {
                if (count > max)
                    max = count;
                count = 0;
            }
        }
        if (count > max)
            max = count;
        if (max >= maxCount)
            this->isChecked = false;
        else this->isChecked = true;
    }
};

string checkPassword(string pass, vector<Policy *> cond) {
    string verf = "OK";
    for (auto &i: cond) {
        i->check(pass);
        if (!i->getCheck()) {
            verf = "NOK";
            return verf;
        }
    }
    return verf;
}

int main() {
    int n;
    char caracter;
    vector<Policy *> cond;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string cerinta;
        cin >> cerinta;
        if (cerinta == "length") {
            int16 max = 0, min;
            string a;
            getline(cin, a);
            istringstream iss(a);
            iss >> min;
            if (iss >> max)
                cond.push_back(new LengthPolicy(min, max));
            else cond.push_back(new LengthPolicy(min));
        }
        if (cerinta == "class") {
            int16 min;
            cin >> min;
            cond.push_back(new ClassPolicy(min));
        }
        if (cerinta == "include") {
            cin >> caracter;
            cond.push_back(new IncludePolicy(caracter));
        }
        if (cerinta == "ninclude") {
            cin >> caracter;
            cond.push_back(new NotIncludePolicy(caracter));
        }
        if (cerinta == "repetition") {
            int16 max;
            cin >> max;
            cond.push_back(new RepetitionPolicy(max));
        }
        if (cerinta == "consecutive") {
            int16 max;
            cin >> max;
            cond.push_back(new ConsecutivePolicy(max));
        }

    }
    string parole;
    while(cin>>parole)
cout<<checkPassword(parole,cond)<<endl;
    return 0;
}
