// The purpose of this program is to use anync way to elumating a job which 
// would run for certain ammount of time

// As of now this is a any to any map
const jobMap = new Map();

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

// Once the limit is reached it would stop the printing
function intervalFunction(param) {
    const ctx = jobMap.get(param);
    ctx.execute();
}

const firstInterval = setInterval(() => { intervalFunction(1)}, 1000);
let intervalCtx1 = new IntervalConext(firstInterval,5);
jobMap.set(1, intervalCtx1);

const secondInterval = setInterval(() => { intervalFunction(2)}, 500);
const intervalCtx2 = new IntervalConext(secondInterval, 10);
jobMap.set(2, intervalCtx2);
