#include "../include/cli.h"
#include "../include/controller.h"
#include "../include/utils.h"
#include <iostream>
#include <algorithm>

CLI::CLI(Controller *controller_param) {
    controller = controller_param;
}

void CLI::PrintMessage(std::wstring message) {
    std::wcout << message << "\n";
}

std::wstring CLI::ReadMessage() {
    std::wstring input_message;
    std::getline(std::wcin, input_message, (wchar_t) '\n');
    return input_message;
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

bool CLI::IsCodeCorrect(std::wstring &message) {
    bool code_is_correct = true;
    for (wchar_t i: message) {
        if ((int) (i - '0') != 0 && (int) (i - '0') != 1)
            code_is_correct = false;
    }
    return code_is_correct;
}

Code CLI::GetCodeFromString(std::wstring &message, TypeOfCode &code_type) {
    std::reverse(message.begin(), message.end());
    return {message, code_type};
}

std::wstring CLI::ReadCodeString() {
    std::wstring message;
    bool is_correct_code = false;
    while (!is_correct_code) {
        is_correct_code = true;
        PrintMessage(L"Введите сообщение (последовательность из 0 и 1 без пробелов)");
        message = ReadMessage();
        if (!IsCodeCorrect(message)) {
            PrintMessage(L"Вы ввели некорректное значение");
            is_correct_code = false;
        }
    }
    return message;
}

Code CLI::ReadCode(TypeOfCode &code_type) {
    std::wstring code = ReadCodeString();
    return GetCodeFromString(code, code_type);
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
            code_type = TypeOfCode::kCycleCode;

        Code code_to_encode = ReadCode(code_type);
        controller->EncodeMessage(code_to_encode);

        PrintMessage(L"В закодированном виде:");
        std::wstring result = code_to_encode.GetCodeWString();
        PrintMessage(result);

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
            code_type = TypeOfCode::kCycleCode;

        Code code_to_decode = ReadCode(code_type);
        int error_have_been_found = controller->DecodeMessage(code_to_decode);
        if (error_have_been_found) {
            PrintMessage(L"В коде была обнаружена ошибка");
            PrintMessage(L"Ошибка в " + std::to_wstring(error_have_been_found) + L" бите справа");
        }

        PrintMessage(L"В раскодированном виде:");
        std::wstring result = code_to_decode.GetCodeWString();
        PrintMessage(result);

        decode_is_not_ended = false;
    }
}
