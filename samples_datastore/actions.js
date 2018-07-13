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
        var promiseRunQuery

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


        var query = `CREATE TABLE IF NOT EXISTS samples(
                id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,
                device_id INTEGER NOT NULL,
                sensor_id INTEGER NOT NULL,
                value_raw INTEGER NOT NULL,
                timestamp TEXT NOT NULL
            )`

        await this.db.run(query, [], (err, res) => {
            promiseRunQuery = new Promise((resolve, reject) => {
                if (err) {
                    reject(err)
                } else {
                    resolve()
                }
            })
        })

        return Promise.all([promiseMkdirp, promiseInitDB, promiseRunQuery])

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

        var query = `INSERT INTO samples(device_id, sensor_id, value_raw, timestamp) VALUES(` +
            sample.device_id + `, ` + sample.sensor_id + `, ` + sample.value_raw + `, "` + sample.timestamp +
            `")`

        this.db.run(query, [], (err) => {
            promiseRunQuery = new Promise(function (resolve, reject) {
                if (err) {
                    reject(err)
                } else {
                    console.log(query)
                    resolve(query)
                }
            })
        })

        return Promise.all([promiseInitDB, promiseRunQuery])

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