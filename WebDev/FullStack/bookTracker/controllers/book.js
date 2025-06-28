let books = [];

export const getBook = (_, res) => {
    if (books.length === 0) {
        return res.status(400).json({
            status: "error",
            message: "No Books",
        });
    }

    res.json({ status: "ok", booklist: books });
};

export const saveBook = (req, res) => {
    const title = req.body.title.trim();
    const author = req.body.author.trim();
    const hasRead = req.body.hasRead.trim();

    if (!title || !author || !hasRead) {
        return res.status(400).json({
            status: "error",
            message: "Paramaters not passed",
        });
    }

    books.push({
        title: title,
        author: author,
        hasRead: hasRead,
    });

    res.json({ status: "ok" });
};
