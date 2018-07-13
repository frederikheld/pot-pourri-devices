'use strict'

module.exports = HelloWorld

// var HelloWorld = (function (greeting = "Hello World!") {
function HelloWorld(greeting = "Hello World!") {

    this.greeting = greeting

    this.greet = function () {
        return this.greeting
    }

    this.setGreeting = function (greeting) {
        this.greeting = greeting
    }

    return this
}
// })
// module.exports = HelloWorld