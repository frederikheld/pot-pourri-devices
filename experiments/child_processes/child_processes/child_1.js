'use strict'

console.log("child_1 is alive now :-)")

var timer = setInterval(function () {
    console.log("Hey there! I'm " + process.env.name)
}, 1000)