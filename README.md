# Library-management-using-AVL-Trees
A library management system developed using AVL trees in C++ language. Performs basic tasks like keeping records of books borrowed, returned, fined etc.
Developed a simple database to store the book details and perform various operations like book issue/renew etc, of a small library.
Library Details
a) Books (all books are single authored ones)
b) Users – faculty, staff, students
Book record format:
1. bookid, bookname, publisher, edition, author, issued_to, date_of_issue
User record format:
1. uid, uname, utype, gender, contact
Operations on Books
1. issuance of a given book
2. renewal of a given book
3. books that are overdue (should display the bookids and the total number of books overdue).
4. check status of a given book (available ? or issued, If so to whom?)
5. deleting a given book (no further issuance is possible)

Book and User details have to be maintained in separate (unordered) files, and the details can be added directly to the respective files.
However when application is started, in order to carrying out the operations mentioned above, the program should read the required data about the books into an appropriate search tree. At the time of closing of application, for making the changes made to remain permanent, it should write back the data in the search tree into appropriate files.
