import readline from 'readline'

class ReplLoop {
    /**
     * 
     * @param {function () {
        *
     }} onQuit 
     */
    constructor(onQuit) {
        this.loopStop = "q";

        // This object would be used to read from the console
        this.readLine = readline.createInterface({
            input: process.stdin,
            output: process.stdout
        });

        this.onLoopEnd = onQuit;
    }

    /**
     * 
     * @param {string} inputString 
     */
    processInput(inputString) {
        if( inputString === "help" ) {
            console.log("ELEV 10")
            console.log("SCHED 3 8")
        }
    }

    start() {
        const quitMessage = `Enter ${this.loopStop} to quit:`;
        console.log(quitMessage);

        this.readLine.question("# ",(input) => {            
            this.processInput(input);
            
            // This is a recusrive function call 
            if( input !== this.loopStop ) {
                this.start();
            }
            else {
                console.log("Quiting REPL loop");
                this.onLoopEnd();
            }
        })
    }
}

const exitHandler = () => {
    console.log("Shutting down main application")
    process.exit(0)    
}

// As of now it takes a function but may be better way implement it 
// via an event emmiter
console.log("Starting elevator application")
let applicationReplLoop = new ReplLoop(exitHandler)

// If event emiiter is not an option, then this function 
// can return a promise. Have to see if over loading the cosntrutor is possible
// or not
applicationReplLoop.start()
