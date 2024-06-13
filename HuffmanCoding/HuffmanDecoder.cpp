#include "HuffmanDecoder.h"

void HuffmanDecoder::decode(Node* currentNode, int& currentIndex, const string& binaryString, ofstream& outputStream) {
    if (currentNode == nullptr) {
        return;
    }

    if (!currentNode->left && !currentNode->right) {
        outputStream << currentNode->ch;
        return;
    }

    currentIndex++;

    if (binaryString[currentIndex] == '0') {
        decode(currentNode->left, currentIndex, binaryString, outputStream);
    }
    else {
        decode(currentNode->right, currentIndex, binaryString, outputStream);
    }
}


string HuffmanDecoder::decimalToBinaryString(unsigned int decimalValue) {
    int maxBits = (sizeof(unsigned int) * 8);
    string binaryString = "";
    int mask = 1;

    for (int i = 0; i < maxBits; i++) {
        binaryString = ((mask & decimalValue) >= 1 ? "1" : "0") + binaryString;
        mask <<= 1;
    }

    return binaryString;
}


void HuffmanDecoder::decodeString(Node* root, const string& binaryString, ofstream& outputStream) {
    if (root->left == nullptr && root->right == nullptr) {
        while (root->freq--) {
            outputStream << root->ch;
        }
    }
    else {
        int index = -1;

        while (index < static_cast<int>(binaryString.size()) - 2) {
            decode(root, index, binaryString, outputStream);
        }
    }
}

string HuffmanDecoder::bitsToString(const list<unsigned int>& listOfValues) {
    ostringstream oss;  // Vytvorenie objektu std::ostringstream na konvertovanie hodnÙt na text

    for (const auto& value : listOfValues) {
        oss << decimalToBinaryString(value);  // Konvertovanie hodnoty na bin·rny reùazec a pridanie do std::ostringstream
    }

    
    return oss.str();  // Prevod obsahu std::ostringstream na std::string a vr·tenie v˝slednÈho reùazca
}


unsigned int HuffmanDecoder::loadToList(ifstream& input) {
    char ch = 'a';                  // Inicializ·cia premenn˝ch
    int i = 0;
    unsigned int tmp = 0;
    bool startLoaded = false;
    unsigned int size = 0;

    while (input) {                 // Cyklus naËÌtavania zo vstupnÈho s˙boru, pokraËuje, pokiaæ je moûnÈ ËÌtaù
        if (startLoaded) {
            if (input.read(reinterpret_cast<char*>(&tmp), sizeof(tmp))) {  // NaËÌtanie hodnoty tmp zo s˙boru
                this->bits.push_back(tmp);  // Pridanie hodnoty tmp do zoznamu bits
            }
        }
        else {
            if (!input.read(reinterpret_cast<char*>(&ch), sizeof(ch))) {  // NaËÌtanie hodnoty ch zo s˙boru, ak sa ne˙speöne naËÌta, ukonËÌ cyklus
                break;
            }

            if (ch == nula) {
                if (!input.read(reinterpret_cast<char*>(&size), sizeof(size))) {  // NaËÌtanie hodnoty size zo s˙boru, ak sa ne˙speöne naËÌta, ukonËÌ cyklus
                    break;
                }
                startLoaded = true;
            }

            if (ch != nula) {
                if (!input.read(reinterpret_cast<char*>(&i), sizeof(i))) {  // NaËÌtanie hodnoty i zo s˙boru, ak sa ne˙speöne naËÌta, ukonËÌ cyklus
                    break;
                }
                this->frequence[ch] = i;  // Pridanie hodnoty i do asociatÌvneho poæa frequence
            }
        }
    }
    return size;  // Vr·tenie hodnoty size, ktor· reprezentuje veækosù bin·rneho reùazca
}



priority_queue<Node*, vector<Node*>, HuffmanDecoder::comp> HuffmanDecoder::BuildTree(unordered_map<char, int>& freq) {
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

void HuffmanDecoder::decompress(const char* inputFileName, const char* outputFileName) {
    ifstream inputFile(inputFileName, ios::binary | ios::in);

    unsigned int decodedSize = loadToList(inputFile);

    string binaryString = bitsToString(bits);

    ofstream outputFile(outputFileName, ios::out);

    string decodedData = binaryString.substr(0, decodedSize);

    priority_queue<Node*, vector<Node*>, comp> priorityQueue = BuildTree(frequence);

    Node* huffmanTreeRoot = priorityQueue.top();

    decodeString(huffmanTreeRoot, decodedData, outputFile);

    outputFile.close();
}
