'use strict'

const childProcess = require('child_process')


// var services = [
//     {
//         name: 'datastore',
//         path: './datastore/datastore-service.js'
//     },
//     {
//         name: 'pot_monitoring_serial',
//         path: './pot-monitoring-serial/pot-monitoring-serial-client.js'
//     }
// ]

// var services = [
//     {
//         name: 'child_1',
//         path: './child_processes/child_1.js'
//     },
//     {
//         name: 'child_2',
//         path: './child_processes/child_2.js'
//     }
// ]


/* The following works for
 *  var services = { service_a: { path: 'path/to/service.js' }}
 */
// var services = {
//     datastore: {
//         path: './datastore/datastore-service.js'
//     },
//     pot_monitoring_serial: {
//         path: './pot-monitoring-serial/pot-monitoring-serial-client.js'
//     }
// }

var services = {
    child_1: {
        path: './child_processes/child_1.js'
    },
    child_2: {
        path: './child_processes/child_2.js'
    },
    child_3: {
        path: './child_processes/child_3.js'
    }
}

for (var key in services) {
    (function (key) { // Why the function? The answer is here: https://stackoverflow.com/questions/32358845/how-do-i-listen-and-spawn-multiple-child-process-in-nodejs

        console.log("Spawning " + key + " (" + services[key].path + ") ...")

        services[key].process_handler = childProcess.spawn(
            'node', [services[key].path], {
                env: Object.assign(process.env, {
                    name: key
                })
            })

        // Alternative: process.exec()
        /*
        services[key].process_handler = childProcess.exec(
            'node ' + services[key].path, {
                env: Object.assign(process.env, {
                    name: key
                })
            })
        */

        // No alternative: process.fork()
        /* process.fork will spawn an independent process.
         * When the parent is killed, the children will not be terminated with it!
         */

        services[key].process_handler.name = key

        // Triggered by console.log():
        services[key].process_handler.stdout.on('data', function (data) {
            process.stdout.write(new Date().toISOString() + " [" + key + "] " + data)
            // console.log(new Date().toISOString() + " [" + services[key].process_handler.name + "] " + data.toString())
            // console.log(new Date().toISOString() + " [" + services[key].process_handler.pid + "] " + data.toString())
        })

        // Triggered by console.error() and throw:
        services[key].process_handler.stderr.on('data', function (err) {
            process.stdout.write(new Date().toISOString() + " [" + key + "] ERROR: " + err)
        })

        // Triggered by process.exit():
        services[key].process_handler.on('exit', function (code, signal) {
            console.log(new Date().toISOString() + " [" + key + "] Process terminated by signal " + signal + " with code " + code + ".")
        })

    })(key)
}

/* Alternative
 * for (let [name, data] of Object.entries(services)) { }
 */

process.on('SIGINT', function () {
    console.log(new Date().toISOString() + " Caught interrupt signal. Terminating all child processes...")

    for (var key in services) {
        console.log(new Date().toISOString() + " Terminating " + key + "...")
        services[key].process_handler.exitCode = 0
    }

    process.exitCode = 1
})