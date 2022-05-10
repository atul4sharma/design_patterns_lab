
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Principle: A class should have a single responsibility
struct Journal
{
    std::string title;
    std::vector<std::string> entries;

    Journal(std::string const & title)
        :title{title}
    {}

    void add_entry(std::string const & entry)
    {
        static int count{};
        entries.emplace_back(std::to_string(++count) + ": " + entry);
    }
};

struct PersistenceManager
{
    static void save(Journal const & j, std::string const & filename)
    {
        auto f = std::ofstream{filename};
        for(auto const & entry: j.entries)
            f << entry << "\n";
    }
};

int main()
{
    auto journal = Journal("Diary");

    journal.add_entry("I worked hard today");
    journal.add_entry("I filled blog today");

    PersistenceManager::save(journal, "diary.txt");

    return 0;
}
