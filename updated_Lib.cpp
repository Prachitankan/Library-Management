#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <limits> // For std::numeric_limits

class Book {
public:
    int id;
    std::string title;
    std::string author;
    bool isBorrowed;

    Book(int id, std::string title, std::string author)
        : id(id), title(title), author(author), isBorrowed(false) {}

    Book() : id(0), title(""), author(""), isBorrowed(false) {}

    void fromString(const std::string& data) {
        std::stringstream ss(data);
        ss >> id;
        ss.ignore(); // Ignore the delimiter after id
        std::getline(ss, title, '|');
        std::getline(ss, author, '|');
        ss >> isBorrowed;
    }

    std::string toString() const {
        std::stringstream ss;
        ss << id << '|' << title << '|' << author << '|' << isBorrowed;
        return ss.str();
    }
};

class Library {
private:
    std::vector<Book> books;
    const std::string filename = "library_data.txt";
    std::unordered_set<int> bookIds;

    void loadBooks() {
        std::ifstream file(filename);
        if (!file.is_open()) return;

        std::string line;
        while (std::getline(file, line)) {
            Book book;
            book.fromString(line);
            books.push_back(book);
            bookIds.insert(book.id);
        }
        file.close();
    }

    void saveBooks() {
        std::ofstream file(filename);
        std::unordered_set<int> uniqueIds;
        for (const auto& book : books) {
            if (uniqueIds.insert(book.id).second) {
                file << book.toString() << '\n';
            }
        }
        file.close();
    }

public:
    Library() {
        loadBooks();
    }

    ~Library() {
        saveBooks();
    }

    void addBook(int id, std::string title, std::string author) {
    if (bookIds.find(id) != bookIds.end()) {
        std::cout << "Error: Book ID already exists." << std::endl;
        return;
    }

    Book newBook(id, title, author);
    auto it = std::lower_bound(books.begin(), books.end(), newBook, [](const Book& a, const Book& b) {
        return a.id < b.id;
    });

    books.insert(it, newBook);
    bookIds.insert(id);
}


    void removeBook(int id) {
        auto it = std::remove_if(books.begin(), books.end(),
                                 [id](const Book& b) { return b.id == id; });
        if (it != books.end()) {
            books.erase(it, books.end());
            bookIds.erase(id);
        }
    }

    void borrowBook(int id) {
        for (auto& book : books) {
            if (book.id == id && !book.isBorrowed) {
                book.isBorrowed = true;
                std::cout << "Book borrowed successfully." << std::endl;
                return;
            }
        }
        std::cout << "Book not available." << std::endl;
    }

    void returnBook(int id) {
        for (auto& book : books) {
            if (book.id == id && book.isBorrowed) {
                book.isBorrowed = false;
                std::cout << "Book returned successfully." << std::endl;
                return;
            }
        }
        std::cout << "Book not found." << std::endl;
    }

    void listBooks() {
        for (const auto& book : books) {
            std::cout << " ID: " << book.id
                      << "\nTitle: " << book.title
                      << "\nAuthor: " << book.author
                      << "\nBorrowed: " << (book.isBorrowed ? "Yes" : "No") << std::endl
                      << "## ----------------- ******* ---------------------- ##" << std::endl;
        }
    }

    void searchBookByTitle(const std::string& title) {
        for (const auto& book : books) {
            if (book.title.find(title) != std::string::npos) {
                std::cout << " ID: " << book.id
                          << "\nTitle: " << book.title
                          << "\nAuthor: " << book.author
                          << "\nBorrowed: " << (book.isBorrowed ? "Yes" : "No") << std::endl
                          << "## ----------------- ******* ---------------------- ##" << std::endl;
            }
        }
    }

    void searchBookByAuthor(const std::string& author) {
        for (const auto& book : books) {
            if (book.author.find(author) != std::string::npos) {
                std::cout << " ID: " << book.id
                          << "\nTitle: " << book.title
                          << "\nAuthor: " << book.author
                          << "\nBorrowed: " << (book.isBorrowed ? "Yes" : "No") << std::endl
                          << "## ----------------- ******* ---------------------- ##" << std::endl;
            }
        }
    }
};

int main() {
    Library library;

    // Initialize the library with at least 10 books
    // library.addBook(12, "Batman", "Bob Kane and Bill Finger");
    // library.addBook(13, "Spider-Man", "Stan Lee and Steve Ditko");
    // library.addBook(14, "Superman", "Jerry Siegel and Joe Shuster");
    // library.addBook(15, "X-Men", "Stan Lee and Jack Kirby");
    // library.addBook(16, "The Avengers", "Stan Lee");
    // library.addBook(17, "Wonder Woman", "William Moulton Marston");

    int choice, id;
    std::string title, author;

    while (true) {
        std::cout << "Library Management System" << std::endl;
        std::cout << "1. Add Book" << std::endl;
        std::cout << "2. Remove Book" << std::endl;
        std::cout << "3. Borrow Book" << std::endl;
        std::cout << "4. Return Book" << std::endl;
        std::cout << "5. List Books" << std::endl;
        std::cout << "6. Search Book by Title" << std::endl;
        std::cout << "7. Search Book by Author" << std::endl;
        std::cout << "8. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Validate input
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a valid number." << std::endl;
            continue;
        }

        switch (choice) {
            case 1:
                std::cout << "Enter book ID: ";
                std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
                std::cout << "Enter book title: ";
                std::getline(std::cin, title);
                std::cout << "Enter book author: ";
                std::getline(std::cin, author);
                library.addBook(id, title, author);
                break;
            case 2:
                std::cout << "Enter book ID to remove: ";
                std::cin >> id;
                library.removeBook(id);
                break;
            case 3:
                std::cout << "Enter book ID to borrow: ";
                std::cin >> id;
                library.borrowBook(id);
                break;
            case 4:
                std::cout << "Enter book ID to return: ";
                std::cin >> id;
                library.returnBook(id);
                break;
            case 5:
                library.listBooks();
                break;
            case 6:
                std::cout << "Enter book title to search: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
                std::getline(std::cin, title);
                library.searchBookByTitle(title);
                break;
            case 7:
                std::cout << "Enter book author to search: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
                std::getline(std::cin, author);
                library.searchBookByAuthor(author);
                break;
            case 8:
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    return 0;
}
