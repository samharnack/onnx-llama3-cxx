#include <iostream>
#include <string>
#include <ort_genai.h>

const char* BLUE = "\033[34m";
const char* GREEN = "\033[32m";
const char* YELLOW = "\033[33m";
const char* RESET = "\033[0m";

void chat(const char* model_path) {
    OgaHandle handle;

    auto model = OgaModel::Create(model_path);
    auto tokenizer = OgaTokenizer::Create(*model);
    auto tokenizer_stream = OgaTokenizerStream::Create(*tokenizer);

    std::cout << BLUE << "Chat Interface (Type 'quit()' to exit)\n"
              << "----------------------------------------\n" << RESET << "\n";

    while (true) {
        std::string text;
        std::cout << GREEN << "User: " << RESET;
        std::getline(std::cin, text);

        if (text == "quit()") break;

        const std::string prompt = "<|user|>\n" + text + "<|end|>\n<|assistant|>";
        auto sequences = OgaSequences::Create();
        tokenizer->Encode(prompt.c_str(), *sequences);

        auto params = OgaGeneratorParams::Create(*model);
        params->SetSearchOption("max_length", 1024);
        params->SetInputSequences(*sequences);

        auto generator = OgaGenerator::Create(*model, *params);
        
        std::cout << YELLOW << "Assistant: " << RESET;
        
        while (!generator->IsDone()) {
            generator->ComputeLogits();
            generator->GenerateNextToken();
            
            const auto num_tokens = generator->GetSequenceCount(0);
            const auto new_token = generator->GetSequenceData(0)[num_tokens - 1];
            std::cout << tokenizer_stream->Decode(new_token) << std::flush;
        }

        std::cout << "\n\n" << std::endl;
    }
}
