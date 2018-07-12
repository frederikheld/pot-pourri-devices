'use strict'

var express = require('express')
var router = express.Router()
var bodyParser = require('body-parser')

var db = require('./db')

router.use(bodyParser.urlencoded({
    extended: true
}))
router.use(bodyParser.json())

router.get('/', function (req, res) {
    return res.status(200).send({
        msg: "I'm alive!"
    })
})

router.post('/', function (req, res) {

    return res.status(200).send({
        msg: "Thank you for your submission!"
    })

})

router.get('/error', function (req, res) {
    res.status(500).send({
        err: "Unfortunately we could not get what you were lookoing for"
    })
})

router.post('/db/init', function (req, res) {
    db.init(null, function () {

    })
})

router.post('/samples', function (req, res) {
    console.log("received: " + JSON.stringify(req.body))

    return res.status(200).send({
        msg: "You posted: " + JSON.stringify(req.body)
    })
})

router.post('/sensors/datapoint', function (req, res) {

    // var data = {
    //     sensorId: 1,
    //     valueRaw: 860,
    //     timestamp: '2018-07-06T20:09:50.369Z'
    // }
    // db.addSensorDatapoint(data, function (err, data) {
    //     if (err) {
    //         return res.status(500).send("There was a problem adding the information to the database.")
    //     }
    //     res.status(200).send(data)
    // })

})

module.exports = router