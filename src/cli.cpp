#include <iostream>
#include <algorithm>
#include "../include/cli.h"
#include "../include/controller.h"

CLI::CLI(Controller *controller_param) {
    controller = controller_param;
}

void CLI::PrintMessage(std::wstring message) {
    std::wcout << message << "\n";
}

std::wstring CLI::ReadMessage() {
    std::getline(std::wcin, input_message, (wchar_t) '\n');
    std::wcin.get();
    return input_message;
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
        message = ReadMessage();
        if (message.length() > 1) {
            PrintMessage(L"Вы ввели некорректное значение");
            continue;
        }

        switch ((int) (message[0] - '0')) {
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

void CLI::Encode() {
    bool encode_is_not_ended = true;
    std::wstring message;
    while (encode_is_not_ended) {
        PrintMessage(L"Выберите один из пунктов ниже:");
        PrintMessage(L"1. Код Хэмминга");
        PrintMessage(L"2. Циклический код");
        PrintMessage(L"0. Назад");
        message = ReadMessage();
        if (message.length() > 1) {
            PrintMessage(L"Вы ввели некорректное значение");
            continue;
        }
        int command = (int)(message[0] - '0');
        if (command < 0 || command > 2){
            PrintMessage(L"Вы ввели некорректное значение");
            continue;
        }
        if (command == 0)
            return;
        bool is_correct_code = false;
        while (!is_correct_code) {
            PrintMessage(L"Введите сообщение для кодирования (последовательность из 0 и 1 без пробелов)");
            message = ReadMessage();
            is_correct_code = true;
            for (int i = 0; i < message.length(); ++i) {
                if (message[i] != '1' && message[i] != '0')
                    is_correct_code = false;
            }
            if (!is_correct_code)
                PrintMessage(L"Вы ввели некорректное значение");
        }
        TypeOfCode toc;
        switch (command) {
            case 1:
                toc = kHamming;
                break;
            default:
                toc = kCycleCode;
                break;
        }
        std::reverse(message.begin(), message.end());
        Code code = Code(message, toc);
        controller->EncodeMessage(code);

        PrintMessage(L"В закодированном виде:");

        std::wstring result = code.GetCodeWString();
        std::reverse(result.begin(), result.end());

        PrintMessage(result);

        encode_is_not_ended = false;
    }
}

void CLI::Decode() {
    bool decode_is_not_ended = true;
    std::wstring message;
    while (decode_is_not_ended) {
        PrintMessage(L"Выберите один из пунктов ниже:");
        PrintMessage(L"1. Код Хэмминга");
        PrintMessage(L"2. Циклический код");
        PrintMessage(L"0. Назад");
        message = ReadMessage();
        if (message.length() > 1) {
            PrintMessage(L"Вы ввели некорректное значение");
            continue;
        }
        int command = (int)(message[0] - '0');
        if (command < 0 || command > 2){
            PrintMessage(L"Вы ввели некорректное значение");
            continue;
        }
        if (command == 0)
            return;
        bool is_correct_code = false;
        while (!is_correct_code) {
            PrintMessage(L"Введите сообщение для декодирования (последовательность из 0 и 1 без пробелов)");
            message = ReadMessage();
            is_correct_code = true;
            for (int i = 0; i < message.length(); ++i) {
                if (message[i] != '1' && message[i] != '0')
                    is_correct_code = false;
            }
            if (!is_correct_code)
                PrintMessage(L"Вы ввели некорректное значение");
        }
        TypeOfCode toc;
        switch (command) {
            case 1:
                toc = kHamming;
                break;
            default:
                toc = kCycleCode;
                break;
        }
        std::reverse(message.begin(), message.end());
        Code code = Code(message, toc);
        bool error_have_been_found = controller->DecodeMessage(code);
        if (error_have_been_found)
            PrintMessage(L"В коде была обнаружена ошибка");
        PrintMessage(L"В раскодированном виде:");

        std::wstring result = code.GetCodeWString();
        std::reverse(result.begin(), result.end());

        PrintMessage(result);

        decode_is_not_ended = false;
    }
}

void CLI::GetStatistic() {
    std::wstring message;
    PrintMessage(L"Введите сообщение для статистики (последовательность из 0 и 1 без пробелов)");
    message = ReadMessage();
    int command = (int)(message[0] - '0');
    TypeOfCode toc = kHamming;
    std::reverse(message.begin(), message.end());
    Code code = Code(message, toc);
    std::vector<Stats> stats = controller->GetStats(code);
    controller->EncodeMessage(code);
    for (int i = 0; i < code.GetLength(); ++i){
        std::wcout << "i = " << i + 1 << " " << stats[i].SummaryCountErrors << " " << stats[i].FoundedErrorsCount << " " <<stats[i].FixesCount << " " << stats[i].FindingRate << " " << stats[i].FixingRate << "\n";
    }
}