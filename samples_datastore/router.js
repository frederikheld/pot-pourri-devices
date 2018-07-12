'use strict'


// -- imports

var express = require('express')
var router = express.Router()
var bodyParser = require('body-parser')

router.use(bodyParser.urlencoded({
    extended: true
}))
router.use(bodyParser.json())

var actions = require('./actions')


// -- routes

router.post('/samples', (req, res) => {

    return res.status(200).send({
        msg: "Hello World!"
    })

    actions.addSample(req.body)
        .then((res) => {

        })
        .catch((err) => {
            throw new Error("addSample failed! " + err)
        })

})

module.exports = router