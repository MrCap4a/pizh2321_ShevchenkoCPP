#include "ArgParser.h"
#include <algorithm>
#include <cstdlib>

using namespace ArgumentParser;

ArgParser::ArgParser(const std::string& description)
    : description_(description)
{
}

// Перегрузка для main()
bool ArgParser::Parse(int argc, char** argv) {
    std::vector<std::string> v;
    v.reserve(argc);
    for (int i = 0; i < argc; ++i)
        v.emplace_back(argv[i]);
    return Parse(v);
}

bool ArgParser::Parse(const std::vector<std::string>& args) {
    // Сброс состояния
    helpRequested_ = false;
    positional_.clear();
    values_.clear();
    flags_.clear();

    // Инициализируем флаги их default-значениями
    for (auto& sp : specs_) {
        if (sp.kind == KFlag) {
            flags_[sp.name] = sp.hasDefault ? sp.defaultFlag : false;
        }
    }

    // Разбор аргументов
    for (size_t i = 1; i < args.size(); ++i) {
        const auto& a = args[i];

        // --long или --long=val
        if (a.rfind("--", 0) == 0) {
            std::string t = a.substr(2);
            auto pos = t.find('=');
            std::string nm = t.substr(0, pos);
            std::string val = (pos == std::string::npos ? "" : t.substr(pos + 1));

            if (nameIndex_.count(nm)) {
                Spec& sp = specs_[nameIndex_[nm]];
                if (sp.kind == KHelp) {
                    helpRequested_ = true;
                }
                else if (sp.kind == KFlag) {
                    flags_[nm] = true;
                }
                else {
                    values_[nm].push_back(val);
                }
                continue;
            }
        }
        // -x=val или склеенные флаги -abc
        else if (a.rfind("-", 0) == 0 && a.size() > 1) {
            auto posEq = a.find('=');
            if (posEq != std::string::npos) {
                // форма -x=val
                char sn = a[1];
                if (shortToName_.count(sn)) {
                    std::string nm = shortToName_[sn];
                    Spec& sp = specs_[nameIndex_[nm]];
                    std::string val = a.substr(posEq + 1);
                    if (sp.kind == KHelp) {
                        helpRequested_ = true;
                    }
                    else if (sp.kind == KFlag) {
                        flags_[nm] = true;
                    }
                    else {
                        values_[nm].push_back(val);
                    }
                }
            }
            else {
                // форма -abc → эквивалент -a -b -c для флагов/help
                for (size_t j = 1; j < a.size(); ++j) {
                    char sn2 = a[j];
                    if (!shortToName_.count(sn2)) continue;
                    std::string nm2 = shortToName_[sn2];
                    Spec& sp2 = specs_[nameIndex_[nm2]];
                    if (sp2.kind == KHelp) {
                        helpRequested_ = true;
                    }
                    else if (sp2.kind == KFlag) {
                        flags_[nm2] = true;
                    }
                }
            }
            continue;
        }

        // Позиционный аргумент
        positional_.push_back(a);
    }

    // Если help — сразу выходим
    if (helpRequested_)
        return true;

    // Раздаем позиционные тем, у кого .Positional()
    for (auto& sp : specs_) {
        if (sp.positional) {
            values_[sp.name] = positional_;
        }
    }

    // Проверяем обязательность / minCount / default
    for (auto& sp : specs_) {
        if (sp.kind == KString || sp.kind == KInt) {
            auto& vec = values_[sp.name];
            if (sp.multi) {
                if (vec.size() < sp.minCount)
                    return false;
            }
            else {
                if (vec.empty()) {
                    if (sp.hasDefault) {
                        vec.push_back(sp.defaultValue);
                    }
                    else {
                        return false;
                    }
                }
            }
        }
    }

    // Кладём результаты в ваши переменные
    for (auto& sp : specs_) {
        auto& vec = values_[sp.name];

        if (sp.kind == KString) {
            if (!sp.multi) {
                if (sp.storeString)
                    *sp.storeString = vec[0];
            }
            else if (sp.storeStrings) {
                sp.storeStrings->clear();
                for (auto& s : vec)
                    sp.storeStrings->push_back(s);
            }
        }
        else if (sp.kind == KInt) {
            if (!sp.multi) {
                int v = vec.empty() ? 0 : std::stoi(vec[0]);
                if (sp.storeInt)
                    *sp.storeInt = v;
            }
            else if (sp.storeInts) {
                sp.storeInts->clear();
                for (auto& s : vec)
                    sp.storeInts->push_back(std::stoi(s));
            }
        }
        else if (sp.kind == KFlag) {
            if (sp.storeFlag)
                *sp.storeFlag = flags_[sp.name];
        }
    }

    return true;
}

bool ArgParser::Help() const {
    return helpRequested_;
}

std::string ArgParser::HelpDescription() const {
    return description_ + "\n";
}

// === Регистрация ===

ArgParser& ArgParser::AddStringArgument(const std::string& name) {
    Spec s; s.name = name; s.kind = KString;
    specs_.push_back(s);
    lastSpec_ = int(specs_.size()) - 1;
    nameIndex_[name] = lastSpec_;
    return *this;
}
ArgParser& ArgParser::AddStringArgument(const std::string& name, const std::string& help) {
    AddStringArgument(name);
    specs_[lastSpec_].helpText = help;
    return *this;
}
ArgParser& ArgParser::AddStringArgument(char sn, const std::string& name) {
    AddStringArgument(name);
    specs_[lastSpec_].shortName = sn;
    shortToName_[sn] = name;
    return *this;
}
ArgParser& ArgParser::AddStringArgument(char sn, const std::string& name, const std::string& help) {
    AddStringArgument(name, help);
    specs_[lastSpec_].shortName = sn;
    shortToName_[sn] = name;
    return *this;
}

