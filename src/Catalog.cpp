#include "Catalog.h"
#include "LoanManager.h"
#include <algorithm>
#include <cctype>

Catalog::Catalog() : loanManager_(nullptr) {}

Catalog::Catalog(LoanManager* loanManager)
    : loanManager_(loanManager) {}

void Catalog::addBook(const Book& book) {

    for (const auto& b : books_) {
        if (b.getISBN() == book.getISBN()) {
            return;
        }
    }

    books_.push_back(book);
}

bool Catalog::removeBook(const std::string& isbn) {

    if (loanManager_ != nullptr) {

        auto activeLoans = loanManager_->getActiveLoans();

        for (const auto& loan : activeLoans) {
            if (loan.getBookISBN() == isbn) {
                return false;
            }
        }
    }

    for (int i = 0; i < static_cast<int>(books_.size()); ++i) {

        if (books_[i].getISBN() == isbn) {
            books_.erase(books_.begin() + i);
            return true;
        }
    }

    return false;
}

bool Catalog::removeBookByIndex(int index) {

    if (index < 0 || index >= static_cast<int>(books_.size()))
        return false;

    books_.erase(books_.begin() + index);
    return true;
}

std::optional<Book*> Catalog::findByISBN(const std::string& isbn) {

    for (auto& book : books_) {

        if (book.getISBN() == isbn) {
            return &book;
        }
    }

    return std::nullopt;
}

std::vector<Book*> Catalog::searchByTitle(const std::string& query) {

    std::vector<Book*> results;

    std::string q = query;
    std::transform(q.begin(), q.end(), q.begin(), ::tolower);

    for (auto& book : books_) {

        std::string title = book.getTitle();
        std::transform(title.begin(), title.end(), title.begin(), ::tolower);

        if (title.find(q) != std::string::npos) {
            results.push_back(&book);
        }
    }

    return results;
}

std::vector<Book*> Catalog::searchByAuthor(const std::string& query) {

    std::vector<Book*> results;

    std::string q = query;
    std::transform(q.begin(), q.end(), q.begin(), ::tolower);

    for (auto& book : books_) {

        std::string author = book.getAuthor();
        std::transform(author.begin(), author.end(), author.begin(), ::tolower);

        if (author.find(q) != std::string::npos) {
            results.push_back(&book);
        }
    }

    return results;
}

std::vector<Book*> Catalog::getAvailableBooks() {

    std::vector<Book*> results;

    for (auto& book : books_) {

        if (book.getAvailableCopies() > 0) {
            results.push_back(&book);
        }
    }

    return results;
}

std::vector<Book*> Catalog::getAllBooks() {

    std::vector<Book*> results;

    for (auto& book : books_) {
        results.push_back(&book);
    }

    return results;
}

std::vector<Book*> Catalog::getBooksByGenre(const std::string& genre) {

    std::vector<Book*> results;

    std::string g = genre;
    std::transform(g.begin(), g.end(), g.begin(), ::tolower);

    for (auto& book : books_) {

        std::string bg = book.getGenre();
        std::transform(bg.begin(), bg.end(), bg.begin(), ::tolower);

        if (bg == g) {
            results.push_back(&book);
        }
    }

    return results;
}

void Catalog::sortByTitle() {

    std::sort(books_.begin(), books_.end(),
        [](const Book& a, const Book& b) {

            return a.getTitle() < b.getTitle();
        });
}

void Catalog::sortByAuthor() {

    std::sort(books_.begin(), books_.end(),
        [](const Book& a, const Book& b) {

            return a.getAuthor() < b.getAuthor();
        });
}