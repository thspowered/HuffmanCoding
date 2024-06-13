#include "HuffmanEncoder.h"


void HuffmanEncoder::GetFrequencies(string text) {
    for (char ch : text) {
        frequence[ch]++;
    }
}


priority_queue<Node*, vector<Node*>, HuffmanEncoder::comp> HuffmanEncoder::BuildTree(unordered_map<char, int>& freq) {
    // vytvorenie primarnej fronty, zoradujem ju tak ze node s najmensou frekvenciu je na  vrcholu vzdy
    priority_queue<Node*, vector<Node*>, comp> pq;

    
    for (auto p : freq) {
        Node* n = new Node;
        n->ch = p.first;     
        n->freq = p.second; 
        n->left = nullptr;
        n->right = nullptr;
        pq.push(n);
    }

    
    while (pq.size() > 1) {
        Node* left = pq.top();  
        pq.pop();
        Node* right = pq.top();  
        pq.pop();

        
        Node* parent = new Node;
        parent->ch = '\0';  
        parent->freq = left->freq + right->freq;  
        parent->left = left;  
        parent->right = right;  
        pq.push(parent);  
    }

    
    return pq;
}

void HuffmanEncoder::EncodeText(string text) {
    priority_queue<Node*, vector<Node*>, comp> pq = BuildTree(frequence);
    Node* root = pq.top();
    unordered_map<char, string> huffmanCode;
    Encode(root, "", huffmanCode);

    // prebehnem cely text a zakodujem ho do EncodeStr
    for (char ch : text) {
        EncodedStr += huffmanCode[ch];
    }
}

void HuffmanEncoder::Encode(Node* root, string str, unordered_map<char, string>& huffmanCode) {
    if (root == nullptr) {
        return;
    }

    // ak dosiahnmem koniec pridam mu ten kod (str)
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    // rekurzivne to volam na cely strom
    Encode(root->left, str + "0", huffmanCode);
    Encode(root->right, str + "1", huffmanCode);
}

void HuffmanEncoder::DataToIntFile(ofstream& output) {
    //zapis frekvencii
    for (auto p : frequence) {
        output.write((char*)&p.first, sizeof(p.first));
        output.write((char*)&p.second, sizeof(p.second));
    }
    output.write((char*)&nula, sizeof(nula));

    //zapis zakodovaneho textu
    unsigned int number = 0;
    unsigned int mask = 0;
    list<unsigned int> bits;

    // Pøevod zakódovaného textu na èísla
    for (unsigned int i = 0; i < EncodedStr.size(); i++) {
        number <<= 1;
        mask = (EncodedStr[i] == '1' ? 1 : 0);
        number = number | mask;

        // Pokud jsme dosáhli 32 bitù, pøidáme je do seznamu
        if ((i > 0 && (i + 1) % 32 == 0)) {
            bits.push_back(number);
            number = 0;
        }
        // Pokud jsme na posledním znaku, doplníme nulami na konci
        else if ((i == EncodedStr.size() - 1)) {
            int pocet = (32 - (i % 32)) - 1;
            number <<= pocet;
            bits.push_back(number);
        }
    }


    // Zápis velikosti zakódovaného textu do souboru
    unsigned int size = EncodedStr.size();
    output.write((char*)&size, sizeof(size));

    // Zápis èísel do souboru
    while (!bits.empty()) {
        output.write((char*)&bits.front(), sizeof(bits.front()));
        bits.pop_front();
    }
}


// Metoda pro kompresi vstupního souboru a zápis do výstupního souboru
void HuffmanEncoder::Compress(const char* inputFileName, const char* outputFileName) {
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName, ios::binary | ios::out);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cout << "Nelze otevrit!";
        return;
    }

    // Naèítanie textu zo vstupného súboru
    string text((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

    // Získanie frekvencií jednotlivých znakov v texte
    GetFrequencies(text);

    // Zakódovanie textu pomocou Huffmanovho kódu
    EncodeText(text);

    // Zápis zakódovaného textu do výstupného súboru
    DataToIntFile(outputFile);

    // Výpis informácií o kompresii
    float fileSize = text.size();
    float fileSizeOutput = outputFile.tellp();

    cout << "Velkost vstupneho suboru: " << fileSize << " bytov" << endl;
    cout << "Velkost vystupneho suboru: " << fileSizeOutput << " bytov" << endl;

    float kompresnyPomer = (fileSizeOutput / fileSize) * 100;
    cout << "Kompresni pomer: " << kompresnyPomer << "%" << endl;

    // Uzatvorenie súborov
    inputFile.close();
    outputFile.close();
}