ArgParser& ArgParser::AddIntArgument(const std::string& name) {
    Spec s; s.name = name; s.kind = KInt;
    specs_.push_back(s);
    lastSpec_ = int(specs_.size()) - 1;
    nameIndex_[name] = lastSpec_;
    return *this;
}
ArgParser& ArgParser::AddIntArgument(const std::string& name, const std::string& help) {
    AddIntArgument(name);
    specs_[lastSpec_].helpText = help;
    return *this;
}
ArgParser& ArgParser::AddIntArgument(char sn, const std::string& name) {
    AddIntArgument(name);
    specs_[lastSpec_].shortName = sn;
    shortToName_[sn] = name;
    return *this;
}
ArgParser& ArgParser::AddIntArgument(char sn, const std::string& name, const std::string& help) {
    AddIntArgument(name, help);
    specs_[lastSpec_].shortName = sn;
    shortToName_[sn] = name;
    return *this;
}

ArgParser& ArgParser::AddFlag(char sn, const std::string& name) {
    Spec s; s.name = name; s.kind = KFlag;
    specs_.push_back(s);
    lastSpec_ = int(specs_.size()) - 1;
    nameIndex_[name] = lastSpec_;
    specs_[lastSpec_].shortName = sn;
    shortToName_[sn] = name;
    return *this;
}
ArgParser& ArgParser::AddFlag(char sn, const std::string& name, const std::string& help) {
    AddFlag(sn, name);
    specs_[lastSpec_].helpText = help;
    return *this;
}

ArgParser& ArgParser::AddHelp(char sn, const std::string& name, const std::string& help) {
    Spec s; s.name = name; s.kind = KHelp; s.shortName = sn; s.helpText = help;
    specs_.push_back(s);
    lastSpec_ = int(specs_.size()) - 1;
    nameIndex_[name] = lastSpec_;
    shortToName_[sn] = name;
    return *this;
}

// === Модификаторы ===

ArgParser& ArgParser::Default(const char* v) {
    return Default(std::string(v));
}
ArgParser& ArgParser::Default(const std::string& v) {
    if (lastSpec_ >= 0) {
        specs_[lastSpec_].hasDefault = true;
        specs_[lastSpec_].defaultValue = v;
    }
    return *this;
}
ArgParser& ArgParser::Default(bool v) {
    if (lastSpec_ >= 0 && specs_[lastSpec_].kind == KFlag) {
        specs_[lastSpec_].hasDefault = true;
        specs_[lastSpec_].defaultFlag = v;
    }
    return *this;
}
ArgParser& ArgParser::MultiValue() {
    if (lastSpec_ >= 0) {
        specs_[lastSpec_].multi = true;
    }
    return *this;
}
ArgParser& ArgParser::MultiValue(std::size_t n) {
    if (lastSpec_ >= 0) {
        specs_[lastSpec_].multi = true;
        specs_[lastSpec_].minCount = n;
    }
    return *this;
}
ArgParser& ArgParser::Positional() {
    if (lastSpec_ >= 0) {
        specs_[lastSpec_].positional = true;
    }
    return *this;
}

// === StoreValue / StoreValues ===

ArgParser& ArgParser::StoreValue(std::string& out) {
    if (lastSpec_ >= 0 && specs_[lastSpec_].kind == KString && !specs_[lastSpec_].multi)
        specs_[lastSpec_].storeString = &out;
    return *this;
}
ArgParser& ArgParser::StoreValue(int& out) {
    if (lastSpec_ >= 0 && specs_[lastSpec_].kind == KInt && !specs_[lastSpec_].multi)
        specs_[lastSpec_].storeInt = &out;
    return *this;
}
ArgParser& ArgParser::StoreValue(bool& out) {
    if (lastSpec_ >= 0 && specs_[lastSpec_].kind == KFlag)
        specs_[lastSpec_].storeFlag = &out;
    return *this;
}
ArgParser& ArgParser::StoreValues(std::vector<std::string>& out) {
    if (lastSpec_ >= 0 && specs_[lastSpec_].kind == KString && specs_[lastSpec_].multi)
        specs_[lastSpec_].storeStrings = &out;
    return *this;
}
ArgParser& ArgParser::StoreValues(std::vector<int>& out) {
    if (lastSpec_ >= 0 && specs_[lastSpec_].kind == KInt && specs_[lastSpec_].multi)
        specs_[lastSpec_].storeInts = &out;
    return *this;
}

// === Геттеры ===

std::string ArgParser::GetStringValue(const std::string& name) const {
    auto it = values_.find(name);
    if (it != values_.end() && !it->second.empty())
        return it->second[0];
    return "";
}
int ArgParser::GetIntValue(const std::string& name) const {
    auto it = values_.find(name);
    if (it != values_.end() && !it->second.empty())
        return std::stoi(it->second[0]);
    return 0;
}
int ArgParser::GetIntValue(const std::string& name, std::size_t idx) const {
    auto it = values_.find(name);
    if (it != values_.end() && idx < it->second.size())
        return std::stoi(it->second[idx]);
    return 0;
}
bool ArgParser::GetFlag(const std::string& name) const {
    auto it = flags_.find(name);
    if (it != flags_.end())
        return it->second;
    return false;
}
