'use strict'

console.log("child_2 is alive now :-)")

var timer = setInterval(function () {
    console.log("Hey there! I'm " + process.env.name)
}, 3000)

var timer2 = setInterval(function () {
    console.error("Something went wrong :-(")
}, 5000)