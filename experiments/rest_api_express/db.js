'use strict'

var fs = require('fs')
var sqlite = require('sqlite3')

var db = new Object()

db.init = function (msg, done) {

    var db_dir = './db';

    if (!fs.existsSync(db_dir)) {
        fs.mkdirSync(db_dir)
    }

    db = new sqlite3.Database(
        db_dir + '/data.db',
        (err) => {
            if (err) return console.log(err)
        })

    db.run(`CREATE TABLE IF NOT EXISTS sensor_log(
            id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
            sensor_id INTEGER NOT NULL,
            value_raw INTEGER NOT NULL,
            timestamp TEXT NOT NULL
        )`)

    done()

}

db.addSensorDatapoint = function ({
    sensorId,
    valueRaw,
    timestamp
}, done) {


    var query = `INSERT INTO sensor_log(sensor_id, value_raw, timestamp) VALUES(` +
        sensorId + `, ` + valueRaw + `, "` + timestamp +
        `")`

    db.run(query, [],
        (err) => {
            if (err) {
                return done(err)
            }
            return done()
        })

}

db.getDatapointsInterval = function (begin, end) {

    var query = `SELECT *
                FROM sensor_log
                WHERE timestamp
                    BETWEEN ?
                    AND ?
                ORDER BY timestamp
                    ASC`

    db.all(query, [begin, end],
        (err, rows) => {
            if (err) {
                return err
            }

            return {
                data: rows
            }
        })

}

module.exports = db