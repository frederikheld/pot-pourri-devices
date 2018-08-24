'use strict'

var sqlite3 = require('sqlite3')
var mkdirp = require('mkdirp')
var path = require('path')

module.exports = Actions

function Actions(dbPath) {

    this.dbPath = dbPath
    this.db = null


    /*
     * Initializes a database at the given location.
     * 
     * Will be executed immediately at object instantiation.
     */
    this.__constructor = (async (dbPath) => {

        var promiseMkdirp
        var promiseInitDB
        var promiseRunQuerySamples

        var dir = path.dirname(dbPath)

        await mkdirp(dir, (err) => {
            promiseMkdirp = new Promise((resolve, reject) => {
                if (err) {
                    reject(err)
                } else {
                    resolve()
                }
            })
        })

        this.db = new sqlite3.Database(
            dbPath, [],
            (err) => {
                promiseInitDB = new Promise((resolve, reject) => {
                    if (err) {
                        reject(err)
                    } else {
                        resolve()
                    }
                })
            })


        var querySamples = `CREATE TABLE IF NOT EXISTS samples(
                id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,
                device_id INTEGER NOT NULL,
                sensor_id INTEGER NOT NULL,
                value_raw INTEGER NOT NULL,
                timestamp TEXT NOT NULL
            )`

        await this.db.run(querySamples, [], (err, res) => {
            promiseRunQuerySamples = new Promise((resolve, reject) => {
                if (err) {
                    reject(err)
                } else {
                    resolve()
                }
            })
        })

        // var queryMeta = `CREATE TABLE IF NOT EXISTS plants(
        //     id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,
        //     name TEXT NOT NULL,
        //     color TEXT
        // )`

        // var querySensors = `CREATE TABLE IF NOT EXISTS sensors(
        //     id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,
        //     address TEXT NOT NULL
        //     type TEXT NOT NULL
        // )`

        return Promise.all([promiseMkdirp, promiseInitDB, promiseRunQuerySamples])

    })(dbPath) // Constructor: Therefore called immediately


    /*
     *  Sample is a json object that has
     *  the following structure:
     * 
     *  {
     *      device_id: <device id>,
     *      sensor_id: <senosr id>,
     *      value_raw: <raw value>,
     *      timestamp: <timestam in iso format>
     *  }
     * 
     *  If successful, the function resolves with
     *  the database query string.
     */
    this.addSample = function (sample) {

        var promiseInitDB
        var promiseRunQuery

        // Some devices can't set a timestamp because they have no clock.
        // In this case the timestamp has to be added here.
        if (!sample.hasOwnProperty('timestamp')) {
            sample.timestamp = new Date().toISOString()
        }

        process.stdout.write("POST /samples: " + JSON.stringify(sample)) // TODO: Should be done in index.js and returned via resolve. It didn't work this way though :-P

        this.db = new sqlite3.Database(
            dbPath, [],
            (err) => {
                promiseInitDB = new Promise((resolve, reject) => {
                    if (err) {
                        return reject(err)
                    } else {
                        return resolve()
                    }
                })
            })

        var query = `INSERT INTO samples(device_id, sensor_id, value_raw, timestamp) VALUES(?, ?, ?, ?)`

        this.db.run(query, [sample.device_id, sample.sensor_id, sample.value_raw, sample.timestamp], (err) => {
            promiseRunQuery = new Promise(function (resolve, reject) {
                if (err) {
                    console.log(" failed")
                    return reject(err)
                } else {
                    console.log(" successful")
                    return resolve(query)
                }
            })
        })

        return Promise.all([promiseInitDB, promiseRunQuery])

    }


    /*
     * Query samples in the interval between intervalStart and intervalEnd
     * 
     * intervalStart: ISO formatted timestamp
     * intervalEnd: ISO formatted timestamp
     */

    this.getSamples = function (intervalStart, intervalEnd) {

        var promiseInitDB
        var promiseRunQuery

        process.stdout.write("GET  /samples: " + intervalStart + ' -> ' + intervalEnd)

        return new Promise((resolve, reject) => {

            // create db object
            this.db = new sqlite3.Database(
                dbPath, [],
                (err) => {
                    if (err) {
                        return reject(err)
                    }
                })

            // create query
            var query = `SELECT *
                    FROM samples
                    WHERE timestamp
                        BETWEEN ?
                        AND ?
                    ORDER BY timestamp
                        ASC`

            // run query
            this.db.all(query, [intervalStart, intervalEnd],
                function (err, rows) {
                    if (err) {
                        console.log(" failed")
                        return reject(err)
                    } else {
                        console.log(" successful")
                        return resolve(rows)
                    }
                })

        })

    }


    // -- actions for debugging purposes

    /*
     * Just returns the string "Hello World!"
     */
    this.helloWorld = function () {
        return "Hello World!"
    }


    /*
     *  Returns exactly what was passed into it.
     */
    this.echo = function (input) {
        return input
    }

}