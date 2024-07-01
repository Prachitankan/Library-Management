#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Include this for std::remove_if

class Book
{
public:
    int id;
    std::string title;
    std::string author;
    bool isBorrowed;

    Book(int id, std::string title, std::string author)
        : id(id), title(title), author(author), isBorrowed(false) {}
};

class Library
{
private:
    std::vector<Book> books;

public:
    void addBook(int id, std::string title, std::string author)
    {
        books.emplace_back(id, title, author);
    }

    void removeBook(int id)
    {
        books.erase(std::remove_if(books.begin(), books.end(),
                                   [id](const Book &b)
                                   { return b.id == id; }),
                    books.end());
    }

    void borrowBook(int id)
    {
        for (auto &book : books)
        {
            if (book.id == id && !book.isBorrowed)
            {
                book.isBorrowed = true;
                std::cout << "Book borrowed successfully." << std::endl;
                return;
            }
        }
        std::cout << "Book not available." << std::endl;
    }

    void returnBook(int id)
    {
        for (auto &book : books)
        {
            if (book.id == id && book.isBorrowed)
            {
                book.isBorrowed = false;
                std::cout << "Book returned successfully." << std::endl;
                return;
            }
        }
        std::cout << "Book not found." << std::endl;
    }

    void listBooks()
    {
        for (const auto &book : books)
        {
            std::cout << std::endl;
            std::cout << " ID: " << book.id
                      << "\nTitle: " << book.title
                      << "\nAuthor: " << book.author
                      << "\nBorrowed: " << (book.isBorrowed ? "Yes" : "No") << std::endl
                      << std::endl
                      << "## ----------------- ******* ---------------------- ##" << std::endl;

            std::cout << std::endl;
        }
    }

    void searchBookByTitle(const std::string &title)
    {
        for (const auto &book : books)
        {
            if (book.title.find(title) != std::string::npos)
            {
                std::cout << std::endl;
                std::cout << " ID: " << book.id
                          << "\nTitle: " << book.title
                          << "\nAuthor: " << book.author
                          << "\nBorrowed: " << (book.isBorrowed ? "Yes" : "No") << std::endl
                          << std::endl
                          << "## ----------------- ******* ---------------------- ##" << std::endl;

                std::cout << std::endl;
            }
        }
    }

    void searchBookByAuthor(const std::string &author)
    {
        for (const auto &book : books)
        {
            if (book.author.find(author) != std::string::npos)
            {
                std::cout << std::endl;
                std::cout << " ID: " << book.id
                          << "\nTitle: " << book.title
                          << "\nAuthor: " << book.author
                          << "\nBorrowed: " << (book.isBorrowed ? "Yes" : "No") << std::endl
                          << std::endl
                          << "## ----------------- ******* ---------------------- ##" << std::endl;

                std::cout << std::endl;
            }
        }
    }
};

int main()
{
    Library library;

    // Initialize the library with at least 10 books
    library.addBook(1, "1984", "George Orwell");
    library.addBook(2, "To Kill a Mockingbird", "Harper Lee");
    library.addBook(3, "The Great Gatsby", "F. Scott Fitzgerald");
    library.addBook(4, "Pride and Prejudice", "Jane Austen");
    library.addBook(5, "The Catcher in the Rye", "J.D. Salinger");
    library.addBook(6, "Moby-Dick", "Herman Melville");
    library.addBook(7, "War and Peace", "Leo Tolstoy");
    library.addBook(8, "The Odyssey", "Homer");
    library.addBook(9, "Brave New World", "Aldous Huxley");
    library.addBook(10, "Crime and Punishment", "Fyodor Dostoevsky");

    int choice, id;
    std::string title, author;

    while (true)
    {
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

        switch (choice)
        {
        case 1:
            std::cout << "Enter book ID: ";
            std::cin >> id;
            std::cin.ignore(); // to ignore newline character left by std::cin
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
            std::cin.ignore(); // to ignore newline character left by std::cin
            std::cout << "Enter book title to search: ";
            std::getline(std::cin, title);
            library.searchBookByTitle(title);
            break;
        case 7:
            std::cin.ignore(); // to ignore newline character left by std::cin
            std::cout << "Enter book author to search: ";
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
