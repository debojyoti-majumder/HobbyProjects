package main

import (
	"github.com/debojyoti-majumder/taskgin/services"
	"github.com/gin-gonic/gin"
	"gorm.io/driver/sqlite"
	"gorm.io/gorm"
)

func main() {
	defaultRouter := gin.Default()

	// Setting up connection with local database
	db, err := gorm.Open(sqlite.Open("tasks.db"), &gorm.Config{})
	if err != nil {
		panic("Failed to connected with db")
	}

	// Creatig the tasks controller
	taskRouter := defaultRouter.Group("/tasks")
	services.SetupTaskService(taskRouter, db)

	defaultRouter.Run(":8080")
}
