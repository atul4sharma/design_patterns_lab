#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

namespace html {
    struct Tag
    {
        std::string      name;
        std::string      text;
        std::vector<Tag> children;
        std::vector<std::pair<std::string, std::string>> attributes;

        friend std::ostream& operator<<(std::ostream& os, const Tag& tag)
        {
            os << "<" << tag.name;
            for (const auto& att : tag.attributes)
                os << " " << att.first << "=\"" << att.second << "\"";
            if (tag.children.size() == 0 && tag.text.length() == 0)
            {
                os << "/>" << std::endl;
            }
            else
            {
                os << ">" << std::endl;
                if (tag.text.length())
                    os << tag.text << std::endl;
                for (const auto& child : tag.children)
                    os << child;
                os << "</" << tag.name << ">" << std::endl;
            }
            return os;
        }

      protected:
        Tag(const std::string& name, const std::string& text)
            : name{name},
            text{text}
        {}

        Tag(const std::string& name, const std::vector<Tag>& children)
            : name{name},
            children{children}
        {}
    };

    struct P : Tag
    {
        P(std::string const & text)
            :Tag{"p", text}
        {}

        P(std::initializer_list<Tag> const & elements)
            :Tag{"p", elements}
        {}

    };

    struct IMG : Tag
    {
        IMG(std::string const & url)
            :Tag{"img", ""}
        {
            Tag::attributes.emplace_back("src", url);
        }
    };

    struct LI : Tag
    {
        LI(std::string const &  text)
            :Tag{"li", text}
        {}
    };

    struct UL : Tag
    {
        UL(std::initializer_list<Tag> const & elements)
            :Tag{"ul", elements}
        {}
    };

}

int main()
{
    using namespace html;
    std::cout <<
        P {
            IMG {"http://pokemon.com/pikachu.png"},
            UL{
                LI{"first"},
                LI{"second"},
                LI{"third"}
            },
            IMG {"http://pokemon.com/pikachu2.png"}
        }
    << std::endl;

    return 0;
}

