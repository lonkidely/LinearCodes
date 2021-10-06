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
    std::wcin.get();
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
        PrintMessage(L"3. Собрать статистику декодирования сообщения");
        PrintMessage(L"0. Выход");
        int choice;
        if (!GetChoiceResult(0, 3, choice)) {
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
            case 3:
                GetStatistic();
                break;
            case 0:
                work_is_not_ended = false;
                break;
            default:
                PrintMessage(L"Вы ввели некорректное сообщение");
                break;
        }
    }
}

bool CLI::IsCodeCorrect(std::wstring &message) {
    bool code_is_correct = true;
    for (wchar_t i : message) {
        if ((int) (i - '0') != 0 && (int) (i - '0') != 1)
            code_is_correct = false;
    }
    return code_is_correct;
}

Code CLI::GetCodeFromString(std::wstring &message, TypeOfCode &code_type) {
    std::reverse(message.begin(), message.end());
    return Code(message, code_type);
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
        switch (command) {
            case 1:
                code_type = kHamming;
                break;
            default:
                code_type = kCycleCode;
                break;
        }

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
        switch (command) {
            case 1:
                code_type = kHamming;
                break;
            default:
                code_type = kCycleCode;
                break;
        }

        Code code_to_decode = ReadCode(code_type);
        bool error_have_been_found = controller->DecodeMessage(code_to_decode);
        if (error_have_been_found)
            PrintMessage(L"В коде была обнаружена ошибка");

        PrintMessage(L"В раскодированном виде:");
        std::wstring result = code_to_decode.GetCodeWString();
        PrintMessage(result);

        decode_is_not_ended = false;
    }
}

void CLI::GetStatistic() {
    bool stats_is_not_ended = true;
    while (stats_is_not_ended) {
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
        switch (command) {
            case 1:
                code_type = kHamming;
                break;
            default:
                code_type = kCycleCode;
                break;
        }

        std::wstring code_string = ReadCodeString();
        if (code_string.length() > kMaxLengthCodeForStats) {
            PrintMessage(L"Вы ввели слишком длинную последовательность");
            continue;
        }
        Code code_for_stats = GetCodeFromString(code_string, code_type);

        std::vector<Stats> stats = controller->GetStats(code_for_stats);
        controller->EncodeMessage(code_for_stats);
        for (int i = 0; i < code_for_stats.GetLength(); ++i) {
            std::wcout << "i = " << i + 1 << " " << stats[i].SummaryCountErrors << " "
                       << stats[i].FoundedErrorsCount << " "
                       << stats[i].FixesCount << " " << stats[i].FindingRate << " " << stats[i].FixingRate << "\n";
        }

        stats_is_not_ended = false;
    }
}