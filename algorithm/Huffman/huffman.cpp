//
// Created by Wingrez on 2021/7/17.
//

#include <iostream>
#include <queue>
#include "huffman.h"

void Huffman::Encode(std::ifstream &fin, std::ofstream &fout) {
    CreateFreqTable(fin);
    CreateHuffmanTree();
    MakeHuffmanCode(huffmanTree.size() - 1, "");
    CreateHuffmanHeader();
    HuffmanEncoding(fin, fout);
}

void Huffman::Decode(std::ifstream &fin, std::ofstream &fout) {
    ReadHuffmanHeader(fin);
    if (header.flag[0] != 'h' || header.flag[1] != 'f' || header.flag[2] != 'm') {
        std::cerr << "[Error] Not Huffman file." << std::endl;
        return;
    }
    alphaVariety = header.alphaVariety;
    ReadFreqTable(fin);
    CreateHuffmanTree();
    MakeHuffmanCode(huffmanTree.size() - 1, "");
    HuffmanDecoding(fin, fout);
}

void Huffman::CreateFreqTable(std::ifstream &fin) {
    unsigned char alpha;
    while (fin.read((char*)&alpha, sizeof(unsigned char))) {
        freqTable[alpha].alpha = alpha;
        freqTable[alpha].freq++;
    }
    int pos = 0;
    for (int i = 0; i < HUFFMAN_TABLE_SIZE; i++) {
        if (freqTable[i].freq != 0) {
            freqTable[pos++] = freqTable[i];
            alphaVariety++;
        }
    }
}

void Huffman::CreateHuffmanTree() {
    // 生成哈夫曼树，总结点数为alphaVariety * 2 - 1
    // [0, alphaVariety - 1]存放叶子节点，[alphaVariety, alphaVariety * 2 - 2]存放分支节点
    huffmanTree = std::vector<HuffmanNode>(alphaVariety * 2 - 1);
    std::priority_queue<HuffmanNode, std::vector<HuffmanNode>, std::greater<HuffmanNode>> nodeQueue;
    for (int i = 0; i < alphaVariety; i++) {
        huffmanTable[freqTable[i].alpha] = i;
        huffmanTree[i].index = i;
        huffmanTree[i].alphaFreq.alpha = freqTable[i].alpha;
        huffmanTree[i].alphaFreq.freq = freqTable[i].freq;
        nodeQueue.push(huffmanTree[i]);
    }

    int left, right;
    for (int i = 0; i < alphaVariety - 1; i++) {
        left = nodeQueue.top().index; nodeQueue.pop();
        right = nodeQueue.top().index; nodeQueue.pop();
        huffmanTree[alphaVariety + i].index = alphaVariety + i;
        huffmanTree[alphaVariety + i].alphaFreq.freq = huffmanTree[left].alphaFreq.freq + huffmanTree[right].alphaFreq.freq;
        huffmanTree[alphaVariety + i].left = left;
        huffmanTree[alphaVariety + i].right = right;
        nodeQueue.push(huffmanTree[alphaVariety + i]);
    }


}

void Huffman::HuffmanEncoding(std::ifstream &fin, std::ofstream &fout) {
    // 将编码写入文件
    fout.write((char*)&header, sizeof(HuffmanHeader)); // 写入头部
    fout.write((char*)freqTable, sizeof(AlphaFreq) * alphaVariety);
    fin.clear();
    fin.seekg(std::ios::beg); // 偏移文件指针，从头开始读取
    unsigned char alpha;
    unsigned char writeValue;
    int bitIndex = 0;
    int nodeIndex;
    while (fin.read((char*)&alpha, sizeof(unsigned char))) {
        nodeIndex = huffmanTable[alpha];
        for (char ch: huffmanTree[nodeIndex].code) {
            ch == '0'? CLR_BIT(writeValue, bitIndex) : SET_BIT(writeValue, bitIndex);
            bitIndex++;
            if (bitIndex >= 8) {
                bitIndex = 0;
                fout.write((char*)&writeValue, sizeof(unsigned char));
            }
        }
    }
    if (bitIndex) {
        fout.write((char*)&writeValue, sizeof(unsigned char));
    }
}

void Huffman::HuffmanDecoding(std::ifstream &fin, std::ofstream &fout) {
    fin.seekg(0, std::ios::end);
    long long fileSize = fin.tellg();
    fin.seekg(sizeof(HuffmanHeader) + sizeof(AlphaFreq) * alphaVariety, std::ios::beg);

    int root = huffmanTree.size() - 1;
    int bitIndex = 0;
    unsigned char readValue;
    fin.read((char*)&readValue, sizeof(unsigned char));
    while(fin.tellg() != -1) {
        if (!GET_BIT(readValue, bitIndex) && huffmanTree[root].left != -1) {
            root = huffmanTree[root].left;
        } else if (huffmanTree[root].right != -1){
            root = huffmanTree[root].right;
        }
        bitIndex++;

        if (huffmanTree[root].left == -1 && huffmanTree[root].right == -1) {
            fout.write((char*)&huffmanTree[root].alphaFreq.alpha, sizeof(unsigned char));
            if (fin.tellg() >= fileSize && bitIndex >= header.lastValidBit) {
                break;
            }
            root = huffmanTree.size() - 1;
        }

        if (bitIndex >= 8) {
            bitIndex = 0;
            fin.read((char*)&readValue, sizeof(unsigned char));
        }
    }
}

void Huffman::MakeHuffmanCode(int root, std::string code) {
    // 哈夫曼编码
    if (huffmanTree[root].left != -1 && huffmanTree[root].right != -1) {
        MakeHuffmanCode(huffmanTree[root].left, code + "0");
        MakeHuffmanCode(huffmanTree[root].right, code + "1");
    } else {
        if (code == "") code += "0";
        huffmanTree[root].code = code;
    }
}

unsigned char Huffman::GetLastValidBit(int alphaVariety) {
    // 获取最后一字节有效位个数
    int bits = 0;
    for (int i = 0; i < alphaVariety; i++) {
        bits += huffmanTree[i].alphaFreq.freq * huffmanTree[i].code.size();
        bits &= 0xff;
    }
    bits &= 0x7;
    return bits == 0? 8: bits;
}

void Huffman::ReadHuffmanHeader(std::ifstream &fin) {
    fin.read((char*)&header, sizeof(HuffmanHeader));
}

void Huffman::ReadFreqTable(std::ifstream &fin) {
    fin.read((char*)freqTable, sizeof(AlphaFreq) * alphaVariety);
}

void Huffman::CreateHuffmanHeader() {
    header.flag[0] = 'h';
    header.flag[1] = 'f';
    header.flag[2] = 'm';
    header.alphaVariety = alphaVariety;
    header.lastValidBit = GetLastValidBit(alphaVariety);
}





