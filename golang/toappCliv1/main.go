package main

import (
	"fmt"
	"os"
)

func showHelp(commands []string) {

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
	fmt.Println(inputCommand)
}
