#include <sstream>
#include <iostream>
#include <set>
#include <map>

#include "util/md5.hpp"

using namespace std;

struct HashMetaData
{
    string hash;
    char tripplet;
    set<char> groups;
};

map<int, HashMetaData> cache;
map<string, string> hashCache;

int getTrippletIdx(string hash)
{
    for (int idx = 0; idx < hash.length() - 2; ++idx)
        if (hash[idx] == hash[idx + 1] && hash[idx] == hash[idx + 2])
            return idx;
    return -1;
}

string stretch(string hash)
{
    MD5Hash md5;
    string strechedHash = hash;
    for (int count = 0; count < 2016; ++count)
    {
        md5.clear();
        md5.digestMessage(strechedHash);
        hashCache[strechedHash] = md5.getHash();
        strechedHash = hashCache[strechedHash];
    }

    return strechedHash;
}

HashMetaData analyzeHash(string prefix, int id, bool stretchHash)
{
    if (cache.find(id) != cache.end())
        return cache[id];

    MD5Hash md5;
    stringstream hashStream;
    hashStream << prefix << id;
    md5.digestMessage(hashStream.str());

    string hash = md5.getHash();

    if (stretchHash == true)
        hash = stretch(hash);

    HashMetaData hg;

    if (getTrippletIdx(hash) != -1)
        hg.tripplet = hash[getTrippletIdx(hash)];
    else
        hg.tripplet = -1;

    for (int idx = 0; idx < hash.length() - 4; ++idx)
    {
        bool isGroup = true;
        for (int offset = 1; offset < 5; ++offset)
        {
            if (hash[idx + offset] != hash[idx])
            {
                isGroup = false;
                break;
            }
        }
        if (isGroup)
            hg.groups.insert(hash[idx]);
    }

    cache[id] = hg;

    return hg;
}

int findValidHashes(string prefix, bool stretchHash)
{
    int id = 1, foundHashes = 0;

    while (foundHashes < 64)
    {
        HashMetaData meta = analyzeHash(prefix, id, stretchHash);

        if (meta.tripplet != -1)
        {
            for (int offset = 1; offset <= 1000; ++offset)
            {
                HashMetaData lookahead = analyzeHash(prefix, id + offset, stretchHash);

                if (lookahead.groups.find(meta.tripplet) != lookahead.groups.end())
                {
                    foundHashes++;
                    break;
                }
            }
        }

        id++;
    }
    return id - 1;
}

int main()
{
    cout << findValidHashes("ihaygndm", false) << endl;

    cache.clear();

    cout << findValidHashes("ihaygndm", true) << endl;
}