#include <algorithm>
#include <bitset>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include "tools.hpp"
#define uChar unsigned char
using namespace std;

HuffmanNode::HuffmanNode(uChar _singleByte, int _frequency)
    : frequency(_frequency), byteCode(_singleByte)
{
    parent = left = right = nullptr;
}

HuffmanNode::HuffmanNode(HuffmanNode *leftNode, HuffmanNode *rightNode)
{
    frequency = leftNode->frequency + rightNode->frequency;
    leftNode->parent = rightNode->parent = this;
    left = (leftNode->byteCode <= rightNode->byteCode) ? leftNode : rightNode;
    right = (leftNode->byteCode > rightNode->byteCode) ? leftNode : rightNode;
    parent = nullptr;
    byteCode = ((int(left->byteCode) + int(right->byteCode)) / 2) % (1 << 8);
}

static bool getFile(string fileName, vector<uChar> &rawData)
{
    bool isGood = false;
    try {
        isGood = tools::openToVector(fileName, rawData);
    } catch (const exception &e) {
        cerr << e.what() << '\n';
    }
    return isGood;
}

static HuffmanNode *mergeHuffmanTree(map<uChar, int> &nodeTable)
{
    priority_queue<HuffmanNode *, vector<HuffmanNode *>, tools::cmpNodes> pq;
    for (auto i : nodeTable) {
        auto newNode = new HuffmanNode(i.first, i.second);
        pq.push(newNode);
    }
    while (pq.size() > 1) {
        auto a = pq.top();
        pq.pop();
        auto b = pq.top();
        pq.pop();

        auto mergedNode = new HuffmanNode(a, b);
        pq.push(mergedNode);
    }

    return pq.top();
}

static void assignCompressCode(HuffmanNode *current, string code)
{
    if (current->left)
        assignCompressCode(current->left, code + "0");
    if (current->left == nullptr && current->right == nullptr)
        current->decompressCode = code;
    if (current->right)
        assignCompressCode(current->right, code + "1");
}

static void recordingLeafs(HuffmanNode *current, vector<HuffmanNode *> &leafs)
{
    if (current->left)
        recordingLeafs(current->left, leafs);
    if (current->left == nullptr && current->right == nullptr)
        leafs.push_back(current);
    if (current->right)
        recordingLeafs(current->right, leafs);
}

static void encoding(vector<HuffmanNode *> &leafs,
                     vector<uChar> &rawData,
                     vector<bool> &encodedData)
{
    map<uChar, string> encodingTable;
    for (auto i : leafs)
        encodingTable.insert(
            pair<uChar, string>(i->byteCode, i->decompressCode));

    for (auto iter = rawData.begin(); iter != rawData.end(); iter++) {
        auto getCode = encodingTable.at(*iter);
        for (auto i : getCode)
            encodedData.push_back(i - '0');  // fill bits into encodedData
    }
}

static string decoding(map<string, uChar> &_table, string &bitStringData)
{
    string tmp, result;
    for (auto iter = bitStringData.begin(); iter != bitStringData.end();
         iter++) {
        tmp.push_back(*iter);
        auto isFound = _table.find(tmp);
        if (isFound != _table.end()) {
            tmp = "";
            result.push_back(char(isFound->second));
        }
    }
    return result;
}

static void writeCompressResult(string inputFileName,
                                vector<HuffmanNode *> leafs,
                                vector<uChar> &rawData)
{
    vector<bool> encodedData;
    string outputName(inputFileName.append(".compress"));
    ofstream outFile(outputName);

    try {
        encoding(leafs, rawData, encodedData);
    } catch (const std::exception &e) {
        std::cerr << e.what() << endl;
    }

    tools::writeHeader(outFile, rawData.size(), encodedData.size(), leafs);
    int peddingDataLength = tools::getPaddingLength(encodedData.size());
    for (int i = 0; i < peddingDataLength; i++)
        encodedData.push_back(0);  // pedding encoded data

    vector<uChar> bodyBytes;
    auto [encodedDataByteArray, encodedDataByteArraySize] =
        tools::toByteArray(encodedData);
    tools::appendByteArray(encodedDataByteArray, encodedDataByteArraySize,
                           bodyBytes);  // bytes to vector
    delete[] encodedDataByteArray;      // release used memory
    for (auto i : bodyBytes)
        outFile << i;

    outFile.close();
}

bool compress(string fileName)
{
    vector<uChar> rawData;
    vector<HuffmanNode *> leafs;
    HuffmanNode *root;
    bool isGoodFile = true;

    // read raw file to vector
    isGoodFile = getFile(fileName, rawData);

    // collect byte frequency in map
    map<uChar, int> nodeTable;  // unsigned char, frequency
    for (auto singleByte : rawData) {
        nodeTable[singleByte]++;
    }

    root = mergeHuffmanTree(nodeTable);
    assignCompressCode(root, "");
    recordingLeafs(root, leafs);
    // tools::printCodingTable(leafs);
    writeCompressResult(fileName, leafs, rawData);
    return isGoodFile;
}

bool decompress(string fileName)
{
    vector<uChar> rawData;
    bool isGoodFile = true;
    HuffmanNode *root;
    map<string, uChar> stringTable;

    // read raw file to vector
    isGoodFile = getFile(fileName, rawData);

    auto [originSize, compressBitsLength, codingTableSize, dataPeddingLength] =
        tools::readHeader(rawData);
    tools::readDecodeTable(rawData, stringTable, codingTableSize);

    string bitStringData = tools::toBitString(rawData, dataPeddingLength);
    rawData.clear();
    rawData.shrink_to_fit();

    string decodedResult = decoding(stringTable, bitStringData);
    // cout << decodedResult;

    ofstream outFile(fileName + string(".decompress"));
    outFile << decodedResult;
    outFile.close();

    // check recover by outSize and originSize
    return (decodedResult.length() == originSize) && isGoodFile;
}
