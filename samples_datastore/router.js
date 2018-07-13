'use strict'


// -- imports

var express = require('express')
var router = express.Router()
var bodyParser = require('body-parser')

router.use(bodyParser.urlencoded({
    extended: true
}))
router.use(bodyParser.json())

var Actions = require('./actions')
var actions = new Actions('./db/data.db')


// -- routes

router.post('/samples', (req, res) => {

    actions.addSample(req.body)
        .then((result) => {
            // console.log(result)
            return res.status(201).send({
                msg: "Sample was successfully stored."
            })
        })
        .catch((err) => {
            return res.status(500).send({
                err: err,
                msg: "Sample could not be stored."
            })
        })

})

router.get('/samples', (req, res) => {

    console.log(req.query)

    actions.getSamples(req.query.timestampStart, req.query.timestampEnd)
        .then((result) => {
            return res.status(200).send({
                msg: "Samples successfully queried.",
                data: result
            })
        })
        .catch((err) => {
            return res.status(500).send({
                msg: "Samples could not be queried.",
                err: err
            })
        })
})

module.exports = router