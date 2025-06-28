import express from "express";
import * as bookRouter from "../controllers/book.js";

const router = express.Router();

router.get("/book", bookRouter.getBook);
router.post("/book", bookRouter.saveBook);

export default router;
