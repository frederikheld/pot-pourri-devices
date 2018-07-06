'use strict'

console.log("child_3 is alive now :-)")

var timer = setInterval(function () {
    console.log("Hey there! I'm " + process.env.name)
}, 3000)

var timer2 = setInterval(function () {
    throw new Error("Panic!!!")
}, 5000)