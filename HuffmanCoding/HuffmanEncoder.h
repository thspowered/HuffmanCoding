#ifndef HUFFMAN_ENCODER_H
#define HUFFMAN_ENCODER_H

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

/**
 * @brief �trukt�ra reprezentuj�ca uzol Huffmanovho stromu.
 */
struct Node {
    char ch;      /**< Znak v uzle. */
    int freq;     /**< Frekvencia znaku. */
    Node* left;   /**< Ukazovate� na �av�ho potomka. */
    Node* right;  /**< Ukazovate� na prav�ho potomka. */
};

/**
 * @brief Trieda HuffmanEncoder pre kompresiu textov�ch s�borov.
 */
class HuffmanEncoder {
public:
    /**
     * @brief Kompresuje vstupn� s�bor pomocou Huffmanovho k�dovania a uklad� do v�stupn�ho s�boru.
     *
     * @param inputFileName N�zov vstupn�ho s�boru.
     * @param outputFileName N�zov v�stupn�ho s�boru.
     */
    void Compress(const char* inputFileName, const char* outputFileName);

private:
    /**
     * @brief �trukt�ra pre porovn�vanie uzlov Huffmanovho stromu pod�a frekvencie.
     */
    struct comp {
        /**
         * @brief Porovn�va dva uzly Huffmanovho stromu pod�a frekvencie.
         *
         * @param a Prv� uzol.
         * @param b Druh� uzol.
         * @return True, ak frekvencia prv�ho uzla je v��ia ne� frekvencia druh�ho.
         */
        bool operator()(Node* a, Node* b) {
            return a->freq > b->freq;
        }
    };

    /**
     * @brief Vytv�ra Huffmanov strom na z�klade frekvenci� znakov.
     *
     * @param freq Frekvencie jednotliv�ch znakov.
     * @return Prioritn� fronta obsahuj�ca uzly Huffmanovho stromu.
     */
    priority_queue<Node*, vector<Node*>, comp> BuildTree(unordered_map<char, int>& freq);

    /**
     * @brief Koduje text pomocou Huffmanovho k�du.
     *
     * @param root Kore� Huffmanovho stromu.
     * @param str Aktu�lny re�azec k�du.
     * @param huffmanCode Mapa uchov�vaj�ca k�dy jednotliv�ch znakov.
     */
    void Encode(Node* root, string str, unordered_map<char, string>& huffmanCode);

    /**
     * @brief Uklad� zak�dovan� d�ta do v�stupn�ho s�boru.
     *
     * @param output V�stupn� s�borov� pr�d.
     */
    void DataToIntFile(ofstream& output);

    /**
     * @brief Koduje text zo vstupn�ho s�boru pomocou Huffmanovho k�du.
     *
     * @param text Vstupn� text.
     */
    void EncodeText(string text);

    /**
     * @brief Z�skava frekvencie jednotliv�ch znakov v texte.
     *
     * @param text Vstupn� text.
     */
    void GetFrequencies(string text);

    unordered_map<char, int> frequence; /**< Frekvencie jednotliv�ch znakov v texte. */
    string EncodedStr;                 /**< Zak�dovan� text. */
    char nula = '\0';                   /**< �peci�lny znak ozna�uj�ci za�iatok zak�dovan�ho re�azca. */
};

#endif // HUFFMAN_ENCODER_H
