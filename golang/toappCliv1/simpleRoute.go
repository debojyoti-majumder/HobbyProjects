package main

import (
	"net/http"

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

func addNewUser(httpContext *gin.Context) {
	var newUser SimpleUser

	err := httpContext.Bind(newUser)

	if err != nil {
		httpContext.IndentedJSON(
			http.StatusBadRequest,
			gin.H{"message": "Unable to parse JSON"},
		)

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
	defaultRouter.POST("/users", addNewUser)

	defaultRouter.Run("localhost:8080")
}
