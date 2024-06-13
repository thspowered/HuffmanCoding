#ifndef HUFFMAN_ENCODER_H
#define HUFFMAN_ENCODER_H

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

/**
 * @brief Štruktúra reprezentujúca uzol Huffmanovho stromu.
 */
struct Node {
    char ch;      /**< Znak v uzle. */
    int freq;     /**< Frekvencia znaku. */
    Node* left;   /**< Ukazovate¾ na ¾avého potomka. */
    Node* right;  /**< Ukazovate¾ na pravého potomka. */
};

/**
 * @brief Trieda HuffmanEncoder pre kompresiu textovıch súborov.
 */
class HuffmanEncoder {
public:
    /**
     * @brief Kompresuje vstupnı súbor pomocou Huffmanovho kódovania a ukladá do vıstupného súboru.
     *
     * @param inputFileName Názov vstupného súboru.
     * @param outputFileName Názov vıstupného súboru.
     */
    void Compress(const char* inputFileName, const char* outputFileName);

private:
    /**
     * @brief Štruktúra pre porovnávanie uzlov Huffmanovho stromu pod¾a frekvencie.
     */
    struct comp {
        /**
         * @brief Porovnáva dva uzly Huffmanovho stromu pod¾a frekvencie.
         *
         * @param a Prvı uzol.
         * @param b Druhı uzol.
         * @return True, ak frekvencia prvého uzla je väèšia ne frekvencia druhého.
         */
        bool operator()(Node* a, Node* b) {
            return a->freq > b->freq;
        }
    };

    /**
     * @brief Vytvára Huffmanov strom na základe frekvencií znakov.
     *
     * @param freq Frekvencie jednotlivıch znakov.
     * @return Prioritná fronta obsahujúca uzly Huffmanovho stromu.
     */
    priority_queue<Node*, vector<Node*>, comp> BuildTree(unordered_map<char, int>& freq);

    /**
     * @brief Koduje text pomocou Huffmanovho kódu.
     *
     * @param root Koreò Huffmanovho stromu.
     * @param str Aktuálny reazec kódu.
     * @param huffmanCode Mapa uchovávajúca kódy jednotlivıch znakov.
     */
    void Encode(Node* root, string str, unordered_map<char, string>& huffmanCode);

    /**
     * @brief Ukladá zakódované dáta do vıstupného súboru.
     *
     * @param output Vıstupnı súborovı prúd.
     */
    void DataToIntFile(ofstream& output);

    /**
     * @brief Koduje text zo vstupného súboru pomocou Huffmanovho kódu.
     *
     * @param text Vstupnı text.
     */
    void EncodeText(string text);

    /**
     * @brief Získava frekvencie jednotlivıch znakov v texte.
     *
     * @param text Vstupnı text.
     */
    void GetFrequencies(string text);

    unordered_map<char, int> frequence; /**< Frekvencie jednotlivıch znakov v texte. */
    string EncodedStr;                 /**< Zakódovanı text. */
    char nula = '\0';                   /**< Špeciálny znak oznaèujúci zaèiatok zakódovaného reazca. */
};

#endif // HUFFMAN_ENCODER_H
