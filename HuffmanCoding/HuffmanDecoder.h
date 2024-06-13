#ifndef HUFFMAN_DECODER_H
#define HUFFMAN_DECODER_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <unordered_map>
#include "HuffmanEncoder.h"  
#include <sstream>


class HuffmanDecoder {
public:
    /**
     * @brief Dekompresuje vstupn� s�bor Huffman k�dovan�.
     *
     * @param inputFileName N�zov vstupn�ho s�boru pre dekompresiu.
     * @param outputFileName N�zov v�stupn�ho s�boru pre p�vodn� text.
     */
    void decompress(const char* inputFileName, const char* outputFileName);

private:
    /**
     * @brief Rekurz�vne dek�duje bin�rny re�azec pomocou Huffman stromu.
     *
     * @param currentNode Aktu�lny uzol Huffman stromu.
     * @param currentIndex Aktu�lny index v bin�rnom re�azci.
     * @param binaryString Bin�rny re�azec na dek�dovanie.
     * @param outputStream V�stupn� pr�d pre dek�dovan� text.
     */
    void decode(Node* currentNode, int& currentIndex, const string& binaryString, ofstream& outputStream);

    /**
     * @brief Konvertuje cel� ��slo na bin�rny re�azec.
     *
     * @param decimalValue Cel� ��slo, ktor� sa m� konvertova� na bin�rny re�azec.
     * @return Bin�rny re�azec prevzat� z vstupn�ho cel�ho ��sla.
     */
    string decimalToBinaryString(unsigned int decimalValue);

    /**
     * @brief Dek�duje cel� bin�rny re�azec pomocou Huffman stromu.
     *
     * @param root Kore� Huffman stromu.
     * @param binaryString Bin�rny re�azec na dek�dovanie.
     * @param outputStream V�stupn� pr�d pre dek�dovan� text.
     */
    void decodeString(Node* root, const string& binaryString, ofstream& outputStream);

    /**
     * @brief Konvertuje zoznam cel�ch ��sel na jednotn� bin�rny re�azec.
     *
     * @param listOfValues Zoznam cel�ch ��sel, ktor� sa m� konvertova� na bin�rny re�azec.
     * @return Bin�rny re�azec prevzat� zo vstupn�ho zoznamu cel�ch ��sel.
     */
    string bitsToString(const list<unsigned int>& listOfValues);

    /**
     * @brief Na��ta d�ta zo vstupn�ho s�boru do zoznamu cel�ch ��sel.
     *
     * @param input Vstupn� pr�d, z ktor�ho sa ��taj� d�ta.
     * @return Ve�kos� bin�rneho re�azca, ktor� bol pre��tan� zo vstupn�ho s�boru.
     */
    unsigned int loadToList(ifstream& input);

    /**
     * @brief �trukt�ra pre porovn�vanie dvoch uzlov Huffman stromu pod�a frekvencie.
     */
    struct comp {
        bool operator()(Node* a, Node* b) {
            return a->freq > b->freq;
        }
    };

    unordered_map<char, int> frequence; /**< Frekvencia jednotliv�ch znakov vstupn�ho textu. */
    list<unsigned int> bits; /**< Bin�rny re�azec pre��tan� zo vstupn�ho s�boru. */
    char nula = '\0'; /**< �peci�lny znak ozna�uj�ci za�iatok bin�rneho re�azca. */

    priority_queue<Node*, vector<Node*>, comp> BuildTree(unordered_map<char, int>& freq);
};

#endif // HUFFMAN_DECODER_H
