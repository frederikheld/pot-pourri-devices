'use strict'

var fs = require('fs')
var sqlite3 = require('sqlite3')

module.exports = function sqlite_select_datastore(options) {

    // -- vars

    var db

    // -- action patterns

    this.add('init: sqlite_select_datastore', init)

    this.add('role: sqlite_select_datastore, cmd: get_datapoints_interval', get_datapoints_interval)


    // -- actions implemented

    function init(msg, respond) {

        var db_dir = './db';

        if (!fs.existsSync(db_dir)) {
            fs.mkdirSync(db_dir)
        }

        db = new sqlite3.Database(
            db_dir + '/data.db',
            (err) => {
                if (err) return console.log(err.message)
            })

        db.run(`CREATE TABLE IF NOT EXISTS sensor_log(
            id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
            sensor_id INTEGER NOT NULL,
            value_raw INTEGER NOT NULL,
            timestamp TEXT NOT NULL
        )`)

        respond()
    }

    function get_datapoints_interval(msg, respond) {

        var query = `SELECT *
                FROM sensor_log
                WHERE timestamp
                    BETWEEN ?
                    AND ?
                ORDER BY timestamp
                    ASC`

        // var query = `SELECT *
        //                 FROM "sensor_log"
        //                 WHERE "timestamp"
        //                     BETWEEN "` + msg.begin + `"
        //                     AND "` + msg.end + `"
        //                 ORDER BY "timestamp"
        //                     ASC`

        //     var query = `SELECT *
        // FROM "sensor_log"
        // WHERE
        //         ("timestamp" > "` + msg.begin + `")
        //     AND ("timestamp" < "` + msg.end + `")
        // ORDER BY "timestamp"
        //     ASC`

        console.log(query)

        // db.all(query, [],
        db.all(query, [msg.begin, msg.end],
            (err, rows) => {
                if (err) {
                    return respond(err)
                }

                respond({
                    data: rows
                })
            })

    }

}