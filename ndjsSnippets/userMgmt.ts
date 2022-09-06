import express, { Express, Request, Response, Router }from "express"

const app:Express = express()

const usersRoute:Router = express.Router();

export class UserCreationRequest {
    firstName: String;
    lastName: String;
    email: String;

    // This where the parsing should happen
    constructor(input:any) {
        this.firstName = input.firstName;
        this.lastName = input.lastName;
        this.email = input.email;
    }
}

export class UsersController {
    // This should not return a new object of user
    addUser(req:UserCreationRequest) {
        return {"created":true};
    }
}

const usersController = new UsersController();

usersRoute.post("/", (req:Request, res:Response) => {
    let userCreationRequestInput = req.body;
    let creatReq = new UserCreationRequest(userCreationRequestInput);
    
    let response = usersController.addUser(creatReq);
    res.status(200);
    res.send(response);
});

app.use(express.json());
app.use("/users", usersRoute);

app.listen(3000, () => {
    console.log("Users mgmt is now running");
});
