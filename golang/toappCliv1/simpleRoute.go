package main

import (
	"net/http"
	"strconv"

	"github.com/gin-gonic/gin"
)

type SimpleUser struct {
	ID        int    `json:"id"`
	FirstName string `json:"first_name"`
	LastName  string `json:"last_name"`
}

var allUsers = []SimpleUser{
	{ID: 0, FirstName: "administrator", LastName: "Majumder"},
}

var creationCount int

func getAllUsers(httpContext *gin.Context) {
	httpContext.IndentedJSON(http.StatusOK, allUsers)
}

func getUserbyID(httpContext *gin.Context) {
	var idString string

	idString = httpContext.Param("id")
	id, err := strconv.Atoi(idString)

	if err != nil {
		httpContext.IndentedJSON(
			http.StatusBadRequest,
			gin.H{"message": "needs to be an int"},
		)
		return
	}

	for _, user := range allUsers {
		if user.ID == id {
			httpContext.IndentedJSON(
				http.StatusOK,
				user,
			)

			return
		}
	}

	httpContext.IndentedJSON(
		http.StatusNotFound,
		gin.H{"message": "User with ID not found"},
	)
}

func addNewUser(httpContext *gin.Context) {
	var newUser SimpleUser

	err := httpContext.Bind(newUser)

	if err != nil {
		httpContext.IndentedJSON(
			http.StatusBadRequest,
			gin.H{"message": "Unable to parse JSON"},
		)

		println(err.Error())
		return
	}

	if newUser.ID != 0 {
		httpContext.IndentedJSON(
			http.StatusBadRequest,
			gin.H{"message": "ID parameter should not have been passed"},
		)

		return
	}

	newUser.ID = creationCount
	creationCount += 1

	// Added the user in memory
	allUsers = append(allUsers, newUser)

	httpContext.IndentedJSON(
		http.StatusOK,
		newUser,
	)
}

func main() {
	println("Running simple web application")

	defaultRouter := gin.Default()
	creationCount = 0

	// Setting up the routes
	defaultRouter.GET("/users", getAllUsers)
	defaultRouter.GET("/users/:id", getUserbyID)

	defaultRouter.POST("/users", addNewUser)

	// Running the server locally
	defaultRouter.Run("localhost:8080")
}
