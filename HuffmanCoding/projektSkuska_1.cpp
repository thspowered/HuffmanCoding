#include <iostream>
#include "HuffmanEncoder.h"
#include "HuffmanDecoder.h"

int main(int argc, char** argv) {
    if (argc != 4) {
        cerr << "Pouziti: " << argv[0] << " <akce (c/d)> <vstupni_soubor> <vystupni_soubor>" << endl;
        return 1;
    }

    string action = argv[1];
    const char* input_file = argv[2];
    const char* output_file = argv[3];

    if (action == "c") {
        HuffmanEncoder encoder;
        encoder.Compress(input_file, output_file);
    }
    else if (action == "d") {
        HuffmanDecoder decoder;
        decoder.decompress(input_file, output_file);
    }
    else {
        cerr << "Neplatna akcia. Pouzi 'c' pre kompresiu alebo 'd' pro dekompresiu." << endl;
        return 1;
    }

    return 0;
}
