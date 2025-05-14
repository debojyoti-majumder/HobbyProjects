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
var idCounter int

func createTask(ctx *gin.Context) {
	var newTask Task

	// Parsing the task object from JSON
	if err := ctx.BindJSON(&newTask); err != nil {
		ctx.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	// The ID always increases
	newTask.ID = idCounter + 1
	idCounter++

	tasks = append(tasks, newTask)

	// Returning the response after the task is done
	ctx.JSON(http.StatusCreated, newTask)
}

func getAllTasks(ctx *gin.Context) {
	ctx.JSON(http.StatusOK, tasks)
}

func getTaskbyId(ctx *gin.Context) {
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
	idCounter = 0
	defaultRouter := gin.Default()

	taskRouter := defaultRouter.Group("/tasks")

	taskRouter.GET("", getAllTasks)
	taskRouter.POST("", createTask)
	taskRouter.GET("/:id", getTaskbyId)

	defaultRouter.Run(":8080")
}

/*
Testing out these APIs

% curl -X POST -H "Content-Type: application/json" -d '{"Caption": "Buy groceries", "done": false}' http://localhost:8080/tasks
{"ID":2,"Caption":"Buy groceries","Done":false}%

% curl -X GET http://localhost:8080/tasks

curl -X GET http://localhost:8080/tasks/2
{"ID":2,"Caption":"Buy groceries","Done":false}
*/
