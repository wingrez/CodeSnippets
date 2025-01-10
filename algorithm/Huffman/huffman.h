//
// Created by Wingrez on 2021/7/17.
//

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <fstream>
#include <string>
#include <vector>

const int HUFFMAN_TABLE_SIZE = 1 << (sizeof(unsigned char) * 8);

// 获取vbyte第index位的值
#define GET_BIT(vbyte, index) (((vbyte) & (1 << ((index) ^ 7))))
// 将vbyte第index位置1
#define SET_BIT(vbyte, index) ((vbyte) |= (1 << ((index) ^ 7)))
// 将vbyte第index位置0
#define CLR_BIT(vbyte, index) ((vbyte) &= (~(1 << ((index) ^ 7))))

#pragma pack(push, 1)

struct HuffmanHeader {
    unsigned char flag[3]{0};
    unsigned int alphaVariety{0};
    unsigned char lastValidBit{0};
    unsigned char unused[8]{0};
};

struct AlphaFreq {
    unsigned char alpha{0};
    unsigned int freq{0};
};

struct HuffmanNode {
    int index{-1};
    AlphaFreq alphaFreq;
    std::string code{""};
    int left{-1};
    int right{-1};

    bool operator>(const HuffmanNode &rhs) const {
        if (alphaFreq.freq == rhs.alphaFreq.freq) {
            return alphaFreq.alpha < rhs.alphaFreq.alpha;
        }
        return alphaFreq.freq > rhs.alphaFreq.freq;
    }
};

class Huffman {
public:
    Huffman() = default;

    ~Huffman() = default;

    void Encode(std::ifstream &fin, std::ofstream &fout);

    void Decode(std::ifstream &fin, std::ofstream &fout);

private:
    HuffmanHeader header;
    unsigned int alphaVariety{0};
    AlphaFreq freqTable[HUFFMAN_TABLE_SIZE];
    unsigned char huffmanTable[HUFFMAN_TABLE_SIZE]{0};
    std::vector<HuffmanNode> huffmanTree;

    void CreateFreqTable(std::ifstream &fin);

    void CreateHuffmanTree();

    void CreateHuffmanHeader();

    void MakeHuffmanCode(int root, std::string code);

    void HuffmanEncoding(std::ifstream &fin, std::ofstream &fout);

    unsigned char GetLastValidBit(int alphaVariety);

    void ReadHuffmanHeader(std::ifstream &fin);

    void ReadFreqTable(std::ifstream &fin);

    void HuffmanDecoding(std::ifstream &fin, std::ofstream &fout);
};

#pragma pack(pop)

#endif //HUFFMAN_H
