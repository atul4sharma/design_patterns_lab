
// Implement a strategy to print list of items in different format

#include <memory>
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

struct TextProcessor
{
    public:
        void set_output_format(OutputFormat const & format)
        {
            clear();
            switch (format) {
                case OutputFormat::html:
                    _strategy = std::make_unique<HtmlStrategy>();
                    break;
                case OutputFormat::markdown:
                    _strategy = std::make_unique<MarkdownStrategy>();
                    break;
            }
        }

        void append(std::vector<std::string> const & items)
        {
            _strategy->start(_oss);
            for(auto const & item : items)
                _strategy->add_list_item(_oss, item);
            _strategy->end(_oss);
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
        std::ostringstream            _oss;
        std::unique_ptr<ListStrategy> _strategy;
};


int main(int const argc, char const * argv[])
{
    auto const items = std::vector<std::string>{"foo", "bar", "baz"};

    auto       text_processor = TextProcessor{};
    text_processor.set_output_format(OutputFormat::html);
    text_processor.append(items);
    std::cout << text_processor.str() << "\n";

    text_processor.set_output_format(OutputFormat::markdown);
    text_processor.append(items);
    std::cout << text_processor.str() << "\n";

    return 0;
}
