const nodemon = require("nodemon");

// nodemon({script: 'tsc -v'}).on('start', () => {
//     console.log("started")
// }).on('restart', () => {
//     console.log("first restarted")
// });

nodemon({script: 'node -v'}).on('restart', () => {
    console.log("restarted")
})