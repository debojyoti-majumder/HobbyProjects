package main

import (
	"bufio"
	"context"
	"fmt"
	"log"
	"os"

	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
)

type ApplicationUser struct {
	Email string
	Id    string
}

const connectionUri = "mongodb+srv://"

func printOptions() {
	fmt.Println("1. Add new user")
	fmt.Println("2. Remove an user")
	fmt.Println("3. List all users")
	fmt.Println("0. Quit")
}

func addUser(user ApplicationUser, pass string) {
	fmt.Print("Adding new user")
}

func removeUser(user ApplicationUser) {
	fmt.Println("Removing user")
}

func listAllUsers() {
	fmt.Println("Listing all users")
}

func main() {
	serverApiVserion := options.ServerAPI(options.ServerAPIVersion1)

	// Connection options
	opts := options.Client()
	opts.ApplyURI(connectionUri)
	opts.SetServerAPIOptions(serverApiVserion)

	// Connecting to database
	mongoClient, err := mongo.Connect(context.TODO(), opts)
	if err != nil {
		log.Fatal(err)
		panic(err)
	}

	// Anynomumus defer func
	defer func() {
		fmt.Println("Closing database connection")

		err := mongoClient.Disconnect(context.TODO())
		if err != nil {
			panic(err)
		}
	}()

	fmt.Println("Connection to DB established")

	val := 1
	consoleReader := bufio.NewReader(os.Stdin)

	for val > 0 {
		printOptions()
		fmt.Scanf("%d\n", &val)

		switch val {
		case 1:
			fmt.Print("Email:")
			userEmail, _ := consoleReader.ReadString('\n')
			fmt.Print("Password:")
			password, _ := consoleReader.ReadString('\n')

			newUser := ApplicationUser{
				Email: userEmail,
				Id:    "",
			}

			addUser(newUser, password)
			fmt.Println(newUser)

		case 2:
			fmt.Print("Id:")
			userId, _ := consoleReader.ReadString('\n')

			tbdUser := ApplicationUser{
				Email: "",
				Id:    userId,
			}

			removeUser(tbdUser)

		case 3:
			listAllUsers()

		case 0:
			fmt.Println("Quiting applications")

		default:
			fmt.Println("Invalid option")
		}
	}

	fmt.Println("End of program")
}
