
// Implement a strategy to print list of items in different format

#include <sstream>
#include <string>
#include <vector>
#include <iostream>

enum class OutputFormat
{
    markdown,
    html
};

struct ListStrategy
{
    virtual void start(std::ostringstream & oss) {}
    virtual void add_list_item(std::ostringstream& oss, std::string const & item) = 0;
    virtual void end(std::ostringstream & oss)   {}

    virtual ~ListStrategy() = default;
};

struct HtmlStrategy : ListStrategy
{
    void start(std::ostringstream & oss) override
    {
        oss << "<ul>\n";
    }

    void add_list_item(std::ostringstream & oss, std::string const & item) override
    {
        oss << "  <li>" << item << "</li>\n";
    }

    void end(std::ostringstream & oss) override
    {
        oss << "</ul>\n";
    }
};

struct MarkdownStrategy : ListStrategy
{
    void add_list_item(std::ostringstream & oss, std::string const & item) override
    {
        oss << "- " << item << "\n";
    }
};

template <typename LS>
struct TextProcessor
{
    public:

        void append(std::vector<std::string> const & items)
        {
            _strategy.start(_oss);
            for(auto const & item : items)
                _strategy.add_list_item(_oss, item);
            _strategy.end(_oss);
        }

        std::string const str() const
        {
            return _oss.str();
        }

        void clear()
        {
            _oss.str("");
            _oss.clear();
        }

    private:
        std::ostringstream _oss;
        LS                 _strategy;
};


int main(int const argc, char const * argv[])
{
    auto const items = std::vector<std::string>{"foo", "bar", "baz"};

    auto       html_processor = TextProcessor<HtmlStrategy>{};
    html_processor.append(items);
    std::cout << html_processor.str() << "\n";

    auto       md_processor = TextProcessor<MarkdownStrategy>{};
    md_processor.append(items);
    std::cout << md_processor.str() << "\n";

    return 0;
}
