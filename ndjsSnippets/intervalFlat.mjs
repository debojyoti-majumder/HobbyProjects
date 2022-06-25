// The purpose of this program is to use anync way to elumating a job which 
// would run for certain ammount of time

class JobManager {
    constructor() {
        this.jobMap = new Map();
        this.jobIdCounter = 0;
    }

    /**
     * 
     * @param {Number} limit 
     */
    addJob(limit) {
        const intervalObj = setInterval(() => {
            this.execute(jobid)
        },1000);

        let intervalCtx = new IntervalConext(intervalObj,limit);

        let jobid = this.jobIdCounter;
        this.jobMap.set(this.jobIdCounter, intervalCtx);

        this.jobIdCounter += 1;
    }

    execute(jobNumber) {
        let obj = this.jobMap.get(jobNumber);
        obj.execute(jobNumber);
    }
}

class IntervalConext {
    /**
     * 
     * @param {IntervalObject} invObj 
     * @param {Number} limit 
     */
    constructor(invObj,limit) {
        this.interval = invObj;
        this.limit = limit;
        this.executeCounter = 0;
    }

    execute() {
        const currentTime = new Date();

        this.executeCounter += 1;
        const turnsLeft = this.limit - this.executeCounter;

        console.log(`${currentTime} Intervaled job. Limit : ${turnsLeft}`);

        if( this.executeCounter >= this.limit ) {
            console.log("Clear timer");
            clearInterval(this.interval);
        }
    }
}

const jobMgr = new JobManager()
jobMgr.addJob(2)
jobMgr.addJob(6)
