#pragma once

#include <string>
#include <memory>
#include <vector>

namespace omfl {

    class NodeImpl; // forward declaration

    class Node {
    public:
        bool IsInt() const;
        int AsInt() const;
        int AsIntOrDefault(int def) const;

        bool IsFloat() const;
        float AsFloat() const;
        float AsFloatOrDefault(float def) const;

        bool IsString() const;
        std::string AsString() const;
        std::string AsStringOrDefault(const std::string& def) const;

        bool IsBool() const;
        bool AsBool() const;
        bool AsBoolOrDefault(bool def) const;

        bool IsArray() const;
        Node operator[](size_t index) const;

        Node Get(const std::string& key) const;

        Node();
        Node(const std::string& val);
        Node(int val);
        Node(float val);
        Node(bool val);
        Node(const std::vector<Node>& array);

        bool IsValid() const;
        void SetInvalid();

        std::shared_ptr<NodeImpl>& access_impl();

    private:
        std::shared_ptr<NodeImpl> impl;
    };

    class Root : public Node {
    public:
        bool valid() const;
        void set_valid(bool is_valid);
    private:
        bool is_valid_ = true;
    };

    Root parse(const std::string& input);

}
