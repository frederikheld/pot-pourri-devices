'use strict'

var sqlite3 = require('sqlite3')
var mkdirp = require('mkdirp')
var path = require('path')

var exports = module.exports = {}

exports.db

/*
 * Initializes a database at the given location.
 */
exports.initDB = async (dbPath) => {

    var promiseMkdirp
    var promiseCreateDB
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
            promiseCreateDB = new Promise((resolve, reject) => {
                if (err) {
                    reject(err)
                } else {
                    resolve()
                }
            })
        })


    var query = `CREATE TABLE IF NOT EXISTS samples(
                id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,
                device_id INTEGER NOT NULL UNIQUE,
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

    return Promise.all([promiseMkdirp, promiseCreateDB, promiseRunQuery])

}

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
 */
exports.addSample = function (sample) {

    // Some devices can't set a timestamp because they have no clock.
    // In this case the timestamp has to be added here.
    if (!sample.hasOwnProperty('timestamp')) {
        sample.timestamp = new Date().toISOString()
    }

    var query = `INSERT INTO sensor_log(device_id, sensor_id, value_raw, timestamp) VALUES(` +
        sample.device_id + `, ` + sample.sensor_id + `, ` + sample.value_raw + `, "` + sample.timestamp +
        `")`

    return new Promise(function (resolve, reject) {

        this.db.run(query, [], (err) => {
            if (err) {
                reject(err)
            }

            console.log(query)
            resolve()
        })

    })

}