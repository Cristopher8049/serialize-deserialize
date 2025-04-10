#include <iostream>
#include <vector>
#include <string>

using namespace std;

string serialize(const vector<string> &strs)
{
    string result;
    for (const auto &s : strs)
    {
        if (s.size() > 255)
        {
            throw runtime_error("String too long to encode in one byte");
        }
        result += static_cast<char>(s.size());
        result += s;
    }
    return result;
}

vector<string> deserialize(const string &data)
{
    vector<string> result;
    size_t i = 0;
    while (i < data.size())
    {
        unsigned char len = static_cast<unsigned char>(data[i]);
        i++;
        result.push_back(data.substr(i, len));
        i += len;
    }
    return result;
}

int main()
{
    vector<string> original = {"hello", "world", "", "cpp"};

    string serialized = serialize(original);
    cout << "Serialized: ";
    for (unsigned char c : serialized)
    {
        if (isprint(c))
            cout << c;
        else
            cout << "[" << (int)c << "]";
    }
    cout << endl;

    vector<string> deserialized = deserialize(serialized);
    cout << "Deserialized:" << endl;
    for (const auto &s : deserialized)
    {
        cout << "- " << s << endl;
    }

    return 0;
}
