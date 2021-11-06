#include "cli.h"
#include "../controller.h"
#include <iostream>

CLI::CLI(std::shared_ptr<Controller> controller_param) {
    controller = std::move(controller_param);
}

void CLI::PrintMessage(const std::wstring &message) {
    std::wcout << message << "\n";
}

std::wstring CLI::ReadMessage() {
    std::wstring input_message;
    std::getline(std::wcin, input_message, (wchar_t) '\n');
    return input_message;
}

bool CLI::IsCorrectNumber(const std::wstring &str) {
    bool is_correct = str.length() > 0;
    for (wchar_t i: str) {
        if (i < static_cast<wchar_t>('0') || i > static_cast<wchar_t>('9'))
            is_correct = false;
    }
    return is_correct;
}

bool CLI::GetChoiceResult(int lower_bound, int upper_bound, int &choice) {
    std::wstring message;
    message = ReadMessage();
    if (!IsCorrectNumber(message))
        return false;
    choice = std::stoi(message);
    return (choice >= lower_bound) && (choice <= upper_bound);
}

void CLI::Start() {
    bool work_is_not_ended = true;
    PrintMessage(L"Начало работы");
    std::wstring message;
    while (work_is_not_ended) {
        PrintMessage(L"Для продолжения выберите один из пунктов ниже:");
        PrintMessage(L"1. Закодировать сообщение");
        PrintMessage(L"2. Раскодировать сообщение");
        PrintMessage(L"0. Выход");
        int choice;
        if (!GetChoiceResult(0, 2, choice)) {
            PrintMessage(L"Вы ввели некорректное значение");
            continue;
        }

        switch (choice) {
            case 1:
                Encode();
                break;
            case 2:
                Decode();
                break;
            case 0:
                work_is_not_ended = false;
                break;
            default:
                PrintMessage(L"Вы ввели некорректное значение");
                break;
        }
    }
}

std::wstring CLI::ReadCodeString(TypeOfCode code_type) {
    std::wstring message;
    bool is_correct_code = false;
    while (!is_correct_code) {
        is_correct_code = true;
        PrintMessage(L"Введите сообщение (последовательность из 0 и 1 без пробелов)");
        message = ReadMessage();
        if (!controller->IsCodeCorrect(message, code_type)) {
            PrintMessage(L"Вы ввели некорректное значение");
            is_correct_code = false;
        }
    }
    return message;
}

void CLI::Encode() {
    bool encode_is_not_ended = true;
    while (encode_is_not_ended) {
        PrintMessage(L"Выберите один из пунктов ниже:");
        PrintMessage(L"1. Код Хэмминга");
        PrintMessage(L"2. Циклический код");
        PrintMessage(L"0. Назад");

        int command;
        if (!GetChoiceResult(0, 2, command)) {
            PrintMessage(L"Вы ввели некорректное значение");
            continue;
        }
        if (command == 0)
            return;

        TypeOfCode code_type;
        if (command == 1)
            code_type = TypeOfCode::kHamming;
        else
            code_type = TypeOfCode::kCyclicCode;

        std::wstring code_to_encode = ReadCodeString(code_type);

        std::wstring result_of_encoding = controller->EncodeMessage(code_to_encode, code_type);
        PrintMessage(L"В закодированном виде:");
        PrintMessage(result_of_encoding);

        encode_is_not_ended = false;
    }
}

void CLI::Decode() {
    bool decode_is_not_ended = true;
    while (decode_is_not_ended) {
        PrintMessage(L"Выберите один из пунктов ниже:");
        PrintMessage(L"1. Код Хэмминга");
        PrintMessage(L"2. Циклический код");
        PrintMessage(L"0. Назад");

        int command;
        if (!GetChoiceResult(0, 2, command)) {
            PrintMessage(L"Вы ввели некорректное значение");
            continue;
        }

        if (command == 0)
            return;

        TypeOfCode code_type;
        if (command == 1)
            code_type = TypeOfCode::kHamming;
        else
            code_type = TypeOfCode::kCyclicCode;

        std::wstring code_to_decode = ReadCodeString(code_type);

        std::pair<std::wstring, bool> result_of_decoding = controller->DecodeMessage(code_to_decode, code_type);
        if (result_of_decoding.second) {
            PrintMessage(L"В коде была обнаружена ошибка");
        }

        PrintMessage(L"В раскодированном виде:");
        PrintMessage(result_of_decoding.first);

        decode_is_not_ended = false;
    }
}
