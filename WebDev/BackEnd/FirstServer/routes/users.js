const express = require("express");
const router = express.Router(); //Create a router, like a subset of the entier backend.

//req = what the user sends to the sever.
//res = what the server sends to the user.

router.get("/", (_, res) => {
    res.send("User List Here");
});

router.get("/new", (_, res) => {
    res.send("Create new user form here");
});

//Instead of manually typing these out, we can chain them using router.route("/:id").get().post().put().delete();

router.get("/:id", (req, res) => {
    //:id is a variable
    res.send(`Got User: ${JSON.stringify(req.user.name)}`); // Get the id
});

router.put("/:id", (req, res) => {
    //:id is a variable
    res.send(`Got User: ${req.params.id}`); // Get the id
});

router.delete("/:id", (req, res) => {
    //:id is a variable
    res.send(`Got User: ${req.params.id}`); // Get the id
});

const users = [{ name: "isak" }, { name: "john" }]; //Just say we have an arrays of users.

router.param("id", (req, res, next, id) => {
    //router.param allows us to access the params BEFORE any request is fufilled.
    req.user = users[id];
    next(); //Runs the next peice of middlewear.
});

module.exports = router; //Export it
