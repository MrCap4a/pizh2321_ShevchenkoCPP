#include "parser.h"
#include <regex>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <variant>
#include <algorithm>

namespace omfl {

    class NodeImpl {
    public:
        using Value = std::variant<int, float, std::string, bool, std::vector<Node>>;
        std::unordered_map<std::string, Node> children;
        Value value;
        bool is_array = false;
    };

    Node::Node() : impl(std::make_shared<NodeImpl>()) {}
    Node::Node(const std::string& val) : impl(std::make_shared<NodeImpl>()) { impl->value = val; }
    Node::Node(int val) : impl(std::make_shared<NodeImpl>()) { impl->value = val; }
    Node::Node(float val) : impl(std::make_shared<NodeImpl>()) { impl->value = val; }
    Node::Node(bool val) : impl(std::make_shared<NodeImpl>()) { impl->value = val; }
    Node::Node(const std::vector<Node>& array) : impl(std::make_shared<NodeImpl>()) {
        impl->value = array;
        impl->is_array = true;
    }

    bool Node::IsValid() const { return impl != nullptr; }
    void Node::SetInvalid() { impl = nullptr; }
    std::shared_ptr<NodeImpl>& Node::access_impl() { return impl; }

    bool Node::IsInt() const { return impl && std::holds_alternative<int>(impl->value); }
    int Node::AsInt() const { return std::get<int>(impl->value); }
    int Node::AsIntOrDefault(int def) const { return (IsValid() && IsInt()) ? AsInt() : def; }

    bool Node::IsFloat() const { return impl && std::holds_alternative<float>(impl->value); }
    float Node::AsFloat() const { return std::get<float>(impl->value); }
    float Node::AsFloatOrDefault(float def) const { return (IsValid() && IsFloat()) ? AsFloat() : def; }

    bool Node::IsString() const { return impl && std::holds_alternative<std::string>(impl->value); }
    std::string Node::AsString() const { return std::get<std::string>(impl->value); }
    std::string Node::AsStringOrDefault(const std::string& def) const {
        return (IsValid() && IsString()) ? AsString() : def;
    }

    bool Node::IsBool() const { return impl && std::holds_alternative<bool>(impl->value); }
    bool Node::AsBool() const { return std::get<bool>(impl->value); }
    bool Node::AsBoolOrDefault(bool def) const {
        return (IsValid() && IsBool()) ? AsBool() : def;
    }

    bool Node::IsArray() const { return impl && impl->is_array; }

    Node Node::operator[](size_t index) const {
        if (!IsArray()) {
            Node invalid;
            invalid.SetInvalid();
            return invalid;
        }
        const auto& vec = std::get<std::vector<Node>>(impl->value);
        if (index >= vec.size()) {
            Node invalid;
            invalid.SetInvalid();
            return invalid;
        }
        return vec[index];
    }

    Node Node::Get(const std::string& key) const {
        if (!impl) return Node();
        size_t dot = key.find('.');
        if (dot == std::string::npos) {
            if (!impl->children.count(key)) return Node();
            return impl->children.at(key);
        }

        std::string first = key.substr(0, dot);
        std::string rest = key.substr(dot + 1);
        if (!impl->children.count(first)) return Node();
        return impl->children.at(first).Get(rest);
    }

    bool Root::valid() const { return is_valid_; }
    void Root::set_valid(bool is_valid) { is_valid_ = is_valid; }

    static std::string trim(const std::string& s) {
        size_t start = s.find_first_not_of(" \t\r");
        size_t end = s.find_last_not_of(" \t\r");
        return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
    }

    Node parse_value(const std::string& val, bool& valid) {
        std::regex int_re(R"([+-]?\d+)");
        std::regex float_re(R"([+-]?\d+\.\d+)");
        std::regex bool_re(R"(true|false)");
        std::regex str_re(R"(".*")");
        std::regex arr_re(R"(\[(.*)\])");

        std::string trimmed = trim(val);

        if (std::regex_match(trimmed, str_re)) {
            size_t count_quotes = std::count(trimmed.begin(), trimmed.end(), '\"');
            if (count_quotes != 2 || trimmed.front() != '\"' || trimmed.back() != '\"') {
                valid = false;
                return Node();
            }
            return Node(trimmed.substr(1, trimmed.size() - 2));
        }
        if (std::regex_match(trimmed, bool_re)) {
            return Node(trimmed == "true");
        }
        if (std::regex_match(trimmed, float_re)) {
            return Node(std::stof(trimmed));
        }
        if (std::regex_match(trimmed, int_re)) {
            return Node(std::stoi(trimmed));
        }
        if (std::regex_match(trimmed, arr_re)) {
            std::string arr_body = std::regex_replace(trimmed, arr_re, "$1");
            std::vector<Node> arr_values;
            std::stringstream item;
            bool in_string = false;
            int depth = 0;

            for (char c : arr_body) {
                if (c == '\"' && (item.str().empty() || item.str().back() != '\\')) {
                    in_string = !in_string;
                }
                if (!in_string && c == '[') depth++;
                if (!in_string && c == ']') depth--;
                if (!in_string && c == ',' && depth == 0) {
                    std::string part = trim(item.str());
                    bool part_valid = true;
                    if (!part.empty()) arr_values.push_back(parse_value(part, part_valid));
                    if (!part_valid) { valid = false; return Node(); }
                    item.str(""); item.clear();
                }
                else {
                    item << c;
                }
            }

            std::string last = trim(item.str());
            if (!last.empty()) {
                bool part_valid = true;
                arr_values.push_back(parse_value(last, part_valid));
                if (!part_valid) { valid = false; return Node(); }
            }

            return Node(arr_values);
        }

        valid = false;
        return Node();
    }

    Root parse(const std::string& input) {
        Root root;
        Node current = root;
        std::istringstream ss(input);
        std::string line;

        std::regex section_re(R"(\[\s*([A-Za-z0-9_.\-]+)\s*\])");
        std::regex kv_re(R"(^([\w\-_]+)\s*=\s*(.+))");

        while (std::getline(ss, line)) {
            line = trim(line);
            if (line.empty() || line[0] == '#') continue;

            size_t hash = line.find('#');
            if (hash != std::string::npos && (line.find('"') == std::string::npos || hash < line.find('"')))
                line = trim(line.substr(0, hash));

            std::smatch match;
            if (std::regex_match(line, match, section_re)) {
                std::string section_path = match[1];
                if (section_path.front() == '.' || section_path.back() == '.') {
                    root.set_valid(false);
                    return root;
                }

                current = root;
                std::istringstream s(section_path);
                std::string part;
                while (std::getline(s, part, '.')) {
                    if (!current.access_impl()->children.count(part))
                        current.access_impl()->children[part] = Node();
                    current = current.access_impl()->children[part];
                }
                continue;
            }

            if (std::regex_match(line, match, kv_re)) {
                std::string key = match[1];
                std::string val = trim(match[2]);

                if (current.access_impl()->children.count(key)) {
                    root.set_valid(false);
                    return root;
                }

                bool value_valid = true;
                Node value = parse_value(val, value_valid);
                if (!value_valid) {
                    root.set_valid(false);
                    return root;
                }

                current.access_impl()->children[key] = value;
                continue;
            }

            root.set_valid(false);
            return root;
        }

        root.set_valid(true);
        return root;
    }

}
