'use strict'

var helloWorld = require('./module')

var hw1 = new helloWorld()
console.log(hw1.greet())
hw1.setGreeting("Wazaaaap?")
console.log(hw1.greet())

var hw2 = new helloWorld()
console.log(hw2.greet())

var hw3 = new helloWorld("Bonjour!")
console.log(hw3.greet())