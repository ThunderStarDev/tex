// Tex v.11.25 - Command line hex converter
// Compile: g++ -std=c++17 -O2 tex.cpp -o tex

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <limits>
#include <vector>

// Convert a plain text string to a space‑separated hex string
std::string textToHex(const std::string& text) {
    std::ostringstream oss;
    for (size_t i = 0; i < text.size(); ++i) {
        oss << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
            << static_cast<int>(static_cast<unsigned char>(text[i]));
        if (i + 1 != text.size()) oss << ' ';
    }
    return oss.str();
}

// Convert a space‑separated hex string back to plain text
std::string hexToText(const std::string& hex) {
    std::istringstream iss(hex);
    std::ostringstream oss;
    std::string token;
    while (iss >> token) {
        // Validate token length (1 or 2 hex digits)
        if (token.size() > 2) throw std::runtime_error("Invalid hex token: " + token);
        // Convert hex token to integer
        unsigned int value;
        std::istringstream conv(token);
        conv >> std::hex >> value;
        if (conv.fail()) throw std::runtime_error("Invalid hex token: " + token);
        oss << static_cast<char>(value);
    }
    return oss.str();
}

// Show help information
void showHelp() {
    std::cout << "ASCII ↔ HEX Converter\n";
    std::cout << "Usage:\n";
    std::cout << "  tex -tx <text>        Convert text to hex\n";
    std::cout << "  tex -xt <hex>         Convert hex to text\n";
    std::cout << "  tex -h, --help        Show this help message\n";
    std::cout << "  tex                   Interactive mode\n";
    std::cout << "\nExamples:\n";
    std::cout << "  tex -tx \"Hello\"\n";
    std::cout << "  tex -xt \"48 65 6C 6C 6F\"\n";
}

// Simple menu loop (original interactive mode)
void interactiveMode() {
    std::cout << "ASCII ↔ HEX Converter\n";
    std::cout << "1) Text → HEX\n";
    std::cout << "2) HEX → Text\n";
    std::cout << "Choose (1 or 2): ";

    int choice;
    if (!(std::cin >> choice)) return;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard newline

    if (choice == 1) {
        std::cout << "Enter text: ";
        std::string txt;
        std::getline(std::cin, txt);
        std::cout << "HEX: " << textToHex(txt) << '\n';
    } else if (choice == 2) {
        std::cout << "Enter HEX (space‑separated, e.g. 48 65 6C 6C 6F): ";
        std::string hexLine;
        std::getline(std::cin, hexLine);
        try {
            std::cout << "Text: " << hexToText(hexLine) << '\n';
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    } else {
        std::cerr << "Invalid choice.\n";
    }
}

int main(int argc, char* argv[]) {
    // If no arguments provided, run in interactive mode
    if (argc == 1) {
        interactiveMode();
        return 0;
    }

    // Parse command line arguments
    std::vector<std::string> args(argv + 1, argv + argc);
    
    if (args[0] == "-h" || args[0] == "--help") {
        showHelp();
        return 0;
    }
    else if (args[0] == "-tx") {
        if (args.size() < 2) {
            std::cerr << "Error: Missing text argument for -tx option\n";
            std::cerr << "Usage: tex -tx \"your text here\"\n";
            return 1;
        }
        
        // Combine all remaining arguments as the text to convert
        std::string text;
        for (size_t i = 1; i < args.size(); ++i) {
            if (i > 1) text += " ";
            text += args[i];
        }
        
        std::cout << textToHex(text) << std::endl;
        return 0;
    }
    else if (args[0] == "-xt") {
        if (args.size() < 2) {
            std::cerr << "Error: Missing hex argument for -xt option\n";
            std::cerr << "Usage: tex -xt \"48 65 6C 6C 6F\"\n";
            return 1;
        }
        
        // Combine all remaining arguments as the hex to convert
        std::string hex;
        for (size_t i = 1; i < args.size(); ++i) {
            if (i > 1) hex += " ";
            hex += args[i];
        }
        
        try {
            std::cout << hexToText(hex) << std::endl;
            return 0;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
            return 1;
        }
    }
    else {
        std::cerr << "Error: Unknown option '" << args[0] << "'\n";
        std::cerr << "Use 'tex -h' for help.\n";
        return 1;
    }
}
