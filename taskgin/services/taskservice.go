package services

import (
	"log"
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

	log.Println("Setting up API handlers")

	router.POST("", createTask)
	router.GET("", getAllTasks)
	router.GET("/:id", getTaskbyId)
}

func createTask(ctx *gin.Context) {
	var newTask Task

	log.Print("Creating a new task")

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
	log.Print("Getting all the task")
	ctx.JSON(http.StatusOK, tasks)
}

func getTaskbyId(ctx *gin.Context) {
	idValue := ctx.Param("id")
	id, err := strconv.Atoi(idValue)

	log.Printf("Getting tasks for id %d\n", id)

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

	log.Println("Task not found")
	ctx.JSON(http.StatusNotFound, gin.H{"id": id})
}
