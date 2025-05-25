#include <bits/stdc++.h>
using namespace std;

enum class Op
{
    ADD,
    SUB,
    MUL,
    MOVI,
    JEQ,
    AND,
    XORI,
    JMP,
    LSL,
    LSR,
    MOVR,
    MOVM,
    SKIP,   // Added for skipping if hazard can not be avoided
    UNKNOWN // Added for unknown operations
};

static const unordered_map<string, Op> str2op = {
    {"ADD", Op::ADD}, {"SUB", Op::SUB}, {"MUL", Op::MUL}, {"MOVI", Op::MOVI}, {"JEQ", Op::JEQ}, {"AND", Op::AND}, {"XORI", Op::XORI}, {"JMP", Op::JMP}, {"LSL", Op::LSL}, {"LSR", Op::LSR}, {"MOVR", Op::MOVR}, {"MOVM", Op::MOVM}, {"SKIP", Op::SKIP}};

static int latency(Op op)
{
    return 3;
}

struct Instr
{
    Op op;
    string text;      // original line or "SKIP"
    int dest = -1;    // −1 means “no destination register”
    vector<int> srcs; // registers read
    int id;           // unique global index (−1 for SKIP)
};

static inline bool isReg(const string &t) { return t.size() > 1 && t[0] == 'R'; }
static inline int regNum(const string &t) { return stoi(t.substr(1)); }
static Op toOp(const string &s)
{
    auto it = str2op.find(s);
    return it == str2op.end() ? Op::UNKNOWN : it->second;
}

vector<Instr> parseFile(const string &path)
{
    ifstream in(path);
    if (!in)
        throw runtime_error("cannot open " + path);
    vector<Instr> code;
    string line;
    int id = 0;
    while (getline(in, line))
    {
        if (line.empty())
            continue; // skip empty lines
        if (line[0] == '\n' || line[0] == '\r')
            continue; // skip lines with only newlines
        stringstream ss(line);
        string m;
        ss >> m;
        if (m.empty() || m[0] == ';')
        {
            code.push_back({Op::SKIP, line, -1, {}, id++});
            continue;
        }
        Op op = toOp(m);
        if (op == Op::UNKNOWN)
            throw runtime_error("unknown mnemonic: " + m);

        string t1, t2, t3;
        ss >> t1 >> t2 >> t3;
        Instr ins{op, line, -1, {}, id++};
        switch (op)
        {
        case Op::ADD:
        case Op::SUB:
        case Op::MUL:
        case Op::AND:
            ins.dest = isReg(t1) ? regNum(t1) : -1;
            if (isReg(t2))
                ins.srcs.push_back(regNum(t2));
            if (isReg(t3))
                ins.srcs.push_back(regNum(t3));
            break;
        case Op::MOVI:
            ins.dest = isReg(t1) ? regNum(t1) : -1;
            break;
        case Op::JEQ:
            if (isReg(t1))
                ins.srcs.push_back(regNum(t1));
            if (isReg(t2))
                ins.srcs.push_back(regNum(t2));
            break;
        case Op::XORI:
            ins.dest = isReg(t1) ? regNum(t1) : -1;
            if (isReg(t2))
                ins.srcs.push_back(regNum(t2));
            break;
        case Op::JMP:
            break;
        case Op::LSL:
        case Op::LSR:
            ins.dest = isReg(t1) ? regNum(t1) : -1;
            if (isReg(t2))
                ins.srcs.push_back(regNum(t2));
            break;
        case Op::MOVR:
        case Op::MOVM:
            ins.dest = isReg(t1) ? regNum(t1) : -1;
            if (isReg(t2))
                ins.srcs.push_back(regNum(t2));
            break;
        default:
            break;
        }
        code.push_back(move(ins));
    }
    return code;
}

struct Block
{
    int s, e;
};
vector<Block> makeBlocks(const vector<Instr> &code)
{
    unordered_set<int> leaders = {0};
    for (size_t i = 0; i < code.size(); ++i)
    {
        Op op = code[i].op;
        if (op == Op::JEQ || op == Op::JMP)
            if (i + 1 < code.size())
                leaders.insert(i + 1);
    }
    vector<int> v(leaders.begin(), leaders.end());
    sort(v.begin(), v.end());
    vector<Block> res;
    for (size_t k = 0; k < v.size(); ++k)
    {
        int s = v[k];
        int e = (k + 1 < v.size() ? v[k + 1] : code.size()) - 1;
        res.push_back({s, e});
    }
    return res;
}

vector<int> scheduleBlock(const vector<Instr> &code, Block b)
{
    int n = b.e - b.s + 1;
    if (n == 0)
        return {};

    vector<vector<int>> succ(n);
    vector<int> indeg(n, 0);

    auto loc = [&](int g)
    { return g - b.s; };

    unordered_map<int, int> lastWrite;
    for (int g = b.s; g <= b.e; ++g)
    {
        const auto &I = code[g];
        int i = loc(g);

        for (int r : I.srcs)
            if (lastWrite.count(r))
            {
                int p = lastWrite[r];
                succ[p].push_back(i);
                ++indeg[i];
            }

        if (I.dest != -1)
        {
            if (lastWrite.count(I.dest))
            {
                int p = lastWrite[I.dest];
                succ[p].push_back(i);
                ++indeg[i];
            }
            lastWrite[I.dest] = i;
        }
    }

    struct Node
    {
        int ready, idx;
    };
    auto cmp = [](const Node &a, const Node &b)
    { return a.ready > b.ready; };
    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);

    const int UNDEF = -1;
    vector<int> issue(n, UNDEF);
    vector<int> ready(n, 0);

    for (int i = 0; i < n; ++i)
        if (indeg[i] == 0)
            pq.push({0, i});

    vector<int> order;
    order.reserve(4 * n);
    int cycle = 0;

    while (!pq.empty())
    {
        if (pq.top().ready > cycle)
        {
            order.push_back(-1);
            ++cycle;
            continue;
        }
        int u = pq.top().idx;
        pq.pop();
        issue[u] = cycle;
        order.push_back(u + b.s);
        int done = cycle + latency(code[u + b.s].op);

        for (int v : succ[u])
        {
            ready[v] = max(ready[v], done);
            if (--indeg[v] == 0)
                pq.push({ready[v], v});
        }
        ++cycle;
    }
    return order;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "usage: " << argv[0] << " file.asm\n";
        return 1;
    }
    string inName = argv[1];
    vector<Instr> code = parseFile(inName);
    vector<Block> blocks = makeBlocks(code);

    vector<int> final;
    final.reserve(code.size() * 2);
    for (auto blk : blocks)
    {
        auto v = scheduleBlock(code, blk);
        final.insert(final.end(), v.begin(), v.end());
    }

    string outName = inName.substr(0, inName.find_last_of('.')) + ".scheduled.asm";
    ofstream out(outName);
    for (int g : final)
    {
        if (g == -1)
            out << "SKIP\n";
        else
        {
            if (code[g].text == "")
                out << "SKIP\n";
            else
                out << code[g].text << "\n";
        }
    }
    cout << "output: " << outName << "\n";
    return 0;
}
