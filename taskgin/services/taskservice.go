package services

import (
	"log"
	"net/http"
	"strconv"

	"github.com/gin-gonic/gin"
	"gorm.io/gorm"
)

type Task struct {
	gorm.Model
	Caption string
	Done    bool
}

var tasks []Task
var repository *gorm.DB

func SetupTaskService(
	router *gin.RouterGroup,
	db *gorm.DB) {
	tasks = []Task{}

	repository = db
	repository.AutoMigrate(&Task{})

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

	repository.Create(&newTask)
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

	// Finds the tasks by ID
	var foundTask Task
	repository.First(&foundTask, id)

	ctx.JSON(http.StatusOK, foundTask)
}
