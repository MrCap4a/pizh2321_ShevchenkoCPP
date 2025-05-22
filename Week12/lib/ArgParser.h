// lib/ArgParser.h
#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <cstddef>

namespace ArgumentParser {

    class ArgParser {
    public:
        explicit ArgParser(const std::string& description);

        // Основной разбор
        bool Parse(const std::vector<std::string>& args);
        // Удобная перегрузка для main(int, char**)
        bool Parse(int argc, char** argv);

        // Help-флаг
        bool Help() const;
        std::string HelpDescription() const;

        // Регистрация аргументов
        ArgParser& AddStringArgument(const std::string& name);
        ArgParser& AddStringArgument(const std::string& name, const std::string& help);
        ArgParser& AddStringArgument(char shortName, const std::string& name);
        ArgParser& AddStringArgument(char shortName, const std::string& name, const std::string& help);

        ArgParser& AddIntArgument(const std::string& name);
        ArgParser& AddIntArgument(const std::string& name, const std::string& help);
        ArgParser& AddIntArgument(char shortName, const std::string& name);
        ArgParser& AddIntArgument(char shortName, const std::string& name, const std::string& help);

        ArgParser& AddFlag(char shortName, const std::string& name);
        ArgParser& AddFlag(char shortName, const std::string& name, const std::string& help);

        ArgParser& AddHelp(char shortName, const std::string& name, const std::string& helpText);

        // Модификаторы
        ArgParser& Default(const char* value);               // <-- новая перегрузка
        ArgParser& Default(const std::string& value);
        ArgParser& Default(bool value);
        ArgParser& MultiValue();
        ArgParser& MultiValue(std::size_t minCount);
        ArgParser& Positional();

        // Привязка к переменным
        ArgParser& StoreValue(std::string& out);
        ArgParser& StoreValue(int& out);
        ArgParser& StoreValue(bool& out);
        ArgParser& StoreValues(std::vector<std::string>& out);
        ArgParser& StoreValues(std::vector<int>& out);

        // Геттеры после Parse
        std::string GetStringValue(const std::string& name) const;
        int         GetIntValue(const std::string& name) const;
        int         GetIntValue(const std::string& name, std::size_t idx) const;
        bool        GetFlag(const std::string& name) const;

    private:
        enum Kind { KString, KInt, KFlag, KHelp };

        struct Spec {
            std::string name;
            char        shortName = 0;
            Kind        kind;
            bool        multi = false;
            std::size_t minCount = 0;
            bool        positional = false;
            bool        hasDefault = false;
            std::string defaultValue;
            bool        defaultFlag = false;
            std::string helpText;

            std::string* storeString = nullptr;
            int* storeInt = nullptr;
            bool* storeFlag = nullptr;
            std::vector<std::string>* storeStrings = nullptr;
            std::vector<int>* storeInts = nullptr;
        };

        std::vector<Spec>                    specs_;
        std::unordered_map<std::string, int>  nameIndex_;
        std::map<char, std::string>           shortToName_;
        std::string                          description_;
        bool                                 helpRequested_ = false;
        int                                  lastSpec_ = -1;

        // Внутренние данные при разборе
        std::map<std::string, std::vector<std::string>> values_;
        std::map<std::string, bool>                    flags_;
        std::vector<std::string>                      positional_;
    };

} // namespace ArgumentParser
