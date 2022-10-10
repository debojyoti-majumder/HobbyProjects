package main

import (
	"fmt"
	"os"
)

func showHelp(commands []string) {
	fmt.Println("Valid commands:")

	// we use this for going over elements in a slice
	for _, command := range commands {
		fmt.Print(command)
		fmt.Print(" ")
	}

	fmt.Println("")
}

type ICommandTask interface {
	process() int
}

type UserCommand struct {
}

type TaskCommand struct {
}

type AssignCommand struct {
}

func (cmd AssignCommand) process() int {
	fmt.Println("Invoking assign command")
	return 0
}

func (cmd UserCommand) process() int {
	fmt.Println("Invoking user commands")
	return 0
}

func (cmd TaskCommand) process() int {
	fmt.Println("Invoking task commands")
	return 0
}

func processTask() {
	fmt.Println("Processing task reqeuest")
}

func processUser() {
	fmt.Println("Processing user request")
}

func assignTask() {
	fmt.Println("Processing taks assignment operation")
}

func cmdIndex(subCommands []string, inp string) int {
	findIndex := -1

	for i, value := range subCommands {
		if inp == value {
			return i
		}
	}
	return findIndex
}

func main() {
	fmt.Println("Staring ToDo Cli application")
	// Defining sub commands
	subCommands := make([]string, 0)
	commandFunctions := make([]ICommandTask, 0)

	subCommands = append(subCommands, "task")
	commandFunctions = append(commandFunctions, TaskCommand{})

	subCommands = append(subCommands, "user")
	commandFunctions = append(commandFunctions, UserCommand{})

	subCommands = append(subCommands, "assign")
	commandFunctions = append(commandFunctions, AssignCommand{})

	fmt.Println(subCommands)
	commandLineArgs := os.Args[1:]

	if len(commandLineArgs) == 0 {
		fmt.Println("No sub commands passed")
		showHelp(subCommands)
		return
	}

	inputCommand := os.Args[1]
	inputIndex := cmdIndex(subCommands, inputCommand)

	if inputIndex == -1 {
		showHelp(subCommands)
		return
	}

	// This would be removed at a later point in time
	switch inputIndex {
	case 0:
		processTask()
	case 1:
		processUser()
	case 2:
		assignTask()
	default:
		showHelp(subCommands)
	}

	// This is the generic invoke that I am calling
	commandFunctions[inputIndex].process()
}
