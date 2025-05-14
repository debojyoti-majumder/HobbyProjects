package main

import (
	"net/http"
	"strconv"

	"github.com/gin-gonic/gin"
)

type Task struct {
	ID      int
	Caption string
	Done    bool
}

var tasks []Task

func createTask(ctx *gin.Context) {
	var newTask Task

	// Parsing the task object from JSON
	if err := ctx.BindJSON(&newTask); err != nil {
		ctx.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	newTask.ID = len(tasks) + 1
	tasks = append(tasks, newTask)

	// Returning the response after the task is done
	ctx.JSON(http.StatusCreated, newTask)
}

func getAllTasks(ctx *gin.Context) {
	ctx.JSON(http.StatusOK, tasks)
}

func getSingleTask(ctx *gin.Context) {
	idValue := ctx.Param("id")
	id, err := strconv.Atoi(idValue)

	if err != nil {
		ctx.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	for _, task := range tasks {
		if task.ID == id {
			ctx.JSON(http.StatusOK, task)
			return
		}
	}

	ctx.JSON(http.StatusNotFound, gin.H{"id": id})
}

func main() {
	defaultRouter := gin.Default()

	// Setting the main operations for the tasks
	defaultRouter.POST("/tasks", createTask)
	defaultRouter.GET("/tasks", getAllTasks)
	defaultRouter.GET("/tasks/:id", getSingleTask)

	defaultRouter.Run(":8080")
}

/*
Testing out these APIs

debojyotim@MR9Q0VGKM2 ~ % curl -X POST -H "Content-Type: application/json" -d '{"Caption": "Buy groceries", "done": false}' http://localhost:8080/tasks
{"ID":2,"Caption":"Buy groceries","Done":false}%

debojyotim@MR9Q0VGKM2 ~ % curl -X GET http://localhost:8080/tasks

curl -X GET http://localhost:8080/tasks/2
{"ID":2,"Caption":"Buy groceries","Done":false}
*/
