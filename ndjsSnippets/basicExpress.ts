import express, { Express, Request, Response, Router }  from "express"
import bodyParser from "body-parser"

const usersRoute:Router = express.Router()
const app:Express = express();

usersRoute.post("/", (req:Request, res:Response) => {
    console.log(req);
    res.send({});
});


usersRoute.get("/", (req:Request, res:Response) => {
    console.log(req);
    res.send({});
});

app.use('/users', usersRoute);
app.use(bodyParser.urlencoded({extended:false}));

app.listen(3000, () => {
    console.log("Application Server is now running")
});
