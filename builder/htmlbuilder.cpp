
// When piecewise construction is complicated, then
// provide an API for doing it succintly

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

// Problem
// std::string output;
// output = "<p>";
// output += text;
// output += "<p>";
//
// We want to provide a better, scalable way to provide the construction of string in a better way

struct HtmlBuilder;

struct HtmlElement
{
    friend struct HtmlBuilder;
    friend struct std::vector<HtmlBuilder>;

    std::string str(int indent = 0) const
    {
        auto       oss = std::ostringstream{};
        auto const i   = std::string(static_cast<std::size_t>(indent_size * indent), ' ');
        oss << i << "<" << name << ">" << std::endl;

        if (text.size() > 0)
            oss << std::string(indent_size*(indent + 1), ' ') << text << std::endl;

        for (const auto& e : children)
            oss << e.str(indent + 1);

        oss << i << "</" << name << ">" << std::endl;

        return oss.str();
    }

  private:
    std::string              name;
    std::string              text;
    std::vector<HtmlElement> children;
    int                      indent_size{2};

    HtmlElement()
    {}

    HtmlElement(std::string const & name, std::string const & text)
        : name{name},
        text{text}
    {}

};

struct HtmlBuilder
{
    HtmlElement root;

    HtmlBuilder(std::string const & name)
        :root{name, ""}
    {}

    HtmlBuilder& add_child(std::string const & name, std::string const & text)
    {
#if 0
        root.children.emplace_back(name, text);
#else
        auto element = HtmlElement{name, text};
        root.children.emplace_back(std::move(element));
#endif
        return *this;
    }

    HtmlElement build() const
    {
        return root;
    }
};

HtmlBuilder create_htmlbuilder(std::string const & name)
{
    return HtmlBuilder{name};
}


int main()
{
    auto const unorderedListItems = create_htmlbuilder("ul")
        .add_child("li", "first")
        .add_child("li", "second")
        .add_child("li", "third")
        .build();

    std::cout << unorderedListItems.str() << "\n";
    return 0;
}

