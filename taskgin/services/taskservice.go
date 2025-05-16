package services

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

var idCounter int
var tasks []Task

func SetupTaskService(router *gin.RouterGroup) {
	tasks = []Task{}
	idCounter = 0

	router.POST("", CreateTask)
	router.GET("", GetAllTasks)
	router.GET("/:id", GetTaskbyId)
}

func CreateTask(ctx *gin.Context) {
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

func GetAllTasks(ctx *gin.Context) {
	ctx.JSON(http.StatusOK, tasks)
}

func GetTaskbyId(ctx *gin.Context) {
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
