package main

import (
	"github.com/debojyoti-majumder/taskgin/services"
	"github.com/gin-gonic/gin"
)

func main() {
	defaultRouter := gin.Default()

	// Creatig the tasks controller
	taskRouter := defaultRouter.Group("/tasks")
	services.SetupTaskService(taskRouter)

	defaultRouter.Run(":8080")
}
