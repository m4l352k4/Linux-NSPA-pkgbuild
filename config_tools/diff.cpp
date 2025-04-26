// clang-format off
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
#define FOR(i,l,r) for(auto i=(l);i<=(r);++i)
#define REP(i,n) FOR(i,0,(n)-1)
#define ssize(x) int(x.size())
template<class A,class B>auto&operator<<(ostream&o,pair<A,B>p){return o<<"("<<p.first<<", "<<p.second<<")";}
template<class T>auto operator<<(ostream&o,T x)->decltype(x.end(),o){o<<"{";int i=0;for(auto e:x)o<<(", ")+2*!i++<<e;return o<<"}";}
#ifdef DEBUG
#define debug(x...) cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...);}(x),cerr<<'\n'
#else
#define debug(...) {}
#endif
// clang-format on

struct Config
{
    unordered_map<string, string> data;
    Config(string fn)
    {
        ifstream f(fn);
        string line;
        while (getline(f, line)) {
            if (line.empty() || line[0] == '#') continue;
            auto it   = line.find("=");
            auto key  = line.substr(0, it);
            auto val  = line.substr(it + 1);
            data[key] = val;
        }
    }
};

void
compare(Config& A, Config& B)
{
    vector<string> common;

    // Only in A
    cout << "Only in A:\n";
    for (const auto& a : A.data) {
        const auto& [key, val] = a;
        if (B.data.count(key)) common.emplace_back(key);
        cout << key.c_str() << "=" << val.c_str() << "\n";
    }
    cout << "\n";

    // Only in B
    cout << "Only in B:\n";
    for (const auto& b : B.data) {
        const auto& [key, val] = b;
        if (A.data.count(key)) continue;
        cout << key.c_str() << "=" << val.c_str() << "\n";
    }
    cout << "\n";

    // Compare common settings:
    cout << "Common diff:\n";
    for (const auto& key : common) {
        const auto &aval = A.data[key], &bval = B.data[key];
        if (aval == bval) continue;
        cout << key.c_str() << ": " << "'" << aval.c_str() << "' -> '" << bval.c_str() << "'\n";
    }
}

int
main(int argc, char* argv[])
{
    cin.tie(0)->sync_with_stdio(0);
    if (argc != 3) {
        cout << "Usage: diff [FILE1] [FILE2]\n\n"
            << " displays difference between two kernel config files\n";
        exit(0);
    }
    assert(argc == 3);
    string fn1(argv[1]);
    string fn2(argv[2]);

    Config c1(fn1);
    Config c2(fn2);

    compare(c1, c2);
    return 0;
}
