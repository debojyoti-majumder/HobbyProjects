import readline from 'readline'

class ElevatorScheduler {
    /**
     * 
     * @param {Number} maxNumOfFloors 
     */
    constructor(maxNumOfFloors) {
        this.floorCount = maxNumOfFloors

        // As of now using hard coded elevators
        this.elevatorCount = 2
        this.interValObjects = {}
    }

    routeMonitor() {
        console.log("Should have a job ID for this")
    }

    /**
     * Ideally this function should return a promise then the request has been served
     * 
     * @param {Number} source 
     * @param {Number} destination 
     */
    schedule(source, destination) {
        if( source == destination ) {
            console.log("Elevator does not require to move")
            return
        }

        const upDirection = false;

        if( destination > source ) {
            upDirection = true
        }

        const jobIntervalObject = setInterval( () => {
            this.routeMonitor(),
            1000
        });
    }
}

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
        this.scheduler = null
    }

    /**
     * 
     * @param {string} inputString 
     */
    processInput(inputString) {
        if( inputString === "help" ) {
            console.log("ELEV 10")
            console.log("SCHED 3 8")
            return
        }

        let inputStringArr = inputString.split(/(\s+)/);
        let command = inputStringArr[0];

        if( command === "ELEV" ) {
            if( this.scheduler == null ) {
                // The data would be fected later
                this.scheduler = new ElevatorScheduler(14);
            }
        }
        else if( command == "SCHED" ) {
            if( this.scheduler != null ) {
                // This data would be parsed later
                const source = parseInt(inputStringArr[2])
                const destination = parseInt(inputStringArr[4])

                console.log(`${source} ---> ${destination}`)
                this.scheduler.schedule(source,destination)
            } 
        }

        console.log(`Command ${inputStringArr[0]}`)
    }

    start() {
        const quitMessage = `Enter ${this.loopStop} to quit:`;
        console.log(quitMessage);

        this.readLine.question("# ",(input) => {            
            this.processInput(input);
            
            // This is a recusrive function call, which is added to 
            // replace a while loop. Using a while loop would not work
            // in this async scenario
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
