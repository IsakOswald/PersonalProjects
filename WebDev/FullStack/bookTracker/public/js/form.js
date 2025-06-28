const errorHeading = document.getElementById("errorH");
const booksList = document.getElementById("booksUL");
const refreshButton = document.getElementById("refresh");
const form = document.getElementById("form");

const title = document.getElementById("titleInput");
const author = document.getElementById("authorInput");
const hasRead = document.getElementById("hasReadInput");

refreshButton.addEventListener("click", async (e) => {
    e.preventDefault();

    try {
        const response = await fetch("http://localhost:3000/api/book");
        const data = await response.json();

        if (!response.ok || data.status === "error") {
            errorHeading.textContent = data.message;
            return;
        }

        const bookList = data.booklist;

        bookList.forEach((book) => {
            const newItem = document.createElement("li");
            newItem.textContent = book.title;

            booksList.appendChild(newItem);
        });
    } catch (error) {
        errorHeading.textContent = error;
    }
});

form.addEventListener("submit", async (e) => {
    e.preventDefault();

    const newBook = {
        title: title.value.trim(),
        author: author.value.trim(),
        hasRead: hasRead.value.trim(),
    };

    try {
        const response = await fetch("http://localhost:3000/api/book", {
            method: "POST",
            headers: {
                "Content-Type": "application/json",
            },
            body: JSON.stringify(newBook),
        });
        const data = await response.json();

        if (!response.ok || data.status === "error") {
            errorHeading.textContent = data.message;
            return;
        }

        errorHeading.textContent = data.status;
    } catch (error) {
        errorHeading.textContent = error;
    }
});
