const express = require("express");

const app = express();

//We need a view engine to use .reder(). So do <npm i ejs>;

app.set("view engine", "ejs"); //Set the type to view engine, and we are using ejs;
app.use(logger);
app.use(express.static("./public/"));

//***
//app.get("/", (_, res) => {
//    res.json({ message: "Error" }); //Send Json;
//    res.render("index"); //Should be in "views/" folder;
//    res.send("Message"); //Send Message;
//    res.download("/path/to/file"); //Send a donwload;
//    res.sendStatus(400); //Send a status;
//    res.status(400).send("Message"); //Send both at the same time;
//});
//***

app.get("/", (_, res) => {
    res.render("index", { text138931: "This is sent from the back end!" }); //When using in .ejs use locals.text
    //as it "local" is the object itself sent down.
});

const userRouter = require("./routes/users.js"); //Import the routher;

app.use("/users", userRouter); //We want the router to defualt at /users and pass in the user rounter (file).

function logger(req, _, next) {
    console.log(req.origionalUrl);
    next();
}

app.listen(3000);
