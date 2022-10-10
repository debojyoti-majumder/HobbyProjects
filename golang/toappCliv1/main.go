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
	subCommands := make([]string, 3)
	subCommands[0] = "task"
	subCommands[1] = "user"
	subCommands[2] = "assign"

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
}
