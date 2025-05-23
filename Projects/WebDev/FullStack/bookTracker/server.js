import express from "express";
import bookRouter from "./routes/book.js";

const app = express();
const PORT = 3000;

app.use(express.static("./public/"));
app.use(express.json());

app.get("/", (_, res) => {
    res.send(`Up`);
});

app.use("/api", bookRouter);

app.listen(PORT, () => {
    console.log(`Sever up on port ${PORT}`);
});
