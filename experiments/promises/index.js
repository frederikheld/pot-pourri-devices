'use strict'

var actions = require('./actions')


actions.foo("bar bar")
    .then((res) => {
        console.log("Result: " + res)
    })

actions.promiseAll()
    .then((res) => {
        console.log(res)
    })
    .catch((err) => {
        console.error(err)
    })